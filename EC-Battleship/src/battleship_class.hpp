#ifndef __BATTLESHIP_HPP__
#define __BATTLESHIP_HPP__
class Battleship
{
    public:
    //Constructores.
    Battleship();
    Battleship(unsigned size);
    Battleship(unsigned size, int** possition);
    //Destructor.
    ~Battleship();
    //Métodos
    void mover(int x_increment, int y_increment);
    void rotar();
    //set
    void set_size(unsigned size);
    void set_possition(int* pos[2]);
    void set_hit(bool* hit);
    void set_derribado(bool var_derribado);
    //get
    unsigned get_size();
    int** get_possition();
    bool* get_hit();
    bool get_derribado();

    private:
    unsigned size;      //Tamaño de la pieza.
    int** possition;   //Posición del barco
    bool* hit;          //Booleano para determinar si ha sido golpeado.
    bool derribado;     //Si han derribado un barco

};
#endif