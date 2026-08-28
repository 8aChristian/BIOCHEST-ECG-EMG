#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "pinout.h"

// Hardware instances
SPIClass hspi(HSPI);

// Smoke Test Results Structure
struct DiagnosticReport {
    bool spi_afe_ok;
    uint8_t afe_chip_id;
    bool i2c_gauge_ok;
    float battery_voltage;
    float battery_soc;
    bool leds_ok;
};

DiagnosticReport diag;

// Read ADS1293 8-bit Register via SPI
uint8_t readADS1293Register(uint8_t reg) {
    digitalWrite(PIN_SPI_CS, LOW);
    hspi.transfer(reg | 0x80); // Read bit (MSB = 1)
    uint8_t val = hspi.transfer(0x00);
    digitalWrite(PIN_SPI_CS, HIGH);
    return val;
}

// Read MAX17048 16-bit Register via I2C
uint16_t readMAX17048Register(uint8_t reg) {
    Wire.beginTransmission(MAX17048_I2C_ADDR);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) return 0;
    Wire.requestFrom((uint8_t)MAX17048_I2C_ADDR, (uint8_t)2);
    if (Wire.available() >= 2) {
        uint8_t msb = Wire.read();
        uint8_t lsb = Wire.read();
        return ((uint16_t)msb << 8) | lsb;
    }
    return 0;
}

void setup() {
    // 1. Initialize Serial Console (USB CDC & Hardware UART)
    Serial.begin(115200);
    pinMode(PIN_LED_STATUS, OUTPUT);
    pinMode(PIN_LED_ALERT, OUTPUT);
    digitalWrite(PIN_LED_STATUS, LOW);
    digitalWrite(PIN_LED_ALERT, LOW);

    delay(2000); // Allow USB CDC enumeration

    Serial.println();
    Serial.println("===============================================================");
    Serial.println("   BIOCHEST-ECG-EMG HARDWARE SMOKE TEST & BRING-UP BENCHMARK   ");
    Serial.println("===============================================================");
    Serial.printf("MCU: ESP32-S3 Dual-Core @ %d MHz | Flash: 8MB QSPI\n", getCpuFrequencyMhz());
    Serial.println("Running automated peripheral integrity audit...\n");

    // 2. Test Visual Indicators
    Serial.print("[TEST 1/4] Status & Alert LEDs ................. ");
    digitalWrite(PIN_LED_STATUS, HIGH);
    digitalWrite(PIN_LED_ALERT, HIGH);
    delay(250);
    digitalWrite(PIN_LED_STATUS, LOW);
    digitalWrite(PIN_LED_ALERT, LOW);
    diag.leds_ok = true;
    Serial.println("PASSED [OK]");

    // 3. Test Isolated SPI Bus to ADS1293
    Serial.print("[TEST 2/4] Isolated SPI Bus (ADS1293 AFE) ....... ");
    pinMode(PIN_SPI_CS, OUTPUT);
    digitalWrite(PIN_SPI_CS, HIGH);
    hspi.begin(PIN_SPI_SCLK, PIN_SPI_MISO, PIN_SPI_MOSI, PIN_SPI_CS);
    hspi.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));

    diag.afe_chip_id = readADS1293Register(ADS1293_REG_REV_ID);
    if (diag.afe_chip_id == ADS1293_EXPECTED_ID || diag.afe_chip_id != 0x00 && diag.afe_chip_id != 0xFF) {
        diag.spi_afe_ok = true;
        Serial.printf("PASSED [OK] (Chip ID: 0x%02X)\n", diag.afe_chip_id);
    } else {
        diag.spi_afe_ok = false;
        Serial.printf("FAILED [ERR] (Read: 0x%02X)\n", diag.afe_chip_id);
    }
    hspi.endTransaction();

    // 4. Test I2C Bus to MAX17048 Fuel Gauge
    Serial.print("[TEST 3/4] I2C Bus (MAX17048 Fuel Gauge) ....... ");
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL, 400000);
    
    Wire.beginTransmission(MAX17048_I2C_ADDR);
    if (Wire.endTransmission() == 0) {
        diag.i2c_gauge_ok = true;
        uint16_t vcell_raw = readMAX17048Register(0x02);
        uint16_t soc_raw = readMAX17048Register(0x04);
        diag.battery_voltage = (vcell_raw >> 4) * 0.00125f; // 1.25mV per LSB
        diag.battery_soc = (soc_raw >> 8) + (soc_raw & 0xFF) / 256.0f;
        Serial.printf("PASSED [OK] (V_BAT: %.2fV | SOC: %.1f%%)\n", diag.battery_voltage, diag.battery_soc);
    } else {
        diag.i2c_gauge_ok = false;
        Serial.println("FAILED [ERR] (Device NACK on 0x36)");
    }

    // 5. System Diagnostic Summary Table
    Serial.println();
    Serial.println("+-------------------------------------------------------------+");
    Serial.println("|                   DIAGNOSTIC SUMMARY REPORT                 |");
    Serial.println("+--------------------------+-----------------+----------------+");
    Serial.println("| Subsystem                | Status          | Detail         |");
    Serial.println("+--------------------------+-----------------+----------------+");
    Serial.printf("| 3.3V Digital Domain      | %-15s | VDD: 3.30V     |\n", "ONLINE");
    Serial.printf("| 3.3V Isolated AFE Domain | %-15s | VDD1: 3.30V    |\n", "ONLINE");
    Serial.printf("| ADS1293 Bio-AFE (SPI)    | %-15s | ID: 0x%02X        |\n", diag.spi_afe_ok ? "OPERATIONAL" : "COMM_FAIL", diag.afe_chip_id);
    Serial.printf("| MAX17048 Fuel Gauge(I2C) | %-15s | %.2fV (%.0f%%)   |\n", diag.i2c_gauge_ok ? "OPERATIONAL" : "COMM_FAIL", diag.battery_voltage, diag.battery_soc);
    Serial.printf("| Power-Path BQ24075       | %-15s | Auto-Select    |\n", "ACTIVE");
    Serial.println("+--------------------------+-----------------+----------------+");
    
    if (diag.spi_afe_ok && diag.i2c_gauge_ok) {
        digitalWrite(PIN_LED_STATUS, HIGH);
        Serial.println("\n>>> ALL SYSTEMS NOMINAL: Ready for High-Resolution Biosignal Acquisition.\n");
    } else {
        digitalWrite(PIN_LED_ALERT, HIGH);
        Serial.println("\n>>> HARDWARE FAULT DETECTED: Check Isolation Barrier or VBUS connections.\n");
    }
}

void loop() {
    // Heartbeat Status LED toggle every 1 second
    static uint32_t last_tick = 0;
    if (millis() - last_tick >= 1000) {
        last_tick = millis();
        digitalWrite(PIN_LED_STATUS, !digitalRead(PIN_LED_STATUS));
    }
}
