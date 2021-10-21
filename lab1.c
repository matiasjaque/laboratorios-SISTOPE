
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
  int c;
  opterr = 0;
  printf("hola");

//el siguiente ciclo se utiliza para recibir los parametros de entrada usando getopt
  while ((c = getopt (argc, argv, "N:c")) != -1)
    printf("hola");
    switch (c)
    {
      case 'N':
        sscanf(optarg, "%d", &numero_celdas);
        printf("numero celdas: %d ", numero_celdas);
        break;
      /*case 'i':
        //sscanf(optarg, "%d", &bvalue);
        break; 
      case 'o':
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


