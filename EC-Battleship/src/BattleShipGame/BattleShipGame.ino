
#include <Adafruit_NeoPixel.h>
#include "BattleShip.hpp"

// Definición de pines y configuración de la matriz LED
#define PIN 6            // Pin al que está conectada la matriz LED
#define ANCHO_MATRIZ 16  // Número de columnas en la matriz
#define ALTO_MATRIZ 16   // Número de filas en la matriz
#define NUM_PIXELES 512  // Total de LEDs
#define BRILLO 50        // Brillo de la matriz (0-255)


//Maquina de estados
#define COLOCACION 0
#define TURNO_J1 1
#define TURNO_J2 2
#define FIN_PARTIDA 3

unsigned char estado;

// Configuración de la matriz LED
Adafruit_NeoPixel matriz(NUM_PIXELES, PIN, NEO_GRB + NEO_KHZ800);

// Definición de botones del controlador NES
const int BOTON_A = 0;
const int BOTON_B = 1;
const int BOTON_SELECCION = 2;
const int BOTON_INICIO = 3;
const int BOTON_ARRIBA = 4;
const int BOTON_ABAJO = 5;
const int BOTON_IZQUIERDA = 6;
const int BOTON_DERECHA = 7;

// Configuración de pines del controlador NES
int pinDatosNES = 4;  // Pin para leer datos del controlador
int pinRelojNES = 2;  // Pin de reloj del controlador
int pinLatchNES = 3;  // Pin de latch del controlador

int puntero[2] = { 7, 7 };  //puntero[0] --> Eje x, puntero[1] --> Eje y
bool estaFijado = false;
int pixelIndex;

byte botonesNES;

// Configuración del juego
const int MAX_BARCOS = 5;  // Número máximo de barcos en el juego
Barco barcos[MAX_BARCOS] = { Barco(2, 2), Barco(2, 2), Barco(2, 2), Barco(2, 2), Barco(2, 2) };
int barcoActual = 0;  // Índice del barco que el jugador está controlando

// Configuración de parpadeo
unsigned long ultimoTiempoParpadeo = 0;     // Guarda el tiempo del último parpadeo
bool mostrarBarcoNoFijo = true;             // Determina si se muestra o no el barco no fijado
const unsigned long tiempoEncendido = 400;  // Tiempo que el barco está visible (en milisegundos)
const unsigned long tiempoApagado = 100;    // Tiempo que el barco está invisible

// Función para limpiar la matriz LED (apaga todos los LEDs)
void limpiarMatriz() {
  for (int i = 0; i < NUM_PIXELES; i++) {
    matriz.setPixelColor(i, 0);  // Establece el color negro en cada LED
  }
}

// Configuración inicial del programa
void setup() {
  matriz.begin();                // Inicializa la matriz LED
  matriz.setBrightness(BRILLO);  // Configura el brillo de la matriz
  matriz.show();                 // Aplica los cambios en la matriz LED
  //Serial.begin(9600);
  pinMode(pinDatosNES, INPUT);   // Configura el pin de datos del controlador como entrada
  pinMode(pinRelojNES, OUTPUT);  // Configura el pin de reloj del controlador como salida
  pinMode(pinLatchNES, OUTPUT);  // Configura el pin de latch del controlador como salida
  estado = COLOCACION;
}

// Lee los botones presionados del controlador NES
byte leerNES() {
  digitalWrite(pinLatchNES, HIGH);  // Activa el latch
  delayMicroseconds(12);            // Espera un momento para la lectura
  digitalWrite(pinLatchNES, LOW);   // Desactiva el latch
  byte datos = 0;
  for (int i = 0; i < 8; i++) {
    datos |= (digitalRead(pinDatosNES) << i);  // Lee cada botón y construye el byte
    digitalWrite(pinRelojNES, HIGH);           // Genera un pulso de reloj
    delayMicroseconds(6);
    digitalWrite(pinRelojNES, LOW);
  }
  return ~datos;  // Invierte los bits para obtener los valores correctos
}

