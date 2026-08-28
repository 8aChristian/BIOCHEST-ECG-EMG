# BIOCHEST-ECG/EMG — Análisis de Aislamiento Galvánico y Seguridad Eléctrica

## 1. Marco de Referencia Normativo
- **Norma Base:** IEC 60601-1:2005+AMD1:2012 (3ª Edición) — *Requisitos generales para la seguridad básica y el funcionamiento esencial*.
- **Clasificación del Prototipo:** Parte aplicada de tipo CF (cardíaca flotante), orientado a monitorización torácica en investigación.
- **Tensión de Trabajo Máxima:** $250\,\text{V}_{\text{RMS}}$ de red en condición de falla externa.
- **Medios de Protección Requeridos:** 2 MOPP (Means of Patient Protection).

---

## 2. Parámetros Físicos de la Barrera de Aislamiento

| Parámetro | Requerido (IEC 60601-1 2 MOPP) | Implementado en BIOCHEST | Margen de Seguridad | Clasificación |
| :--- | :--- | :--- | :--- | :--- |
| **Rigidez Dieléctrica ($V_{\text{ISO}}$)** | $4000\,\text{V}_{\text{RMS}}$ (1 min) | **$5000\,\text{V}_{\text{RMS}}$** (TI ISO7741UDWR) | $+25\%$ | [A] Datasheet |
| **Distancia de Fuga (*Creepage*)** | $\ge 8.0\,\text{mm}$ (Material Group IIIb) | **$14.5\,\text{mm}$** (Encapsulado SOIC-16 DWW) | $+81.2\%$ | [A] Datasheet |
| **Espacio de Aire (*Clearance*)** | $\ge 5.0\,\text{mm}$ | **$14.2\,\text{mm}$** en encapsulado / **$2.0\,\text{mm}$** ranura fresada | Cumple con creces | [A] Datasheet |
| **Inmunidad a Transitorios (CMTI)** | $> 25\,\text{kV}/\mu\text{s}$ | **$100\,\text{kV}/\mu\text{s}$** típico | $4\times$ margen | [A] Datasheet |
| **Corriente de Fuga a Paciente (NC)** | $< 10\,\mu\text{A}$ (Tipo CF) | **$< 2\,\mu\text{A}$** estimado (batería aislada) | Cumple | [C] Inferencia |

---

## 3. Topología de Doble Dominio en PCB

```
┌──────────────────────────────────────┐       ╔═══════════════════════╗       ┌──────────────────────────────────────┐
│        DOMINIO AFE / PACIENTE        │       ║ BARRERA DE AISLAMIENTO║       │         DOMINIO DIGITAL (MCU)        │
│  - 5 Snaps textiles (ECG/EMG/RLD)    │       ║ (5000 Vrms, 2 MOPP)   ║       │  - ESP32-S3-MINI-1 (WiFi/BLE)        │
│  - Supresión ESD TPD2E001 (<0.9 pF)  │  ==>  ║ - ISO7741UDWR (DWW-16)║  ==>  │  - Puerto USB-C (Prog/Carga)         │
│  - Texas Instruments ADS1293 (24-bit)│       ║ - DC-DC B0503S Aislado║       │  - Cargador LiPo BQ24075 + DW01A     │
│  - LDO Ultra bajo ruido TPS7A2033    │       ║ - Ranura PCB 2.0x24mm ║       │  - Fuel Gauge MAX17048               │
│  - Plano de Masa: AGND (Layer 2)     │       ║ - Keepout Cobre 14.5mm║       │  - Plano de Masa: DGND (Layer 2)     │
└──────────────────────────────────────┘       ╚═══════════════════════╝       └──────────────────────────────────────┘
```

> **Aviso de Responsabilidad:** El diseño incorpora los márgenes requeridos por IEC 60601-1; el cumplimiento formal de 2 MOPP para certificación clínica exige ensayos de tipo hi-pot y corrientes de fuga en laboratorio acreditado sobre el gabinete final.
