
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "Funciones.h"
#include <math.h>


//Autores:     - Marcela Rivera 
int main (int argc, char **argv) {

  int numero_celdas = 0;
  char nombre_archivo[100];
  printf("argc: %d \n", argc);
  int c;
  opterr = 0;
  printf("hola \n");

//el siguiente ciclo se utiliza para recibir los parametros de entrada usando getopt
while ((c = getopt (argc, argv, "N:i:")) != -1){
    printf("hola \n");
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
        calcular_impactos(celdas,particulas,numero_celdas,cantidad_particulas);
        for (int i = 0; i < numero_celdas; i++)
        {
          printf("celda: %d -- energia: %f \n", i, celdas[i]);
        }
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
        printf("%d %f \n", pos_max,max);
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
      /*case 'o':
        //cvalue = optarg;
        break;*/
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
  /*printf ("avalue = %i, bvalue = %i, cvalue = %s\n",
          avalue, bvalue, cvalue);
 
//-----------------------------------------------------------------------------------------------------------------

  hola();
  
  int N=10;
  float* Energy = (float*)malloc(sizeof(float)*N);
  srand((unsigned int)time(NULL));
  for(int i = 0; i<N; i++){
    Energy[i] = (float)rand()/(float)RAND_MAX;
  }
  niceprint(N,Energy);
  */
  return 0;
}