void colocar_barcos() {
  if (barcoActual < MAX_BARCOS) {
    if (botonesNES & (1 << BOTON_IZQUIERDA)) barcos[barcoActual].mover(1, 0);  // Mueve a la derecha
    if (botonesNES & (1 << BOTON_DERECHA)) barcos[barcoActual].mover(-1, 0);   // Mueve a la izquierda
    if (botonesNES & (1 << BOTON_ARRIBA)) barcos[barcoActual].mover(0, -1);    // Mueve hacia arriba
    if (botonesNES & (1 << BOTON_ABAJO)) barcos[barcoActual].mover(0, 1);      // Mueve hacia abajo

    // Cambia la forma del barco con el botón de selección
    if (botonesNES & (1 << BOTON_SELECCION)) {
      barcos[barcoActual].formaActual = (barcos[barcoActual].formaActual + 1) % 3;
      barcos[barcoActual].cambiarForma();
    }
    // Rota el barco con el botón A
    if (botonesNES & (1 << BOTON_A)) {
      barcos[barcoActual].rotar();
    }

    // Fija el barco si es posible con el botón B
    if (botonesNES & (1 << BOTON_B)) {
      if (barcos[barcoActual].puedeFijarse()) {
        barcos[barcoActual].fijar();                                   // Marca el barco como fijo
        barcos[barcoActual].dibujar(matriz, matriz.Color(0, 0, 255));  // Lo dibuja en azul
        barcoActual++;                                                 // Cambia al siguiente barco
      }
    }

    // Dibuja el barco actual en verde si no está fijado
    if (mostrarBarcoNoFijo) {
      barcos[barcoActual].dibujar(matriz, matriz.Color(0, 255, 0));  // Verde para barcos no fijados
    }
  }
}

/*bool isLedOn(int index) {
  uint32_t color = matriz.getPixelColor(index);  // Obtiene el color en formato RGB
  uint8_t r = (color >> 16) & 0xFF;              // Extrae el componente rojo
  uint8_t g = (color >> 8) & 0xFF;               // Extrae el componente verde
  uint8_t b = color & 0xFF;                      // Extrae el componente azul

  // Verifica si al menos un canal tiene un valor distinto de cero
  return (r > 0 || g > 0 || b > 0);
}*/

bool atacar() {
  if (!estaFijado) {
    if (botonesNES & (1 << BOTON_IZQUIERDA) && puntero[0] > 0)
      puntero[0]--;
    else if (botonesNES & (1 << BOTON_DERECHA) && puntero[0] < ANCHO_MATRIZ - 1)
      puntero[0]++;
    else if (botonesNES & (1 << BOTON_ARRIBA) && puntero[1] > 0)
      puntero[1]--;
    else if (botonesNES & (1 << BOTON_ABAJO) && puntero[1] < ALTO_MATRIZ - 1)
      puntero[1]++;
    // matriz.clear();  // Limpia todos los LEDs
    else if (botonesNES & (1 << BOTON_A))
      estaFijado = true;

    pixelIndex = ((puntero[1] % 2) ? puntero[1] * ANCHO_MATRIZ + puntero[0] : puntero[1] * ANCHO_MATRIZ + (ANCHO_MATRIZ - 1 - puntero[0]));
    matriz.setPixelColor(pixelIndex + 256, matriz.Color(255, 0, 0));  // Convierte las coordenadas (X, Y) al índice en la matriz en formato serpiente
  } else {
    for(barcoActual = 0; barcoActual < MAX_BARCOS; barcoActual++)
      if (barcos[barcoActual].recibeAtaque(matriz,pixelIndex)) {
        matriz.setPixelColor(pixelIndex, matriz.Color(255, 0, 0));
        matriz.show();
        matriz.setPixelColor(pixelIndex + 256, matriz.Color(0, 255, 0));
        matriz.show();
      }
      estaFijado = false;
      puntero[0] = 7;
      puntero[1] = 7;
  }

  // matriz.show();  // Muestra los cambios en la matriz
  //Dibujarlo por pantalla si se ha movido.
  // int numPixel_p
  // if(puntero_ant[0] != puntero[0] && puntero_ant[1] != puntero[1])
  //   matriz.show();
  // //Actualizar el valor anterior.
  // puntero_ant[0] = puntero[0];
  // puntero_ant[1] = puntero[1];
}



