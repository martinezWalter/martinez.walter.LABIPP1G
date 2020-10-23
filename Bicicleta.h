#ifndef BICICLETA_H_INCLUDED
#define BICICLETA_H_INCLUDED

#include "Tipo.h"
#include "Color.h"

struct {
   int id;
   char marca[20];
   int idTipo;
   int idColor;
   float rodado;
} typedef Bicicleta;

int altaBicicleta(Bicicleta* bicicletas, int id, char* marca, int idTipo, int idColor, float rodado, int TAM);
int bajaBicicleta(Bicicleta* bicicletas, int id, int TAM);
int modificarBicicleta(Bicicleta* bicicletas, int id, char* nuevaMarca, int idTipo, int idColor, float rodado,  int TAM);
int listarBicicletas(Bicicleta* bicicletas, Tipo* tipos, Color* colors, int TAM, int TAM_TIPO, int TAM_COLOR);
int findBicicletaById(Bicicleta* bicicletas, int TAM, int id);


#endif // BICICLETA_H_INCLUDED
