/*
 * busquedas.h
 *
 *  Created on: 25/09/2026
 *      Author: Ernesto Beltran
 */
#ifndef BUSQUEDAS_H_
#define BUSQUEDAS_H_

#include <vector>
#include <string>
#include "player.h"

using namespace std;

// Regresa la posicion del primer jugador con ese nombre, o -1 si no existe
// Mejor caso: O(1)
// Caso promedio: O(n)
// Peor caso: O(n)
int bs_seq(vector<Player>& arr, int size, string nombre) {
    for (int i = 0; i < size; i++) {                // O(n)
        if (arr[i].getName() == nombre) {           // O(1)
            return i;
        }
    }
    return -1;
}

// La lista debe estar ordenada de mayor a menor puntaje
// Mejor caso: O(1)
// Caso promedio: O(log(n))
// Peor caso: O(log(n))
int bs_aux(vector<Player>& arr, int low, int high, int val) {
    if (low > high) {                               // Caso base: no existe
        return -1;
    }

    int mid = (low + high) / 2;                     // O(1)
    if (arr[mid].getScore() == val) {               // Caso base: encontrado
        return mid;
    } else if (arr[mid].getScore() > val) {
        return bs_aux(arr, mid + 1, high, val);     // Esta ordenada de mayor a menor
    } else {
        return bs_aux(arr, low, mid - 1, val);
    }
}

// Mejor caso: O(1)
// Caso promedio: O(log(n))
// Peor caso: O(log(n))
int bs_rec(vector<Player>& arr, int size, int val) {
    return bs_aux(arr, 0, size - 1, val);
}

#endif