// Bucle principal del programa
void loop() {
  limpiarMatriz();  // Limpia la matriz LED al inicio de cada iteración

  botonesNES = leerNES();  // Lee los botones presionados

  // Control del parpadeo para el barco no fijado
  unsigned long tiempoActual = millis();
  unsigned long intervaloParpadeo = mostrarBarcoNoFijo ? tiempoEncendido : tiempoApagado;
  if (tiempoActual - ultimoTiempoParpadeo >= intervaloParpadeo) {
    ultimoTiempoParpadeo = tiempoActual;
    mostrarBarcoNoFijo = !mostrarBarcoNoFijo;  // Alterna entre visible e invisible
  }

  // Dibuja todos los barcos que ya están fijados
  for (int i = 0; i < barcoActual; i++) {


    barcos[i].dibujar(matriz);  // Los barcos fijados son azules
  }

  // Control del barco actual si aún no se han fijado todos
  /*if (barcoActual < MAX_BARCOS) {
        if (botonesNES & (1 << BOTON_IZQUIERDA)) barcos[barcoActual].mover(1, 0);  // Mueve a la derecha
        if (botonesNES & (1 << BOTON_DERECHA)) barcos[barcoActual].mover(-1, 0);  // Mueve a la izquierda
        if (botonesNES & (1 << BOTON_ARRIBA)) barcos[barcoActual].mover(0, -1);   // Mueve hacia arriba
        if (botonesNES & (1 << BOTON_ABAJO)) barcos[barcoActual].mover(0, 1);     // Mueve hacia abajo

        // Cambia la forma del barco con el botón de selección
        if (botonesNES & (1 << BOTON_SELECCION)) {
            barcos[barcoActual].formaActual = (barcos[barcoActual].formaActual + 1) % 3;
            barcos[barcoActual].cambiarForma();
        }
        // Rota el barco con el botón A
        if (botonesNES & (1 << BOTON_A)) {
            barcos[barcoActual].rotar();
        }

        // Fija el barco si es posible con el botón B
        if (botonesNES & (1 << BOTON_B)) {
            if (barcos[barcoActual].puedeFijarse()) {
                barcos[barcoActual].fijar(); // Marca el barco como fijo
                barcos[barcoActual].dibujar(matriz, matriz.Color(0, 0, 255)); // Lo dibuja en azul
                barcoActual++; // Cambia al siguiente barco
            }
        }

        // Dibuja el barco actual en verde si no está fijado
        if (mostrarBarcoNoFijo) {
            barcos[barcoActual].dibujar(matriz, matriz.Color(0, 255, 0)); // Verde para barcos no fijados
        }
    }*/

  switch (estado) {
    case COLOCACION:
      //Serial.println("COLOCACION");
      colocar_barcos();
      if (barcoActual >= MAX_BARCOS)
        estado = TURNO_J1;
      break;
    case TURNO_J1:
      //Serial.println("TURNO_J1");
      //matriz.setPixelColor(300,matriz.Color(255,0,0));
      //matriz.setPixelColor(300, matriz.Color(255,0,0));  // Convierte las coordenadas (X, Y) al índice en la matriz en formato serpiente


      atacar();
      // if(botonesNES & (1 << BOTON_B))
      //   estado = FIN_PARTIDA;
      // else
      //estado = TURNO_J2;
      break;
    /*case TURNO_J2:
        if(todos_derribados(jugador1))
          estado = TURNO_J1;
        else

      break;*/
    case FIN_PARTIDA:
      //Serial.println("FIN_PARTIDA");
      matriz.setPixelColor(256, matriz.Color(0, 255, 0));
      break;
    default:
      break;
  }

  matriz.show();  // Actualiza la matriz LED con los cambios
  delay(50);      // Pequeña pausa para suavizar el parpadeo
}
