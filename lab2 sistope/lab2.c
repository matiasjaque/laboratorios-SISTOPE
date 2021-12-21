#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "Funciones.h"
#include <math.h>
#include <sys/wait.h>
#include <sys/types.h>
#define LECTURA 0
#define ESCRITURA 1




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
  char *nombre_archivo = NULL;
  char *nombre_archivoSalida = NULL;
  int c;
  int imprimir = 0;
  int cantidad_procesos = 0;
  int cantidadLineas = 0;
  opterr = 0;

  //el siguiente ciclo se utiliza para recibir los parametros de entrada usando getopt
  while ((c = getopt (argc, argv, "N:p:c:i:o:D")) != -1){
      switch (c)

      {
        case 'N':

          sscanf(optarg, "%d", &numero_celdas);
          if(numero_celdas == 0)
          {
            printf("Error al ingresar parametro de N\n");
            return(1);
          }
          break;
          case 'p':

          sscanf(optarg, "%d", &cantidad_procesos);
          if(cantidad_procesos == 0)
          {
            printf("Error al ingresar parametro de p\n");
            return(1);
          }
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
        case 'o':
          nombre_archivoSalida = optarg;
          break;

        case 'D':
          imprimir = 1;
          break;
        case '?':

          if (optopt == 'i'){
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
        abort ();
      }

  }
  
  //-----------------------------------------------------------------------------------------------------------------
  //Validar Archivo de entrada
  FILE *archivo;
  archivo = fopen(nombre_archivo, "r");
  if (archivo == NULL){
    printf("Error al abrir el archivo \n");
    exit(1);
  }
  //Validar Archivo de salida
  FILE * archivo_salida;
  archivo_salida = fopen (nombre_archivoSalida, "w");
  if (archivo_salida == NULL)
  {
    printf("Error al abrir el archivo de salida.");
    exit(1);
  }
  //Se crea un arreglo de tamaño la cantidad de celdas
  float * celdas = (float *)malloc(sizeof(float)*numero_celdas);

  //Se inicia el arreglo en 0
  for (size_t i = 0; i < numero_celdas; i++)
  {
    celdas[i] = 0;
  }

  
  //Se crea una matriz de tamaño 2xcantidad de particulas
  int ** particulas = (int**) malloc(sizeof(int)* 2);
  particulas[0] = (int*)malloc(sizeof(int)*cantidadLineas);
  particulas[1] = (int*)malloc(sizeof(int)*cantidadLineas);
  //Se llena la matriz con los datos del archivo
  for (int i = 0; i < cantidadLineas; i++)
  {
    fscanf(archivo, "%d %d", &particulas[0][i], &particulas[1][i]);

  }
  fclose(archivo);

  // calcular cantidad de particulas por proceso
  int division = cantidadLineas/cantidad_procesos;
  int resto = cantidadLineas % cantidad_procesos;
  //cantidad de celdas para los hijos
  int length = (int) (log10(numero_celdas) + 2);
  char* strCantidadCeldas = malloc( length + 1 );
  snprintf(strCantidadCeldas,length, "%d", numero_celdas);
  //cantidad lineas para los hijos
  length = (int) (log10(cantidadLineas) + 2);
  char* strCantidadLineas = malloc( length + 1 );
  snprintf(strCantidadLineas,length, "%d",  cantidadLineas);
  //tamaño cantidad de procesos
  int tamanoProcesos = (int) (log10(cantidadLineas) + 2);
  int linea = 0;
for(int i=0;i<cantidad_procesos;i++) 
    {
      if (i < resto + 1 && i > 0)
      {
        linea = linea + division + 1;
      }
      else if (i > 0 )
      {
        linea = linea + division;
      }
      int pipedf[2];
      int pipefd[2];
      char buffer[10000];
      pipe(pipedf);
      pipe(pipefd);
      int status;
      int pid;
      pid = fork();
      if (pid == 0)
      {
        if (i<resto)
        {
          length = (int) (log10(division +1 ) + 2);
          char* str = malloc( length + 1 );
          snprintf(str,length, "%d", division + 1);
          
          close(pipedf[ESCRITURA]);
          dup2(pipedf[LECTURA],STDIN_FILENO);
          dup2(pipefd[ESCRITURA],STDOUT_FILENO);
          close(pipefd[LECTURA]);
          //pasamos la cantidad de particulas y la cantidad de celdas a los hijos
          execl("./bomb", "./bomb","-p", str,"-N",strCantidadCeldas, "-c",strCantidadLineas,"-i", nombre_archivo,NULL);
          perror("exec ls failed");
          exit(EXIT_FAILURE);
        }
        else
        {
          length = (int) (log10(division) + 2);
          char* str2 = malloc( length + 1 );
          snprintf(str2,length, "%d", division);
          close(pipedf[ESCRITURA]);
          dup2(pipedf[LECTURA],STDIN_FILENO);
          dup2(pipefd[ESCRITURA],STDOUT_FILENO);
          close(pipefd[LECTURA]);
          execl("./bomb", "./bomb","-p", str2,"-N",strCantidadCeldas, "-c",strCantidadLineas,"-i", nombre_archivo,NULL);
          perror("exec ls failed");
          exit(EXIT_FAILURE);
        }
        
      }
      else
        {
            close(pipedf[LECTURA]);
            char* strI = malloc( tamanoProcesos + 1 );
            snprintf(strI,tamanoProcesos,"%d", linea);
            write(pipedf[ESCRITURA],strI,tamanoProcesos);
            wait(&status);
            read(pipefd[LECTURA], buffer, 100); //leemos el pipe y lo imprimimos
            printf("Hijo dice: %si: %d\n",buffer,i);
        }

    }
    /* for(int i=0;i<cantidad_procesos;i++) 
    wait(NULL);  */


  //Liberar memoria del arreglo de particulas 
  free(particulas[0]);
  free(particulas[1]);
  free(particulas);

  /* //Encontrar el mayor 
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
  fclose(archivo_salida);
  if(imprimir == 1)
  {
    niceprint(numero_celdas, celdas, max);
    free(celdas);
  }
          
           */
    time (&end);

    double dif = difftime (end,start);
    printf ("El tiempo de ejecucion es %.2lf segundos.\n", dif );

    return 0;
}