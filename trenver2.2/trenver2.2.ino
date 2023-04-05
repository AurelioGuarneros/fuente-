const int pulsePin1 = 5; // Pin para el primer tren de pulsos
const int pulsePin2 = 6; // Pin para el segundo tren de pulsos
const int pulseWidth = 15; // Ancho del pulso en microsegundos (1/20kHz)
const int deadTime = 3; // Tiempo muerto entre pulsos en microsegundos
const int cycleTime = 2500; // Tiempo total de un ciclo en milisegundos Apagado
const int pulseTime = 2500; // Tiempo durante el cual se generan pulsos en cada ciclo

unsigned long startTime; // Tiempo de inicio del ciclo actual
int cycleCount = 0; // Conteo de ciclos realizados

void setup() {
  pinMode(pulsePin1, OUTPUT);
  pinMode(pulsePin2, OUTPUT);
  startTime = millis(); // Guardar el tiempo de inicio
}

void loop() {
  // Verificar si se ha alcanzado el tiempo total del ciclo actual
  if (millis() - startTime >= cycleTime) {
    cycleCount++; // Incrementar el conteo de ciclos realizados
    startTime = millis(); // Reiniciar el tiempo de inicio
  }

  // Verificar si se está dentro del tiempo de generación de pulsos
  if (millis() - startTime < pulseTime && cycleCount % 2 == 0) {
    // Generar el primer tren de pulsos
    digitalWrite(pulsePin1, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(pulsePin1, LOW);
    delayMicroseconds(deadTime);

    // Generar el segundo tren de pulsos desfasado
    digitalWrite(pulsePin2, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(pulsePin2, LOW);
    delayMicroseconds(deadTime);
  } else {
    // Detener los pulsos
    digitalWrite(pulsePin1, LOW);
    digitalWrite(pulsePin2, LOW);
  }
}
