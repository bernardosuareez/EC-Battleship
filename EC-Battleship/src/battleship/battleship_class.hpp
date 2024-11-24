#ifndef __BATTLESHIP_HPP__
#define __BATTLESHIP_HPP__

#include <Vector.h>

typedef Vector<int> ejes;

class Battleship
{
    public:
    //Constructores.
    Battleship();
    Battleship(int varEjeX[], int varEjeY[]);
    //Destructor.
    ~Battleship();
    //Métodos
    void mover(int x_increment, int y_increment);
    //set
    void set_hit(bool var_hit, size_t pos);
    void set_derribado(bool var_derribado);
    //get
    ejes get_ejeX();
    ejes get_ejeY();
    bool get_hit(int pos);
    bool get_derribado();
    //Operadores
    Battleship operator=(const Battleship &barco);
    Battleship operator^(const bool &rot);
    Battleship operator+(const int &(vec[]));

    private:
    ejes ejeX;
    ejes ejeY;
    unsigned hit; //No hace falta un vector, con que cuente el numero de golpes basta.
    bool derribado;

};
#endif