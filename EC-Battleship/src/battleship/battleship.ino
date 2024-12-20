#include <Adafruit_NeoPixel.h>
#include <Vector.h>
#include "battleship_class.hpp"

#define PIN 6 //Pin digital
#define MATRIX_WIDTH 16 //Numero de columnas
#define MATRIX_HEIGHT 16 //Numero de filas
#define NUM_PIXELS MATRIX_WIDTH * MATRIX_HEIGHT //Numero de pixeles
#define BRIGHTNESS 50 //Brillo de los leds

#define SHIP_WIDTH 1 //Este numero corresponde a la anchura de los barcos
#define SHIP_HEIGHT 1 //Este numero corresponde a la altura de los barcos
#define NUM_BARCOS 1 //Numero de barcos
#define TAM 3

Adafruit_NeoPixel led_matrix = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int A_BUTTON      = 0;
const int B_BUTTON      = 1;
const int SELECT_BUTTON = 2; 
const int START_BUTTON  = 3;
const int UP_BUTTON     = 4;
const int DOWN_BUTTON   = 5;
const int LEFT_BUTTON   = 6;
const int RIGHT_BUTTON  = 7;


/*enum buttons
{
  A_BUTTON //0
  B_BUTTON //1
  SELECT_BUTTON //2
  START_BUTTON //3
  UP_BUTTON //4
  DOWN_BUTTON //5
  LEFT_BUTTON //6
  RIGHT_BUTTON //7
}*/

byte nesRegister = 0;
int data = 4;   // Pin de datos del controlador NES verde
int clk = 2;    // Pin de clock del controlador NES blanco
int latch = 3;  // Pin de latch del controlador NES negro

//Barcos
int ejeX[] = {0,0,0};
int ejeY[] = {0,1,2};
Battleship* barcos = new Battleship(ejeX,ejeY);

//Posicion inicial de los leds. Cambia a arrays si los tamaños de los datos son distintos a uno
//const unsigned tam = barcos.get_size();
int ledX[TAM] = {0,0,0};
int ledY[TAM] = {0,1,2};
//Esquina superior izquierda.

//Color del led en formato RGB
uint32_t colorLed = led_matrix.Color(255,0,0); //Rojo puro


void atacar(Battleship atacante, Battleship defensor);

void display(Battleship barcos[], int ledX[], int ledY[])
{
  unsigned tam = barcos->get_size();
  Vector<int> posX = barcos->get_ejeX();
  Vector<int> posY = barcos->get_ejeY();

  for(unsigned i = 0; i < tam; ++i)
  {
    ledX[i] = posX.at(i);
    ledY[i] = posY.at(i);
  }
  return;
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
  led_matrix.clear();  // Limpia todos los LEDs
  int pixelIndex[TAM];
  for(int i=0; i<TAM; ++i)
  {
    pixelIndex[i] = obtenerIndiceMatriz(ledX[i], ledY[i]);  // Convierte las coordenadas (X, Y) al índice en la matriz en formato serpiente
    led_matrix.setPixelColor(pixelIndex[i], colorLed);  // Establece el color del LED en la posición actual
    led_matrix.show();  // Muestra los cambios en la matriz
  }
  
}

void setup()
{
  Serial.begin(9600);

  pinMode(data,INPUT);
  pinMode(clk, OUTPUT);
  pinMode(latch, OUTPUT);
  digitalWrite(clk, LOW);
  digitalWrite(latch, LOW);

  //Inicializacion de la matriz
  led_matrix.begin();
  led_matrix.setBrightness(BRIGHTNESS);
  led_matrix.show();
}

void loop()
{
  
 nesRegister = readNesController();
 
  // Movimientos de la cruceta
  if (bitRead(nesRegister, UP_BUTTON) == 0 && ledY[0] > 0) {  //límite superior
    for(int i=0; i< NUM_BARCOS; ++i)
    {
      barcos[i].mover(0, -1);
    }
    Serial.println("arriba");
  } 
  if (bitRead(nesRegister, DOWN_BUTTON) == 0 && ledY[3] < MATRIX_HEIGHT - 1-1) {  //límite inferior
    for(int i=0; i< NUM_BARCOS; ++i)
    {
      barcos[i].mover(0,1);
    }
    Serial.println("abajo");
  }
  if (bitRead(nesRegister, RIGHT_BUTTON) == 0 && ledX[2] > 0) { //límite derecha
  for(int i=0; i< NUM_BARCOS; ++i)
    barcos[i].mover(1,0);
  Serial.println("derecha");
  }
  if (bitRead(nesRegister, LEFT_BUTTON) == 0 && ledX < MATRIX_WIDTH - 1) { //límite izquierda
    for(int i=0; i< NUM_BARCOS; ++i)
      barcos[i].mover(-1,0);
  }
  
  display(barcos, ledX, ledY);
  actualizarMatriz();
}

byte readNesController() {  
  byte tempData = 0xFF;
  
  // Pulso en el latch para leer el estado de los botones
  digitalWrite(latch, HIGH);
  delayMicroseconds(2);
  digitalWrite(latch, LOW);

  for (int i = 0; i < 8; i++) {
    if (digitalRead(data) == LOW)
      bitClear(tempData, i);
    
    digitalWrite(clk, HIGH);
    delayMicroseconds(2);
    digitalWrite(clk, LOW);
  }
  
  return tempData;
}
