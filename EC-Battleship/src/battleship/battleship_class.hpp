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
    void mover(const int &x_increment,const int &y_increment);
    //set
    void set_hit(const unsigned &var_hit);
    void set_derribado(const bool &var_derribado);
    //get
    ejes get_ejeX();
    ejes get_ejeY();
    unsigned get_hit();
    bool get_derribado();
    size_t get_size();
    //Operadores
    Battleship operator=(const Battleship &barco);
    Battleship operator^(const bool &rot);
    Battleship operator+(int vec[]);

    private:
    ejes ejeX;
    ejes ejeY;
    unsigned hit; //No hace falta un vector, con que cuente el numero de golpes basta.
    bool derribado;

};
#endif