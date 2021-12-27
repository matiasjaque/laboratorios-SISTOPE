#include "Funciones.h"
#include "stdio.h"
#include <unistd.h>
#include <stdlib.h>

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
                break;
            case 'N':
                sscanf(optarg, "%d", &cantidad_celdas);
                break;
            case 'c':
                sscanf(optarg, "%d", &cantidadLineas);
                if(cantidadLineas == 0)
                {
                    fprintf(stderr,"Error al ingresar parametro de c\n");
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
    int * particulas[2];
    particulas[0] = (int*)malloc(sizeof(int)*cantidad_particulas);
    particulas[1] = (int*)malloc(sizeof(int)*cantidad_particulas);

    //Se llena la matriz con los datos del archivo
    int * linea = (int*)malloc(sizeof(int)*2);

    // abrir archivo
    FILE *archivo;
    archivo = fopen(nombre_archivo, "r");

    // leer hasta el final
    int lin = 0;
    int pp = 0;
    while ( fscanf(archivo, "%d %d", &linea[0], &linea[1]) != EOF ) {
        
        // sino si ya pase las lineas que me interesan salgo
        if ( lin >= posicion + cantidad_particulas ) {
            break;
        }
        
        // si estoy en la lineas que me interesan
        if( lin > posicion - 1 )
        {
            // lleno particulas
            particulas[0][pp] = linea[0];
            particulas[1][pp] = linea[1];
            pp++;
        }
        lin++;
    }

    // Validar que pp es 1 o mas
    free(linea);

    // cierro el archivo 
    fclose(archivo);

    // Ejecutar funcion calcular_impactos
    calcular_impactos(celdas, particulas, cantidad_celdas, cantidad_particulas);

    // Escribir el archivo
    for (int i = 0; i < cantidad_celdas; i++)
    {
       fprintf(stdout,"%d %f\n", i,celdas[i]);   
    }


    //Liberar memoria del arreglo de particulas 
    free(particulas[0]);
    free(particulas[1]);

    close(stdout);

    fprintf(stdout,"TERMINE\n");
  
    exit(0);
}