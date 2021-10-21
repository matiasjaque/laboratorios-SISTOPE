#include <math.h>
#include <stdio.h>
#include "Funciones.h"
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
