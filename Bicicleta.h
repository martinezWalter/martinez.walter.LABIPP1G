#ifndef BICICLETA_H_INCLUDED
#define BICICLETA_H_INCLUDED

#include "Tipo.h"
#include "Color.h"
#include "Cliente.h"

struct {
   int id;
   char marca[20];
   int idTipo;
   int idColor;
   float rodado;
   int idCliente;
} typedef Bicicleta;

int altaBicicleta(Bicicleta* bicicletas, int id, char* marca, int idTipo, int idColor, float rodado, int idCliente, int TAM);
int bajaBicicleta(Bicicleta* bicicletas, int id, int TAM);
int modificarBicicleta(Bicicleta* bicicletas, int id, char* nuevaMarca, int idTipo, int idColor, float rodado, int idCliente,  int TAM);
int listarBicicletas(Bicicleta* bicicletas, Tipo* tipos, Color* colors, Cliente* clientes, int TAM, int TAM_TIPO, int TAM_COLOR, int TAM_CLIENTE);
int listarBicicletasPorColor(Bicicleta* bicicletas, Tipo* tipos, Color* colors, Cliente* clientes, int idColor, int TAM, int TAM_TIPO, int TAM_COLOR, int TAM_CLIENTE);
int listarBicicletasPorTipo(bicicletas, tipos, colores, clientes, idTipo, TAM, TAM_TIPO, TAM_COLOR, TAM_CLIENTE);
int findBicicletaById(Bicicleta* bicicletas, int TAM, int id);
int getCliente(Cliente* clientes, int id, int TAM_CLIENTE);
int getColor(Color* colors, int id, int TAM_COLOR);
int getTipo(Tipo* tipos, int id, int TAM_TIPO);

#endif // BICICLETA_H_INCLUDED
