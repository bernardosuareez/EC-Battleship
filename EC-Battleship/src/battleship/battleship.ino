#include <Adafruit_Neopixel.h>
#include "battleship_class.hpp"


#define PIN 6 //Pin digital
#define MATRIX_WIDTH 16 //Numero de columnas
#define MATRIX_HEIGHT 16 //Numero de filas
#define NUM_PIXELS MATRIX_WIDTH * MATRIX_HEIGHT //Numero de pixeles
#define BRIGHTNESS 50 //Brillo de los leds

#define SHIP_WIDTH 1 //Este numero corresponde a la anchura de los barcos
#define SHIP_HEIGHT 1 //Este numero corresponde a la altura de los barcos

Adafruit_NeoPixel led_matrix = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int A_BUTTON      = 0;
const int B_BUTTON      = 1;
const int SELECT_BUTTON = 2; 
const int START_BUTTON  = 3;
const int UP_BUTTON     = 4;
const int DOWN
const int
const int

enum buttons
{
  A_BUTTON //0
  B_BUTTON //1
  SELECT_BUTTON //2
  START_BUTTON //3
  UP_BUTTON //4
  DOWN_BUTTON //5
  LEFT_BUTTON //6
  RIGHT_BUTTON //7
}

byte nes_register = 0;
int data = 4;   // Pin de datos del controlador NES verde
int clk = 2;    // Pin de clock del controlador NES blanco
int latch = 3;  // Pin de latch del controlador NES negro

//Posicion inicial de los leds. Cambia a arrays si los tamaños de los datos son distintos a uno
int ledX = 0;
int ledY = 0;
//Esquina superior izquierda.

//Color del led en formato RGB
unit32_t colorLed = led_matrix.Color(255,0,0) //Rojo puro

void setup
{
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

void loop
{
 nes_register = readNesController();
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
      --ledX;
    Serial.println("derecha");
  }
  if (bitRead(nesRegister, LEFT_BUTTON) == 0 && ledX < MATRIX_WIDTH - 1) { //límite izquierda
    ++ledX;
  }
}