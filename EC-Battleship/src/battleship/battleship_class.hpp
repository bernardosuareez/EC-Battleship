#ifndef __BATTLESHIP_HPP__
#define __BATTLESHIP_HPP__

#include <Vector.h>


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
    Vector<int> get_ejeX();
    Vector<int> get_ejeY();
    bool get_hit(int pos);
    bool get_derribado();

    private:
    Vector<int> ejeX;
    Vector<int> ejeY;
    Vector<bool> hit;
    bool derribado;

};
#endif