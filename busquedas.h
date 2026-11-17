/*
 * busquedas.h
 */
#ifndef BUSQUEDAS_H_
#define BUSQUEDAS_H_

#include <iostream>
#include <string>
#include "dlist.h"
#include "player.h"

using namespace std;

// Imprime todas las partidas de un jugador y regresa cuantas encontro
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
int buscarPorNombre(DList<Player>& lista, string nombre) {
    int encontradas = 0;
    DListIterator<Player> it(&lista);
    bool hay = it.begin();

    while (hay) {                                       // O(n)
        if (it().getName() == nombre) {                 // O(1)
            encontradas++;
            cout << encontradas << ". " << it().getScore() << " pts" << endl;
        }
        hay = ++it;
    }
    return encontradas;
}

// La lista recibida debe estar ordenada e imprime la posicion de cada jugador
// con ese puntaje y regresa cuantos encontro
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
int buscarPorPuntaje(DList<Player>& ranking, int puntaje) {
    int encontrados = 0;
    int posicion = 1;
    DListIterator<Player> it(&ranking);
    bool hay = it.begin();

    while (hay) {                                       // O(n)
        if (it().getScore() == puntaje) {               // O(1)
            encontrados++;
            cout << "Posicion " << posicion << ": " << it().getName() << endl;
        }
        posicion++;
        hay = ++it;
    }
    return encontrados;
}

#endif