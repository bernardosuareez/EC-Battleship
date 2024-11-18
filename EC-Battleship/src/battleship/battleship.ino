#include <Adafruit_NeoPixel.h>
#include "battleship_class.hpp"

#define PIN 6 //Pin digital
#define MATRIX_WIDTH 16 //Numero de columnas
#define MATRIX_HEIGHT 16 //Numero de filas
#define NUM_PIXELS MATRIX_WIDTH * MATRIX_HEIGHT //Numero de pixeles
#define BRIGHTNESS 50 //Brillo de los leds

#define SHIP_WIDTH 1 //Este numero corresponde a la anchura de los barcos
#define SHIP_HEIGHT 1 //Este numero corresponde a la altura de los barcos

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

byte nes_register = 0;
int data = 4;   // Pin de datos del controlador NES verde
int clk = 2;    // Pin de clock del controlador NES blanco
int latch = 3;  // Pin de latch del controlador NES negro

//Barcos
Battleship barcos = Battleship(3,0,0);

//Posicion inicial de los leds. Cambia a arrays si los tamaños de los datos son distintos a uno
//const unsigned tam = barcos.get_size();
int ledX[TAM] = {0,0,0};
int ledY[TAM] = {0,0,0};
//Esquina superior izquierda.

//Color del led en formato RGB
uint32_t colorLed = led_matrix.Color(255,0,0); //Rojo puro


void atacar(Battleship atacante, Battleship defensor);

void display(Battleship barco, int* ledX, int* ledY)
{
  unsigned tam = barco.get_size();
  //Serial.println(tam);
  int posX;
  int* posY;
  posX = barco.get_ejeX();
  posY = barco.get_ejeY();

  //Serial.println(posX);


  for(unsigned i = 0; i < tam; ++i)
  {
    //Serial.println(posY[i]);
    ledX[i] = posX;
    ledY[i] = posY[i];
    delay(500);
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
 /*nes_register = readNesController();
 
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
  */
  display(barcos, ledX, ledY);
  actualizarMatriz();
}

