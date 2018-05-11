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

/**
 * @brief Función de selección nº1-> Estrategia: Si el equipo de la posición 
 * inicial es mayor o igual que la ciudad a atacar se envia directamenta, en otro 
 * caso se envia el equipo siguiente
 * 
 * @param ciudades Vector de ciudades invadidas
 * @param equipos Vector de equipos para contraatacar
 * @param ciudad_actual Ciudad a atacar actualmente
 * @param tam Número de equipos disponibles
 * @return Devuelve la posición del equipo a enviar
 */
int seleccion(int ciudades[], int equipos[], int ciudad_actual, int tam) {
    int equipo = 0; //Equipo a enviar
    if (equipos[equipo] >= ciudades[ciudad_actual]) return equipo;
    else return equipo++;
} //seleccion

/**
 * @brief Función de selección nº2-> Estrategia: Hace un búsqueda en 5 equipos
 * y se queda con el equipo con el que se vaya a ganar con más fuerza
 * 
 * @note Por defecto enviará el primer equipo
 * 
 * @param ciudades Vector de ciudades invadidas
 * @param equipos Vector de equipos para contraatacar
 * @param ciudad_actual Ciudad a atacar actualmente
 * @param tam Número de equipos disponibles
 * @return Devuelve la posición del equipo a enviar
 */
int seleccion2(int ciudades[], int equipos[], int ciudad_actual, int tam) {
    int equipo = 0; //Equipo a enviar
    int i = 0;
    while (i < 5 || i == tam - 1) {
        if (equipos[i] > ciudades[ciudad_actual])
            if (equipos[i] > equipos[equipo]) equipo = i;
        i++;
    }
    return equipo;
} //seleccion2

/**
 * @brief Función de selección nº3-> Estrategia: Hace un análisis de todos los
 * equipos disponibles y se envía aquel que se gana con la suficiente fuerza de 
 * manera que no se desperdicie efectivos
 * 
 * @note Por defecto enviará el primer equipo
 * 
 * @param ciudades Vector de ciudades invadidas
 * @param equipos Vector de equipos para contraatacar
 * @param ciudad_actual Ciudad a atacar actualmente
 * @param tam Número de equipos disponibles
 * @return Devuelve la posición del equipo a enviar
 */
int seleccion3(int ciudades[], int equipos[], int ciudad_actual, int tam) {
    int equipo = 0; //Equipo a enviar
    int i = 0;
    int diferencia = INFINITO; //Valor que indicará con que ventaja se gana 
    while (i < tam) {
        if (equipos[i] >= ciudades[ciudad_actual])
            if ((equipos[i] - ciudades[i]) < diferencia) {
                equipo = i;
                diferencia = equipos[i] - ciudades[i];
            }
        i++;
    }
    return equipo;
} // seleccion3

/**
 * @brief Elimina una posición de un vector
 * 
 * @param v Vector
 * @param pos Posición a eliminar
 * @param n Tamaño del Vector
 */
void eliminar(int v[], int pos, int n) {
    v[pos] = v[n - 1];
}

/**
 * @brief Nos informa si es factible añadir un elemento a la solución
 * 
 * @param vector Vector 
 * @param n El tamaño del vector
 * @return Devuelve 1 si es factible añadir otro elemento o 0 en caso contrario
 */
int factible(int vector[], int n) {
    if (vector[n - 1] == 0) return 1;
    else return 0;
}

/**
 * @brief Función voraz
 * 
 * @param ciudades Ciudades a atacar
 * @param equipos Equipos a enviar al ataque de las ciudades
 * @param n El número de equipos 
 * @return Un vector solución con los efectivos que hay que enviar a cada ciudad
 * para maximizar el número de éxitos obtenidos
 */
int* algoritmoVoraz(int ciudades[], int equipos[], int n) {
    int* S = malloc(n * sizeof (int)); //S es el conjunto solución
    //Inicializamos
    for (int i = 0; i < n; i++) S[i] = 0;
    //Variables
    int tam_S = 0, tam_equipos = n, ele, pos;
    //Bucle voraz
    while (tam_S != n && tam_equipos != 0) {
        pos = seleccion3(ciudades, equipos, n - tam_equipos, tam_equipos);
        ele = equipos[pos];
        eliminar(equipos, pos, tam_equipos);
        tam_equipos--;
        if (factible(S, n)) {
            S[tam_S] = ele;
            tam_S++;
        }
    }
    return S;
} //algoritmoVoraz

/**
 * @brief Indica quién ganaría en la batalla entre los efectivos de los equipos 
 * vs efectivos de la ciudad
 * 
 * @param v Vector de ciudades invadidas
 * @param w Vector de equipos para contraatacar
 * @param pos Posición en donde se encuentran los efectivos
 * @return Devuelve 1 si ganan los efectivos del equipo y 0 si lo hacen los 
 * efectivos de la ciudad
 */
int quienGana(int v[], int w[], int pos) {
    if (w[pos] >= v[pos]) return 1;
    else return 0;
} //quienGana

/*
 * @brief Función principal: Presenta un ejemplo sobre el problema. Muestra los
 * efectivos de cada ciudad y los efectivos del equipo enviado. Para cada caso se
 * muestra el resultado de la batalla
 * 
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
} //main

