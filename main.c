#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "Bicicleta.h"
#include "Color.h"
#include "Servicio.h"
#include "Cliente.h"

/*OPERACIONES*/
#define ALTA                   1
#define MODIFICAR              2
#define BAJA                   3
#define LISTAR_BICICLETAS      4
#define LISTAR_TIPOS           5
#define LISTAR_COLORES         6
#define LISTAR_SERVICIOS       7
#define INFORMAR_x_COLOR       1
#define INFORMAR_x_TIPO        2
#define INFORMAR_MENOR_RODADO  3
#define INFORMAR_ORDENADO_TIPO 4
#define INFORMAR_x_COLOR_TIPO  5
#define INFORMAR_CANT_COLOR    6
#define SALIR_AL_MENU          7
/*----------*/

#define TAM                 100
#define TAM_TIPO            4
#define TAM_SERVICIO        4
#define TAM_COLOR           5
#define TAM_RODADO           4
#define TAM_CLIENTE         4


float rodados[4] = { 20, 26, 27.5, 29 };

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

Cliente clientes[4] = {{ 0, "Juan", 'h' },
                        { 1, "Erik", 'h' },
                        { 2, "Paola", 'm' },
                        { 3, "Joel", 'h' }};
int operation;
int idAlta = 1;

Bicicleta bicicletas[100] = {};

