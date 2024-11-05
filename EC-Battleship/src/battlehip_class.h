#ifndef __BATTLESHIP_H__
#define __BATTLESHIP_H__

class Battleship
{
    public:
    //Constructores.
    Battlesip();
    Battleship(unsigned size);
    Battleship(unsigned size, int[2]* possition);
    //Destructor.
    ~Battleship();
    //Métodos
    void mover(int x_increment, int y_increment);
    void rotar()
    bool atacar(int x_cord, int y_cord, Battleship other_battleship);
    //set
    void set_size(unsigned size);
    void set_possition(int* pos[2])
    void set_hit(bool* hit);
    //get
    unsigned get_size();
    int[2]* get_possition();
    bool* get_hit();

    private:
    unsigned size;      //Tamaño de la pieza.
    int* possition[2]   //Posición del barco
    bool* hit;          //Booleano para determinar si ha sido golpeado.
    bool derribado;     //Si han derribado un barco

}

#endif