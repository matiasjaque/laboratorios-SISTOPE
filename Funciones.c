#include <math.h>
#include <stdio.h>
#include "Funciones.h"

//Entradas: Se recibe un arreglo correspondiente a las celdas,
//          un arreglo doble correspondiente a las particulas con su respectiva energia,
//          la cantidad de celdas y la cantidad de particulas.
//Funcionamiento: La siguiente funcion se encarga de calcular la energia total de cada particula
//                correspondiente al choque de cada particula con todas las celdas.
//Salidas: La salida es de tipo void por lo cual no retorna nada.

void calcular_impactos(float* celdas, int ** particulas, int cantidad_celdas, int cantidad_particulas){
    int cantidad_minima = pow(10,-3)/cantidad_celdas;
    for (int i = 0; i < cantidad_particulas; i++)
    {   
        int posicion = particulas[0][i];
        int energia = particulas[1][i];

        //Si cae por fuera del lado derecho
        if (posicion >= cantidad_celdas)
        {
            for (int j = cantidad_celdas-1; j < 0; j--)
            {
                float energia_depositada = calcular_energia(posicion, energia,j,cantidad_celdas);
                celdas[j] = celdas[j] + energia_depositada;
                if(energia_depositada <= cantidad_minima)
                {
                    j = 0;
                }
            }

        }

        //Si cae dentro o por fuera a la derecha
        else
        {
            for (int j = 0; j < cantidad_celdas; j++)
            {
                float energia_depositada = calcular_energia(posicion, energia,j,cantidad_celdas);
                celdas[j] = celdas[j] + energia_depositada;
                if(energia_depositada <= cantidad_minima && j > posicion)
                {
                    j = cantidad_celdas;
                }
                
            }
            
        }        
    }
    
}

//Entradas: Se recibe la posicion de impacto de la particula que corresponde a j,
//          la energia de la particula que corresponde a energiap,
//          la posicion de la celda que corresponde a i,
//          la cantidad de celdas que son en total que corresponde a n.
//Funcionamiento: La siguiente funcion se encarga de calcular la energia mediante la formula proporcionada
//                por el eneunciado y filtra si la energia es mayor al minimo de energia para que se
//                considere o en caso contrario que la energia no sea mayor a la minima, esta se ignora.
//Salidas: La salida es de tipo float que corresponde a decimales para no perder la precision de los valores
//         y el cual corresponde a la energia calculada de la particula en cierta celda j que impacta con cierta
//         posicion de i que esta recorriendo.
float calcular_energia(int j, int energiap, int i, int n)
{
    float energia = (pow(10,3)*energiap) / (n * sqrt(fabs(j-i)+1));
    if (energia < pow(10,-3)/n)
    {
        return 0;
    }
    else
    {
        return energia;
    }
    
}
