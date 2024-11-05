#include <Adafruit_NeoPixel.h>

// Configuración de la matriz NeoPixel
#define PIN            6         // Pin donde está conectado el NeoPixel
#define MATRIX_WIDTH   16        // Ancho de la matriz
#define MATRIX_HEIGHT  16        // Altura de la matriz
#define NUM_PIXELS     MATRIX_WIDTH * MATRIX_HEIGHT  // Número total de píxeles
#define BRIGHTNESS     50       // Brillo de la matriz (mitad de 255)

// Configuración de la matriz NeoPixel
Adafruit_NeoPixel matrix = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Configuración del controlador NES
const int A_BUTTON         = 0;
const int B_BUTTON         = 1;
const int SELECT_BUTTON    = 2;
const int START_BUTTON     = 3;
const int UP_BUTTON        = 4;
const int DOWN_BUTTON      = 5;
const int LEFT_BUTTON      = 6;
const int RIGHT_BUTTON     = 7;

byte nesRegister = 0;
int nesData      = 4;    // Pin de datos del controlador NES verde
int nesClock     = 2;    // Pin de clock del controlador NES blanco
int nesLatch     = 3;    // Pin de latch del controlador NES negro

// Posición inicial del LED
int ledX[4] = {0,1,0,1};
int ledY[4] = {0,0,1,1};

// Colores
uint32_t colorActual = matrix.Color(255, 0, 0); // Rojo inicial

void setup() {
  Serial.begin(9600);

  // Configuración del controlador NES
  pinMode(nesData, INPUT);
  pinMode(nesClock, OUTPUT);
  pinMode(nesLatch, OUTPUT);
  digitalWrite(nesClock, LOW);
  digitalWrite(nesLatch, LOW);

  // Inicialización de la matriz NeoPixel
  matrix.begin();
  matrix.setBrightness(BRIGHTNESS);  // Establece el brillo a la mitad
  matrix.show();  // Apaga todos los LEDs al inicio
}

void loop() {
  nesRegister = readNesController();  // Lee el estado del controlador

  // Movimientos de la cruceta
  if (bitRead(nesRegister, UP_BUTTON) == 0 && ledY[0] > 0) {  //límite superior
    for(int i=0; i<4; ++i)
    {
      ----ledY[i];
    }
    Serial.println("arriba");
  } 
  if (bitRead(nesRegister, DOWN_BUTTON) == 0 && ledY[3] < MATRIX_HEIGHT - 1-1) {  //límite inferior
    for(int i=0; i<4; ++i)
    {
      ++++ledY[i];
    }
    Serial.println("abajo");
  }
  if (bitRead(nesRegister, RIGHT_BUTTON) == 0 && ledX[2] > 0) { //límite derecha
    for(int i=0; i<4; ++i)
    {
      ----ledX[i];
    }
    Serial.println("derecha");
  }
  if (bitRead(nesRegister, LEFT_BUTTON) == 0 && ledX[1] < MATRIX_WIDTH - 1) { //límite izquierda
    for(int i=0; i<4; ++i)
    {
      ++++ledX[i];
    }
    Serial.println("izquierda");
  }

  // Cambia el color según el botón presionado
  if (bitRead(nesRegister, A_BUTTON) == 0) {
    colorActual = matrix.Color(0, 0, 255);  // Azul
  } 
  if (bitRead(nesRegister, B_BUTTON) == 0) {
    colorActual = matrix.Color(0, 255, 0);  // Verde
  }
  if (bitRead(nesRegister, START_BUTTON) == 0) {
    colorActual = matrix.Color(255, 0, 0);  // Rojo
  }
  if (bitRead(nesRegister, SELECT_BUTTON) == 0) {
    colorActual = matrix.Color(255, 255, 0);  // Amarillo
  }

  // Actualiza la matriz de LEDs
  actualizarMatriz();

  // Espera antes de la siguiente lectura del controlador
  delay(100);
}

// Función para convertir las coordenadas (X, Y) en índice considerando el formato de "serpiente"
int obtenerIndiceMatriz(int x, int y) {
  if (y % 2 == 0) {
    // Si la fila es par, el índice va de izquierda a derecha
    return y * MATRIX_WIDTH + x;
  } else {
    // Si la fila es impar, el índice va de izquierda a derecha para evitar inversión
    return y * MATRIX_WIDTH + (MATRIX_WIDTH - 1 - x);
  }
}

// Función para actualizar el LED activo en la matriz
void actualizarMatriz() {
  matrix.clear();  // Limpia todos los LEDs
  int pixelIndex[4];
  for(int i=0; i<4; ++i)
  {
    pixelIndex[i] = obtenerIndiceMatriz(ledX[i], ledY[i]);  // Convierte las coordenadas (X, Y) al índice en la matriz en formato serpiente
    matrix.setPixelColor(pixelIndex[i], colorActual);  // Establece el color del LED en la posición actual
    matrix.show();  // Muestra los cambios en la matriz
  }
  
}

// Función para leer el estado del controlador NES
byte readNesController() {  
  byte tempData = 0xFF;
  
  // Pulso en el latch para leer el estado de los botones
  digitalWrite(nesLatch, HIGH);
  delayMicroseconds(2);
  digitalWrite(nesLatch, LOW);

  for (int i = 0; i < 8; i++) {
    if (digitalRead(nesData) == LOW)
      bitClear(tempData, i);
    
    digitalWrite(nesClock, HIGH);
    delayMicroseconds(2);
    digitalWrite(nesClock, LOW);
  }
  
  return tempData;
}