int main()
{
    Bicicleta bicicleta1 = { 1, "Marca1", 2, 4, 29, 1 };
    Bicicleta bicicleta2 = { 2, "Marca2", 1, 0, 27.5, 2 };
    Bicicleta bicicleta3 = { 3, "Marca3", 0, 1, 20, 3 };
    Bicicleta bicicleta4 = { 4, "Marca4", 1, 1, 20, 0 };
    Bicicleta bicicleta5 = { 5, "Marca5", 0, 1, 20, 3 };
    Bicicleta bicicleta6 = { 6, "Marca6", 3, 4, 27.5, 0 };
    bicicletas[0] = bicicleta1;
    bicicletas[1] = bicicleta2;
    bicicletas[2] = bicicleta3;
    bicicletas[3] = bicicleta4;
    bicicletas[4] = bicicleta5;
    bicicletas[5] = bicicleta6;

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
        system("cls");
        menu();
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
            system("cls");
            listarBicicletas(bicicletas, tipos, colores, clientes, 100, 4, 5, 4);
            informes();
        } else {
            system("cls");
            printf("No hay registros de bicicletas\n");
            printf("\nPresione una tecla para continuar\n");
        }
        getch();
        break;
    case LISTAR_TIPOS:
        system("cls");
        listarTipos();
        printf("\nPresione una tecla para continuar\n");
        getch();
        break;
    case LISTAR_COLORES:
        system("cls");
        listarColores();
        printf("\nPresione una tecla para continuar\n");
        getch();
        break;
    case LISTAR_SERVICIOS:
        system("cls");
        listarServicios();
        printf("\nPresione una tecla para continuar\n");
        getch();
        break;
    default:
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
    int idTipo = -1;
    int idColor = -1;
    int idCliente = -1;
    float rodado;

    if(operacion == MODIFICAR){
        printf("\nIngrese ID: ");
        fflush(stdin);
        scanf("%d", &idToUpdate);
    }

    printf("\nSeleccione Marca(max 20 caracteres): ");
    fflush(stdin);
    gets(marca);

    for(i = 0; i < TAM_TIPO; i++){
        printf("   %d - %s\n", i, tipos[i].descripcion);
    }
    printf("\nSeleccione Tipo(0-3): ");
    fflush(stdin);
    scanf("%d", &idTipo);

    for(i = 0; i < TAM_COLOR; i++){
        printf("   %d - %s\n", i, colores[i].nombreColor);
    }
    printf("\nSeleccione Color(0-4): ");
    fflush(stdin);
    scanf("%d", &idColor);

    printf("\nSeleccione Rodado(20, 26, 27.5, 29): ");
    fflush(stdin);
    scanf("%f", &rodado);

    printf("\nIngrese ID cliente: ");
    fflush(stdin);
    scanf("%d", &idCliente);

    if (findClienteById(clientes, TAM_CLIENTE, idCliente) == 0 &&
        findTipoById(tipos, TAM_TIPO, idTipo) == 0 &&
        findColorById(colores, TAM_COLOR, idColor) == 0){
        switch(operacion){
        case ALTA:
            if (altaBicicleta(bicicletas, idAlta, marca, idTipo, idColor, rodado, idCliente, TAM) == 0){
                printf("\nSe ha realizado el alta exitosamente.\n");
                printf("\nPresione una tecla para continuar\n");
            } else {
                printf("\nNo se ha podido realizar la operacion.\n");
                printf("\nPresione una tecla para continuar\n");
            }
            break;
        case MODIFICAR:
            if(findBicicletaById(bicicletas, TAM, idToUpdate) == 0){
                if (modificarBicicleta(bicicletas, idToUpdate, marca, idTipo, idColor, rodado, idCliente, TAM) == 0 ){
                    printf("\nSe ha realizado la baja exitosamente.\n");
                    printf("\nPresione una tecla para continuar\n");
                } else {
                    printf("\nNo se ha podido realizar la operacion.\n");
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
    } else {
        printf("\n\n\nDatos ingresados no validos\n");
        printf("\nPresione una tecla para continuar\n");
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

/* MUESTRA EL LISTADO DE SERVICIOS */
void listarServicios(){
    int i;
    printf("  ID     DESCRIPCION     PRECIO    \n\n");
    for(i = 0; i < TAM_SERVICIO; i++){
        printf("  %d    %s    %d \n", servicios[i].id, servicios[i].descripcion, servicios[i].precio);
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

void informes(){
    int operation = -1;
    printf("\n\n 1 - Informar por color");
    printf("\n 2 - Informar por tipo");
    printf("\n 3 - Informar por rodado (NO DISP)");
    printf("\n 4 - Informar ordenado por tipo (NO DISP)");
    printf("\n 5 - Informar cantidad por color y tipo (NO DISP)");
    printf("\n 6 - Informar los colores mas utilizados (NO DISP)");
    printf("\n 7 - Salir al menu");
    printf("\n\nSeleccione informe: ");
    fflush(stdin);
    scanf("%d", &operation);

    if(isValidOperation(operation) == 0){
        initFunctionInfo(operation);
    } else {
        printf("\nOpcion no valida\n");
        printf("\nPresione una tecla para continuar\n");
        getch();
        system("cls");
        informes();
    }
}

void initFunctionInfo(int operation){
    int idColor;
    int idTipo;
    int i;
    switch (operation){
    case INFORMAR_x_COLOR:
        for(i = 0; i < TAM_COLOR; i++){
            printf("   %d - %s\n", i, colores[i].nombreColor);
        }
        printf("\nSeleccione Color(0-4): ");
        fflush(stdin);
        scanf("%d", &idColor);

        if(findColorById(colores, TAM_COLOR, idColor) == 0){
            system("cls");
            listarBicicletasPorColor(bicicletas, tipos, colores, clientes, idColor, TAM, TAM_TIPO, TAM_COLOR, TAM_CLIENTE);
            printf("\n\nPresione una tecla para continuar\n");
        } else {
            system("cls");
            printf("No hay registros de bicicletas\n");
            printf("\nPresione una tecla para continuar\n");
        }
        getch();
        break;
    case INFORMAR_x_TIPO:
        for(i = 0; i < TAM_TIPO; i++){
            printf("   %d - %s\n", i, tipos[i].descripcion);
        }
        printf("\nSeleccione Tipo(0-3): ");
        fflush(stdin);
        scanf("%d", &idTipo);

        if(findTipoById(tipos, TAM_TIPO, idTipo) == 0){
            system("cls");
            listarBicicletasPorTipo(bicicletas, tipos, colores, clientes, idTipo, TAM, TAM_TIPO, TAM_COLOR, TAM_CLIENTE);
            printf("\n\nPresione una tecla para continuar\n");
        } else {
            system("cls");
            printf("No hay registros de bicicletas\n");
            printf("\nPresione una tecla para continuar\n");
        }
        getch();
        break;
    case INFORMAR_MENOR_RODADO:
        printf("\nOpcion no disponible\n");
        printf("\nPresione una tecla para continuar\n");
        getch();
        break;
    case INFORMAR_ORDENADO_TIPO:
        printf("\nOpcion no disponible\n");
        printf("\nPresione una tecla para continuar\n");
        getch();
        break;
    case INFORMAR_x_COLOR_TIPO:
        printf("\nOpcion no disponible\n");
        printf("\nPresione una tecla para continuar\n");
        getch();
        break;
    case INFORMAR_CANT_COLOR:
        printf("\nOpcion no disponible\n");
        printf("\nPresione una tecla para continuar\n");
        getch();
        break;
    case SALIR_AL_MENU:
        system("cls");
        menu();
        break;
    default:
        break;
    }
    system("cls");
    listarBicicletas(bicicletas, tipos, colores, clientes, 100, 4, 5, 4);
    informes();
}

int findTipoById(Tipo* tipos, int len, int id){
    int i;
    for(i = 0; i< len; i++){
        if(tipos[i].id == id){
            return 0;
        }
    }
    return -1;
}
int findColorById(Color* colores, int len, int id){
    int i;
    for(i = 0; i< len; i++){
        if(colores[i].id == id){
            return 0;
        }
    }
    return -1;
}
int findRodadoById(float* rodados, int len, int rodado){
    int i;
    for(i = 0; i< len; i++){
        if(rodados[i] == rodado){
            return 0;
        }
    }
    return -1;
}
int findClienteById(Cliente* clientes, int len, int id){
    int i;
    for(i = 0; i< len; i++){
        if(clientes[i].id == id){
            return 0;
        }
    }
    return -1;
}
