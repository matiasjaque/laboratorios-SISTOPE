
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "Funciones.h"
#include <math.h>


void extern niceprint(int N, float*Energy, float max);



//Entradas: Recibe un argumento de tipo int que indica la cantidad de argumentos que se introduciran
//          por linea de comandos y recibe un arreglo doble de tipo char que almacenara los argumentos
//          que se introduciran por linea de comandos
//Funcionamiento: La funcion main se encarga de calcular el tiempo de ejecucion del programa,
//                ademas de recibir los parametros de entrada usando getopt y guardarlos en variables
//                para luego ser usadas, calcula la energia de cada particula y luego escribe los 
//                resultados en el archivo de salida llamando output.txt como lo solicita el enunciado,
//                ademas el programa puede resolver los errores de entrada de argumentos, gracias al 
//                switch case, el cual contempla los casos bordes.              
//Salidas: La funcion main es de tipo int por lo cual retorna un entero, 0 en este caso por defecto.

int main (int argc, char **argv) {
  time_t start,end;

  time (&start);

  int numero_celdas = 0;
  char nombre_archivo[100];
  printf("argc: %d \n", argc);
  int c;
  opterr = 0;
  printf("hola\n");

  //el siguiente ciclo se utiliza para recibir los parametros de entrada usando getopt
  while ((c = getopt (argc, argv, "N:i:D")) != -1){
      printf("hola2\n");
      switch (c)

      {
        case 'N':

          sscanf(optarg, "%d", &numero_celdas);
          printf("numero celdas: %d \n", numero_celdas);
          //Se crea un arreglo de tamaño la cantidad de celdas
          float * celdas = (float *)malloc(sizeof(float)*numero_celdas);
          //Se vacia el arreglo
          for (size_t i = 0; i < numero_celdas; i++)
          {
            celdas[i] = 0;
          }
          
          break;
        case 'i':

          sscanf(optarg, "%s", nombre_archivo);  
          printf("nombre del archivo: %s \n", nombre_archivo);
          //Se abre el archivo
          FILE *archivo;
          archivo = fopen(nombre_archivo, "r");
          printf("Archivo abierto");
          //Se lee la cantidad de particulas
          int cantidad_particulas = 0;
          fscanf(archivo, "%d", &cantidad_particulas);
          printf("cantidad particulas: %d\n", cantidad_particulas);
          //Se crea una matriz de tamaño 2xcantidad de particulas
          int ** particulas = (int**) malloc(sizeof(int)* 2);
          particulas[0] = (int*)malloc(sizeof(int)*cantidad_particulas);
          particulas[1] = (int*)malloc(sizeof(int)*cantidad_particulas);
          //Se llena la matriz con los datos del archivo
          for (int i = 0; i < cantidad_particulas; i++)
          {
            fscanf(archivo, "%d %d", &particulas[0][i], &particulas[1][i]);
            printf("Posicion: %d, Energia: %d \n",particulas[0][i], particulas[1][i]);
          }
          // Calcular los impactos 
          calcular_impactos(celdas,particulas,numero_celdas,cantidad_particulas);
          //Imprimir resultados (Prueba)
         /* for (int i = 0; i < numero_celdas; i++)
          {
            printf("celda: %d -- energia: %f \n", i, celdas[i]);
          }*/
          //Encontrar el mayor 
          float max = 0;
          int pos_max = -1;
          for (int i = 0; i < numero_celdas; i++)
          {
            if (celdas[i] > max )
            {
              max = celdas [i];
              pos_max = i;
            }
          }
          //printf("%d %f \n", pos_max,max);
          //Generar el archivo de salida
          FILE * archivo_salida;
          archivo_salida = fopen ("output.txt", "w");
          for (int i = -1; i < numero_celdas; i++)
          {
            if(i == -1)
            {
              fprintf(archivo_salida,"%d %f\n", pos_max,max);
            }
            else
            {
            fprintf(archivo_salida, "%d %f\n", i, celdas[i]);
            }        
          }
          
          break; 
        case 'D':
          printf("Hay D\n");
          niceprint(numero_celdas, celdas, max);
          /* for (int i = 0; i < numero_celdas; i++)
          {

            //printf("celda: %d -- energia: %f \n", i, celdas[i]);
          } */
          break;
        case '?':

          if (optopt == 'c'){
            fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
          }
          
          else if (isprint (optopt))
            fprintf (stderr, "Opcion desconocida `-%c'.\n", optopt);
          else
            fprintf (stderr,
                    "Opcion con caracter desconocido `\\x%x'.\n",
                    optopt);
          return 1;
        
        default:
        printf("salida");
          abort ();
      }

  }
  
  //-----------------------------------------------------------------------------------------------------------------

    /* int N=10;
    float* Energy = (float*)malloc(sizeof(float)*N);
    srand((unsigned int)time(NULL));
    for(int i = 0; i<N; i++){
      if (i == 0)
      {
        Energy[i] = 10.0000;
      }
      
      else{
        Energy[i] = (float)rand()/(float)RAND_MAX;
      }
    }
    niceprint(N,Energy, max); */
    

    time (&end);

    double dif = difftime (end,start);
    printf ("El tiempo de ejecucion es %.2lf segundos.", dif );

    return 0;
}


