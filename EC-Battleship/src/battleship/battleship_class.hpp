#ifndef __BATTLESHIP_HPP__
#define __BATTLESHIP_HPP__
class Battleship
{
    public:
    //Constructores.
    Battleship();
    Battleship(unsigned size);
    Battleship(unsigned var_size, int varEjeX, int varEjeY);
    //Destructor.
    ~Battleship();
    //Métodos
    void mover(int x_increment, int y_increment);

    //set
    void set_size(unsigned size);
    void set_possition(int setEjeX,const int* setEjeY);
    void set_hit(bool* hit);
    void set_derribado(bool var_derribado);
    //get
    unsigned get_size();
    int get_ejeX();
    int* get_ejeY();
    bool* get_hit();
    bool get_derribado();

    private:
    unsigned size;      //Tamaño de la pieza.
    int ejeX;          //Posicion en el eje X del barco.
    int* ejeY;          //Posicion en el eje Y del barco.
    bool* hit;          //Booleano para determinar si ha sido golpeado.
    bool derribado;     //Si han derribado un barco

};
#endif