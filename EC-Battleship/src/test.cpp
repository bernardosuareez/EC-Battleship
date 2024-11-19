#include "battleship_class.hpp"
#include <stdio.h>

#define TAM 3

int main()
{
    Battleship* barco = new Battleship(TAM,0,0);

    printf("Fin de prueba.\n");
    fflush(stdin);
    getchar();

    return 0; 
}