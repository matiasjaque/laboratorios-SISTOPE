#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "Funciones.h"
#include <math.h>
#include <sys/wait.h>
<<<<<<< Updated upstream
#include <sys/types.h>
<<<<<<< HEAD
=======
#include <ctype.h>

>>>>>>> Stashed changes
=======
#define LECTURA 0
#define ESCRITURA 1
>>>>>>> main




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
  clock_t inicio = clock();

  

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
    printf("Error al abrir el archivo de salida.\n");
    exit(1);
  }
  //Se crea un arreglo de tamaño la cantidad de celdas
  float * celdas = (float *)malloc(sizeof(float)*numero_celdas);

  //Se inicia el arreglo en 0
  for (size_t i = 0; i < numero_celdas; i++)
  {
    celdas[i] = 0;
  }


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
  //Crear un arreglo de pipes para guardar las salidas
  FILE ** salidas = (FILE**)malloc(sizeof(FILE*)*cantidad_procesos);
  for(int i=0;i<cantidad_procesos;i++) 
    {
      //Calcular la linea en la que va el archivo
      if (i <= resto  && i > 0) //Si i es menor o igual al resto y mayor que 0
      {
        linea = linea + division + 1; // Se le suma division + 1 a la linea
      }
      else if (i > 0)
      {
        linea = linea + division; //Si no se le suma la division a la linea
      }
      //Pipe de lectura hijo escritura padre
      int pipedf[2];
      pipe(pipedf);
      //Pipe de escritura hijo lectura padre
      int pipefd[2];
      pipe(pipefd);
      int status;
      int pid;
      pid = fork();
      
      if ( pid < 0 ) {
          perror("Error al crear subproceso");
          exit(1);
      }

      if (pid == 0)
      {
        //Calcular el largo de la division
        length = (int) (log10(division +1 ) + 2);
        char* str = malloc( length + 1 );
        //Cerrar la escritura del hijo en el pipe de solo lectura hijo
        close(pipedf[ESCRITURA]);
        //Cambiar la entrada standar por la lectura del pipe de lectura hijo
        dup2(pipedf[LECTURA],STDIN_FILENO);
        //Cambiar la salida estandar por la salida del pipe de escritura hijo
        dup2(pipefd[ESCRITURA],STDOUT_FILENO);
        //Cerrar la lectura del pipe de solo escritura hijo
        close(pipefd[LECTURA]);
        if (i<resto) //Si el i es < al resto de la division 
        {
          //Convertimos la division + 1 a string
          snprintf(str,length, "%d", division + 1);
        }
        else
        {
          //Convertimos la division + 1 a string
          snprintf(str,length, "%d", division);  
        }
         //pasamos la cantidad de particulas, la cantidad de celdas, la division y el nombre del archivo a los hijos
          execl("./bomb", "./bomb","-p", str,"-N",strCantidadCeldas, "-c",strCantidadLineas,"-i", nombre_archivo,NULL);
          perror("exec ls failed");
          exit(EXIT_FAILURE);
        
      }
      //Cerrar la lectura del pipe de lectura hijo padre escribe
      close(pipedf[LECTURA]);
      //Guardar los procesos como string
      char* strI = malloc( tamanoProcesos + 1 );
      snprintf(strI,tamanoProcesos,"%d", linea);
      printf("hola %d\n",linea);

      //Escribir el tamaño de los procesos al hijo
      write(pipedf[ESCRITURA],strI,tamanoProcesos);
      close(pipedf[ESCRITURA]);

      //Crear un archivo de salida utilizando la salida del pipe
      FILE *salidaHijo;
      if ( !(salidaHijo = fdopen(pipefd[LECTURA], "r")) ) {
        perror("Failed to open streams");
        exit(EXIT_FAILURE);
      }
      //Guardar el archivo de salida en el arreglo de salidas
      salidas[i] = salidaHijo;
    }

    int status;
    //Sumar todas las salidas
    for(int i=0;i<cantidad_procesos;i++)
    {
      //Esperar al hijo
      //wait(&status);
      float f; int pp;
      //Leer la posicion y el valor que retorna el hijo
      while ( 1 == 1 ) {
        int r = fscanf(salidas[i], "%d %f", &pp, &f) ;
        if ( r != 2 ) break;
        
        //Se guarda en el arreglo de celdas
        celdas[pp] = f + celdas[pp];
        //printf("Hijo dice %i: %d %f\n",i , pp, f);
      }
    }


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
          
          
    clock_t fin = clock();

    double tiempo = (double)(fin - inicio)/CLOCKS_PER_SEC;
    printf ("El tiempo de ejecucion es %f segundos.\n", tiempo);

    return 0;
}