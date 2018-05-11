/* 
 * @file main.c
 * @author: Manuel Alférez Ruiz
 * @date 11 de mayo de 2018, 10:00
 * @note Problema 7
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define INFINITO 99999

/**
 * ENUNCIADO DEL PROBLEMA:
 * En una guerra, los ejércitos enemigos han invadido n ciudades. Los servicios 
 * de inteligencia están informados de que en cada una de las ciudades invadidas
 * se encuentran e efectivos enemigos. Para contraatacar, el Grupo de Interven-
 * ción Rápida dispone de n equipos listos para intervenir. Cada uno de ellos 
 * consta de d efectivos completamente equipados y entrenados. Para garantizar el 
 * éxito de la intervención en una ciudad es necesario que se cuenten al menos 
 * con tantos efectivos de defensa como el enemigo. 
 * 
 * Describir e implementar al menos dos estrategias voraces (distintas funciones
 * de selección) que indiquen qué equipo de intervención debe ir a cada ciudad,
 * de forma que se maximice el número de éxitos garantizados. 
 */

int seleccion(int ciudades[], int equipos[], int ciudad_actual, int tam) {
    int equipo = 0; //Equipo a enviar
    if (equipos[equipo] >= ciudades[ciudad_actual]) return equipo;
    else return equipo++;
}

int seleccion2(int ciudades[], int equipos[], int ciudad_actual, int tam) {
    int equipo = 0; //Equipo a enviar
    int i = 0;
    while (i < 5 || i == tam - 1) {
        if (equipos[i] > ciudades[ciudad_actual])
            if (equipos[i] > equipos[equipo])
                equipo = i;
        i++;
    }
    return equipo;
}

int seleccion3(int ciudades[], int equipos[], int ciudad_actual, int tam) {
    int equipo = 0; //Equipo a enviar
    int i = 0;
    int diferencia = INFINITO;
    while (i < tam) {
        if (equipos[i] >= ciudades[ciudad_actual])
                if ((equipos[i] - ciudades[i]) < diferencia) {
                    equipo = i;
                    diferencia= equipos[i] - ciudades[i];
                }
        i++;
    }
    return equipo;
}

void eliminar(int v[], int pos, int n) {
    v[pos] = v[n - 1];
}

int factible(int vector[], int n) {
    if (vector[n - 1] == 0)
        return 1;
    else return 0;
}

int* algoritmoVoraz(int ciudades[], int equipos[], int n) {
    int* S = malloc(n * sizeof (int)); //S es el conjunto solución
    //Inicializamos
    for (int i = 0; i < n; i++) S[i] = 0;
    //Variables
    int tam_S, tam_equipos, ciudad_actual, ele, pos;
    ciudad_actual = 0;
    tam_S = 0;
    tam_equipos = n;

    //Bucle voraz
    while (tam_S != n && tam_equipos != 0) {
        pos = seleccion3(ciudades, equipos, ciudad_actual, tam_equipos);
        ele = equipos[pos];
        eliminar(equipos, pos, tam_equipos);
        tam_equipos--;
        ciudad_actual++;
        if (factible(S, n)) {
            S[tam_S] = ele;
            tam_S++;
        }
    }
    return S;
}

int quienGana(int v[], int w[], int pos) {
    if (w[pos] >= v[pos])
        return 1;
    else return 0;
}

/*
 * @brief Función principal
 * @param argc Número de parámetros por línea de ordenes
 * @param argv Parámetros por líneas de órdenes
 */
int main(int argc, char** argv) {

    int castillos[] = {5, 8, 1, 4, 2, 7, 14, 2};
    int ejercitos[] = {6, 1, 4, 7, 12, 4, 5, 9};

    int num = 8;

    int * solucion = algoritmoVoraz(castillos, ejercitos, num);

    for (int i = 0; i < num; i++) {
        printf("Ciudad: %d vs Ejercito: %d --> WIN: %d\n", castillos[i],
                solucion[i], quienGana(castillos, solucion, i));
    }

    return (EXIT_SUCCESS);
}

