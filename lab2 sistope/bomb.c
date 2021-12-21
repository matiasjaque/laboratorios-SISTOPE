#include "Funciones.h"
#include "stdio.h"
#include <unistd.h>
#include <stdlib.h>

void hola() {
    printf("hola");
}
int main (int argc, char **argv){
    int c;
    int cantidad_particulas = 0;
    int cantidad_celdas = 0;
    int cantidadLineas = 0 ;
    char * nombre_archivo;
    while ((c = getopt (argc, argv, "p:N:c:i:")) != -1){
        switch (c)
        {
            case 'p':
                sscanf(optarg, "%d", &cantidad_particulas);
                printf("particulas: %d ",cantidad_particulas);
                break;
            case 'N':
                sscanf(optarg, "%d", &cantidad_celdas);
                printf("celdas: %d \n",cantidad_celdas);
                break;
            case 'c':
                sscanf(optarg, "%d", &cantidadLineas);
                if(cantidadLineas == 0)
                {
                    printf("Error al ingresar parametro de c\n");
                    return(1);
                }
                break;
            case 'i':
                nombre_archivo = optarg;
                break;
            


        }
    }
    int posicion;
    scanf("%d",&posicion);
    //Se crea un arreglo de tamaño la cantidad de celdas
    float * celdas = (float *)malloc(sizeof(float)*cantidad_celdas);

    //Se inicia el arreglo en 0
    for (size_t i = 0; i < cantidad_celdas; i++)
    {
        celdas[i] = 0;
    }
    //Se crea una matriz de tamaño 2xcantidad de particulas
    int ** particulas = (int**) malloc(sizeof(int)* 2);
    particulas[0] = (int*)malloc(sizeof(int)*cantidad_particulas);
    particulas[1] = (int*)malloc(sizeof(int)*cantidad_particulas);
    FILE *archivo;
    archivo = fopen(nombre_archivo, "r");
    //Se llena la matriz con los datos del archivo
    char line[256]; /* or other suitable maximum line size */
    int count = 0;
    int particula = 0 ;
    int * caca = (int*)malloc(sizeof(int)*2);
    for (int i = 0; i < posicion + cantidad_particulas; i++)
    {
        if( i > posicion - 1 )
        {
            fscanf(archivo, "%d %d", &particulas[0][i], &particulas[1][i]);
            printf("real: %d %d\n",particulas[0][i], particulas[1][i]);
        }
        else
        {
            fscanf(archivo, "%d %d", &caca[0], &caca[1]);
            printf("caca: %d %d\n", caca[0], caca[1]);
        }

    }
    for (int i = 0; i < cantidad_particulas; i++)
    {
        printf("oficial: %d %d\n",particulas[0][i], particulas[1][i]);
    }
    
    fclose(archivo);
    return 0;
}