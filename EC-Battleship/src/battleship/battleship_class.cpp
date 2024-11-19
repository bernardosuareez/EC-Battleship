#include "battleship_class.hpp"
#include <stdlib.h>
#include <Vector.h>

//Constructores.
Battleship::Battleship() {
  derribado = false;
}

Battleship::Battleship(int varEjeX[], int varEjeY[]) {
  if ( 1) {
    for (size_t i = 0; i < sizeof(varEjeX); ++i) {
      ejeX.push_back(varEjeX[i]);
      ejeY.push_back(varEjeY[i]);
      hit.push_back(false);
    }
    derribado = false;
  }
}
//Destructor.
Battleship::~Battleship() {
}
//Métodos
void Battleship::mover(int x_increment, int y_increment) {
  for (size_t i = 0; i < ejeX.size(); ++i) {
    ejeX.assign(i, ejeX.at(i) + x_increment);
    ejeY.assign(i, ejeY.at(i) + y_increment);
  }
}

//set
void Battleship::set_hit(bool var_hit, size_t pos) {
  hit.assign(pos, var_hit);
}

void Battleship::set_derribado(bool var_derribado) {
  derribado = var_derribado;
}
//get
Vector<int> Battleship::get_ejeX() {
  return ejeX;
}
Vector<int> Battleship::get_ejeY() {
  return ejeY;
}
bool Battleship::get_hit(int pos) {
  return hit.at(pos);
}
bool Battleship::get_derribado() {
  return derribado;
}