idf_component_register(SRCS "main.c"
                            "ads1293_driver.c"
                            "ecg_processing.c"
                            "event_classifier.c"
                            "alert_manager.c"
                       INCLUDE_DIRS "."
                       REQUIRES esp_timer esp_wifi esp_http_client mbedtls driver nvs_flash json)
