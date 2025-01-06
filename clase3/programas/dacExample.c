void setup() {
    // Iniciar el DAC
    dacBegin(25); // Pin 25 para DAC1
}

void loop() {
    // Enviar valores al DAC
    for (int value = 0; value <= 255; value++) {
        // Escribir el valor en el DAC
        dacWrite(25, value);
        delay(10); // Esperar un poco para ver el cambio
    }

    // Decrementar el valor
    for (int value = 255; value >= 0; value--) {
        // Escribir el valor en el DAC
        dacWrite(25, value);
        delay(10); // Esperar un poco para ver el cambio
    }
}