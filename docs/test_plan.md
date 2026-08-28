# BIOCHEST-ECG/EMG — Plan Maestro de Pruebas y Validación (12 Fases)

Este protocolo define las 12 fases obligatorias de ensayo antes de cualquier despliegue experimental en voluntarios humanos:

1. **Fase 1: Simulación SPICE y Modelado Matemático (Completada):** Verificación de filtros anti-aliasing, CMRR y respuesta en frecuencia.
2. **Fase 2: Generador de Señal ECG Sintética Calibrada:** Inyección de patrones estándar MIT-BIH y validación del detector Pan-Tompkins.
3. **Fase 3: Generador de Señales sEMG:** Inyección de trenes de pulso mioeléctricos (20–500 Hz) para evaluar ancho de banda y distorsión.
4. **Fase 4: Osciloscopio y Medición de Ruido Residual:** Verificación de piso de ruido $< 50\,\mu\text{V}_{\text{RMS}}$ referido a entrada con terminales en corto.
5. **Fase 5: Ensayos de Descarga Electrostática (ESD):** Ensayos según IEC 61000-4-2 ($\pm 8\,\text{kV}$ contacto / $\pm 15\,\text{kV}$ aire en snaps).
6. **Fase 6: Compatibilidad Electromagnética (EMC):** Verificación de emisiones radiadas por ESP32-S3 y supresión de armónicos RF.
7. **Fase 7: Ensayo de Rigidez Dieléctrica y Aislamiento:** Prueba hi-pot a $4000\,\text{V}_{\text{RMS}}$ (1 min) a través de la barrera de aislamiento.
8. **Fase 8: Ensayos Mecánicos de Banda Torácica:** Ensayos de tracción, elasticidad cíclica y retención de snaps (500 ciclos).
9. **Fase 9: Ensayos de Sudor y Humedad:** Exposición a solución salina isotónica para verificar corrosión y estabilidad de impedancia.
10. **Fase 10: Comparación Directa con ECG de Referencia:** Adquisición simultánea frente a Polar H10 y holter de referencia con correlación $R^2 > 0.95$.
11. **Fase 11: Estudio de Artefactos de Movimiento:** Evaluación de SNR durante reposo, caminata a 4 km/h y trote a 8 km/h.
12. **Fase 12: Estudio Piloto con Voluntarios:** Protocolo de investigación aprobado con consentimiento informado y registro continuo de 24h.
