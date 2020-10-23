#include "Bicicleta.h"
#include <float.h>

int altaBicicleta(Bicicleta* bicicletas, int id, char* marca, int idTipo, int idColor, float rodado, int TAM){
    int error = -1;
    int indice = buscarLibre(bicicletas, TAM);;
    Bicicleta bicicleta;
    if(indice == -1){
        printf("\nEl sistema esta completo\n");
    } else {
        bicicleta.id = id;
        strcpy(bicicleta.marca, marca);
        bicicleta.idTipo = idTipo;
        bicicleta.idColor = idColor;
        bicicleta.rodado = rodado;

        bicicletas[indice] = bicicleta;
        error = 0;
    }
    return error;
}

int bajaBicicleta(Bicicleta* bicicletas, int id, int TAM){
    int error = -1;
    int i;
    int j;
    for(i = 0; i < TAM; i++){
        if (bicicletas[i].id == id){
            for(j=i;j<TAM;j++){
                bicicletas[j]=bicicletas[j+1];
            }
            TAM--;
            i--;
            error = 0;
        }
    }
    return error;
}

int modificarBicicleta(Bicicleta* bicicletas, int id, char* marca, int idTipo, int idColor, float rodado,  int TAM){
    int error = -1;
    int i;
    for(i = 0; i< TAM ; i++){
        if(bicicletas[i].id == id){
            strcpy(bicicletas[i].marca, marca);
            bicicletas[i].idTipo = idTipo;
            bicicletas[i].idColor = idColor;
            bicicletas[i].rodado = rodado;
            error = 0;
        }
    }
    return error;
}

int listarBicicletas(Bicicleta* bicicletas, Tipo* tipos, Color* colors, int TAM, int TAM_TIPO, int TAM_COLOR){
    int error = -1;
    int i;
    printf("  ID     MARCA    TIPO    COLOR    RODADO\n\n");
    for(i = 0; i < TAM; i++){
        if(bicicletas[i].id > 0){
            error  = 0;
            int idTipo = getTipo(tipos, bicicletas[i].idTipo, TAM_TIPO);
            int idColor = getColor(colors, bicicletas[i].idColor, TAM_COLOR);
            printf("  %d    %s    %s    %s    %2.1lf   \n",
                bicicletas[i].id,
                bicicletas[i].marca,
                tipos[idTipo].descripcion,
                colors[idColor].nombreColor,
                bicicletas[i].rodado);
        }
    }
    return error;
}

int getTipo(Tipo* tipos, int id, int TAM_TIPO){
    int error = -1;
    int i;
    for(i = 0; i < TAM_TIPO; i++){
        if(tipos[i].id == id){
            return i;
        }
    }
    return error;
}

int getColor(Color* colors, int id, int TAM_COLOR){
    int error = -1;
    int i;
    for(i = 0; i < TAM_COLOR; i++){
        if(colors[i].id == id){
            return i;
        }
    }
    return error;
}

int buscarLibre(Bicicleta* bicicletas, int tam){
    int indice = -1;
    int i;
    for(i=0;i<tam;i++){
        if(bicicletas[i].id == 0){
            indice = i;
            break;
        }
    }
    return indice;
}

int findBicicletaById(Bicicleta* bicicletas, int TAM, int id){
    int i;
    for(i = 0; i<TAM; i++){
        if(bicicletas[i].id == id){
            return 0;
        }
    }
    return -1;
}