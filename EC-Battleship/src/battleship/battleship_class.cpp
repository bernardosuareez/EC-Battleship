#include "battleship_class.hpp"
#include <stdlib.h>
#include <Vector.h>

//Constructores.
Battleship::Battleship() {
  derribado = false;
  hit = 0;
}

Battleship::Battleship(int varEjeX[], int varEjeY[]) {
  
    for (size_t i = 0; i < sizeof(varEjeX); ++i) {
      ejeX.push_back(varEjeX[i]);
      ejeY.push_back(varEjeY[i]);
    }
    derribado = false;
    hit = 0;
  
}
//Destructor.
Battleship::~Battleship() {
}
//Métodos
void Battleship::mover(const int &x_increment,const int &y_increment) {
  for (size_t i = 0; i < ejeX.size(); ++i) {
    ejeX.assign(i, ejeX.at(i) + x_increment);
    ejeY.assign(i, ejeY.at(i) + y_increment);
  }
}

//set
void Battleship::set_hit(const unsigned &var_hit) {
  hit = var_hit;
}

void Battleship::set_derribado(const bool &var_derribado) {
  derribado = var_derribado;
}
//get
ejes Battleship::get_ejeX() {
  return ejeX;
}
ejes Battleship::get_ejeY() {
  return ejeY;
}
unsigned Battleship::get_hit() {
  return hit;
}
bool Battleship::get_derribado() {
  return derribado;
}
size_t Battleship::get_size()
{
  return ejeX.size();
}

//Operadores
//Este operador es el de asignación, nada fuera de lo común.
Battleship Battleship::operator=(const Battleship &barco)
{
  Battleship* nuevo_barco = new Battleship();
  nuevo_barco->ejeX = barco.ejeX;
  nuevo_barco->ejeY = barco.ejeY;
  nuevo_barco->derribado = barco.derribado;
  nuevo_barco->hit = barco.hit;
  return *nuevo_barco;
}
// Este operador será el de rotación, en principio no necesita valores ya que la rotación
// es simetrica respecto a la diagonal por la forma de los barcos, pero si se decide añadir
// formas más complejas se puede añadir una variable booleana para determinar el giro de la rotación
// (izq o derecha), por lo que habría que modificarla en un futuro, pero la forma que tendría será
// bool rot; //(rot = false --> izq; rot = true --> der)
// nuevo_barco = (barco^rot); //El parentesis no es necesario, pero no viene mal ponerlo.
Battleship Battleship::operator^(const bool &rot)
{
  Battleship* nuevo_barco = new Battleship();
}

// Suma el incremento en ambos ejes, es una forma alternativa a la funcion mover.
// Vec contiene lo que en la función mover equivale a x_increment e y_increment.
Battleship Battleship::operator+(int vec[]) // vec[0] --> x_increment; vec[1] --> y_increment;
{
  Battleship* nuevo_barco = new Battleship();
  size_t tam = (this->ejeX).size();
  for(size_t i = 0; i < tam; ++i)
  {
    (nuevo_barco->ejeX).push_back((this->ejeX)[i]+vec[0]);
    (nuevo_barco->ejeY).push_back((this->ejeY)[i]+vec[1]);
  }
  nuevo_barco->hit = this->hit;
  nuevo_barco->derribado = this->derribado;
  return *nuevo_barco;
}