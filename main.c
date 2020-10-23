#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "Bicicleta.h"
#include "Servicio.h"

#define ALTA                1
#define MODIFICAR           2
#define BAJA                3
#define LISTAR_BICICLETAS   4
#define LISTAR_TIPOS        5
#define LISTAR_COLORES      6
#define LISTAR_SERVICIOS    7

#define TAM                 100
#define TAM_TIPO            4
#define TAM_COLOR           5

double rodados[4] = { 20, 26, 27.5, 29 };

Tipo tipos[4] = {{ 0, "Rutera" },
                { 1, "Carrera" },
                { 2, "Mountain" },
                { 3, "BMX" }};
Color colores[5] = {{ 0, "Gris" },
                { 1, "Negro" },
                { 2, "Blanco" },
                { 3, "Azul" },
                { 4, "Rojo" }};
Servicio servicios[4] = {{ 0, "Limpieza", 250 },
                        { 1, "Parche", 300 },
                        { 2, "Centrado", 400 },
                        { 3, "Cadena", 350 }};
int operation;
int idAlta = 1;

Bicicleta bicicletas[100] = {};

int main()
{
    menu();
    return 0;
}

/* INICIA EL MENU */
void menu(){
    printf("******MENU******\n \n ");
    printf("\n 1 - Alta Bicicleta");
    printf("\n 2 - Modificar Bicicleta");
    printf("\n 3 - Baja Bicicleta");
    printf("\n 4 - Listar Bicicletas");
    printf("\n 5 - Listar Tipos");
    printf("\n 6 - Listar Colores");
    printf("\n 7 - Listar Servicios");
    printf("\n \n Seleccione: ");
    fflush(stdin);
    scanf("%d", &operation);

    if(isValidOperation(operation) == 0){
        initFunction(operation);
    } else {
        printf("\nOpcion no valida\n");
        printf("\nPresione una tecla para continuar\n");
        getch();
    }
}

/* REALIZA LA OPERACION SELECCIONADA DEL MENU */
void initFunction(int operation){
    int idToRemove;
    switch (operation){
    case ALTA:
        inputBicicleta(ALTA);
        idAlta++;
        getch();
        break;
    case MODIFICAR:
        if(isEmpty(bicicletas, TAM) == 0){
            inputBicicleta(MODIFICAR);
        } else {
            system("cls");
            printf("No hay registros de bicicletas\n");
            printf("\nPresione una tecla para continuar\n");
        }
        getch();
        break;
    case BAJA:
        if(isEmpty(bicicletas, TAM) == 0){
            printf("Ingrese ID para completar la baja: ");
            scanf("%d", &idToRemove);
            if (bajaBicicleta(bicicletas, idToRemove, TAM) == 0){
                printf("Se ha realizado la baja exitosamente.\n");
                printf("\nPresione una tecla para continuar\n");
            } else {
                printf("No se ha podido realizar la operacion.\n");
                printf("\nPresione una tecla para continuar\n");
            }
        } else {
            system("cls");
            printf("No hay registros de bicicletas\n");
            printf("\nPresione una tecla para continuar\n");
        }
        getch();
        break;
    case LISTAR_BICICLETAS:
        if(isEmpty(bicicletas, TAM) == 0){
            listarBicicletas(bicicletas, tipos, colores, 100, 4, 5);
            printf("\n\nPresione una tecla para continuar\n");
        } else {
            system("cls");
            printf("No hay registros de bicicletas\n");
            printf("\nPresione una tecla para continuar\n");
        }
        getch();
        break;
    case LISTAR_TIPOS:
        listarTipos();
        printf("\nPresione una tecla para continuar\n");
        getch();
        break;
    case LISTAR_COLORES:
        listarColores();
        printf("\nPresione una tecla para continuar\n");
        getch();
        break;
    case LISTAR_SERVICIOS:
        printf("\nOperacion aun no disponible\n");
        printf("\nPresione una tecla para continuar\n");
        getch();
        break;
    }
    system("cls");
    menu();
}

/* VERIFICA QUE LA OPCION INGRESADA EN EL MENU SEA VALIDA */
int isValidOperation(int operation){
    int error = -1;
    if(!(operation > 7) && !(operation < 1 )){
        error = 0;
    }
    return error;
}

/* REALIZA EL ALTA O MODIFICACION DE UN REGISTRO DE BICICLETA */
void inputBicicleta(int operacion){
    int i;
    int idToUpdate;
    char marca[20];
    int idTipo;
    int idColor;
    float rodado;

    if(operacion == MODIFICAR){
        printf("Ingrese ID: ");
        fflush(stdin);
        scanf("%d", &idToUpdate);
    }

    printf("\nSeleccione Marca(max 20 caracteres): ");
    fflush(stdin);
    gets(marca);

    for(i = 0; i < TAM_TIPO; i++){
        printf("   %d - %s", i, tipos[i].descripcion);
    }
    printf("\nSeleccione Tipo(0-3): ");
    fflush(stdin);
    scanf("%d", &idTipo);

    for(i = 0; i < TAM_COLOR; i++){
        printf("   %d - %s", i, colores[i].nombreColor);
    }
    printf("\nSeleccione Color(0-4): ");
    fflush(stdin);
    scanf("%d", &idColor);

    printf("\nSeleccione Rodado(20, 26, 27.5, 29): ");
    fflush(stdin);
    scanf("%f", &rodado);

    switch(operacion){
    case ALTA:
        if (altaBicicleta(bicicletas, idAlta, marca, idTipo, idColor, rodado, TAM) == 0){
            printf("Se ha realizado la baja exitosamente.\n");
            printf("\nPresione una tecla para continuar\n");
        } else {
            printf("No se ha podido realizar la operacion.\n");
            printf("\nPresione una tecla para continuar\n");
        }
        break;
    case MODIFICAR:
        if(findBicicletaById(bicicletas, TAM, idToUpdate) == 0){
            if (modificarBicicleta(bicicletas, idToUpdate, marca, idTipo, idColor, rodado, TAM) == 0 ){
                printf("Se ha realizado la baja exitosamente.\n");
                printf("\nPresione una tecla para continuar\n");
            } else {
                printf("No se ha podido realizar la operacion.\n");
                printf("\nPresione una tecla para continuar\n");
            }
        } else {
            printf("\nID no valido\n");
            printf("\nPresione una tecla para continuar\n");
        }
        break;
    default:
        break;
    }
}

/* MUESTRA EL LISTADO DE TIPOS */
void listarTipos(){
    int i;
    printf("  ID     DESCRIPCION    \n\n");
    for(i = 0; i < TAM_TIPO; i++){
        printf("  %d    %s \n", tipos[i].id, tipos[i].descripcion);
    }
}

/* MUESTRA EL LISTADO DE COLORES */
void listarColores(){
    int i;
    printf("  ID     COLOR    \n\n");
    for(i = 0; i < TAM_COLOR; i++){
        printf("  %d    %s \n", colores[i].id, colores[i].nombreColor);
    }
}

/* VERIFICA QUE EL LISTADO DE BICICLETAS NO ESTE VACIO */
int isEmpty(Bicicleta* bicicletas, int len){
    int isEmpty = -1;
    int i;
    for(i = 0; i< len ; i++){
        if(bicicletas[i].id > 0){
            isEmpty = 0;
        }
    }
    return isEmpty;
}
