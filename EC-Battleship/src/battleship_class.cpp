#include "battleship_class.hpp"

//Constructores.
Battleship::Battleship()
{
    size = 0;
    possition = nullptr;
    hit = nullptr;
    derribado = false;
}
Battleship::Battleship(unsigned var_size)
{
    size = var_size;
    possition = nullptr;
    hit = nullptr;
    derribado = false;
}
Battleship::Battleship(unsigned var_size, int **var_possition)
{
    size = var_size;
    for (unsigned i = 0; i < 2; i++)
        for (unsigned j = 0; j < size; ++j)
            possition[i][j] = var_possition[i][j];

    for (unsigned i = 0; i < size; i++)
        hit[i] = false;

    derribado = false;
}
//Destructor.
Battleship::~Battleship()
{
    for (unsigned i = 0; i < 2; ++i)
        delete possition[i];

    delete possition;
}
//Métodos
void Battleship::mover(int x_increment, int y_increment)
{
    for (unsigned pos = 0; pos < size; pos++)
        possition[0][pos] += x_increment;

    for (unsigned pos = 0; pos < size; pos++)
        possition[1][pos] += y_increment;
}
void Battleship::rotar()
{
    int temp;
    for(unsigned i = 0; i < size; ++i)
    {
        possition[0][i] = temp;
        possition[0][i] = possition[1][i];
        possition[1][i] = temp;
    }
}
//set
void Battleship::set_size(unsigned var_size){size = var_size;}
void Battleship::set_possition(int **posi)
{
    for(unsigned dim = 0; dim < 2; dim++)
        for(unsigned pos = 0; pos < size; size++)
            possition[dim][pos] = posi[dim][pos];
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
int **Battleship::get_possition(){return possition;}
bool *Battleship::get_hit(){return hit;}
bool Battleship::get_derribado(){return derribado;}