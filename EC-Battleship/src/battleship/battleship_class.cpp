#include "battleship_class.hpp"
#include <stdio.h>

//Constructores.
Battleship::Battleship()
{
    size = 0;
    ejeX = 0;
    ejeY = nullptr;
    hit = nullptr;
    derribado = false;
}
Battleship::Battleship(unsigned var_size)
{
    size = var_size;
    ejeX = 0;
    ejeY = nullptr;
    hit = nullptr;
    derribado = false;
}
Battleship::Battleship(unsigned var_size, int varEjeX, int varEjeY)
{
    size = var_size;
    ejeX = varEjeX;
    
    for(unsigned i = 0; i < size; ++i)
    {
        ejeY[i] = varEjeY;
        printf("&d\n",ejeY[i]);
        ++varEjeY;
    }

    for (unsigned i = 0; i < size; i++)
        hit[i] = false;

    derribado = false;
}
//Destructor.
Battleship::~Battleship()
{
}
//Métodos
void Battleship::mover(int x_increment, int y_increment)
{
    ejeX = x_increment;

    for(unsigned i = 0; i < size; ++i)
        ejeY[i] += y_increment;
}

//set
void Battleship::set_size(unsigned var_size){size = var_size;}
void Battleship::set_possition(int setEjeX,const int* setEjeY)
{
    ejeX = setEjeX;
    for(unsigned i = 0; i < size; ++i)
        ejeY[i] = setEjeY[i];
}
void Battleship::set_hit(bool *var_hit)
{
    for(unsigned pos = 0; pos < size; pos++)
        hit[pos] = var_hit;
}

void Battleship::set_derribado(bool var_derribado)
{
    derribado = var_derribado;
}
//get
unsigned Battleship::get_size(){return size;}
int Battleship::get_ejeX(){return ejeX;}
int* Battleship::get_ejeY(){return ejeY;}
bool *Battleship::get_hit(){return hit;}
bool Battleship::get_derribado(){return derribado;}