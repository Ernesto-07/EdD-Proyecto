/*
 * historial.h
 *
 *  Created on: 20/10/2026
 *      Author: Ernesto Beltran
 */
#ifndef HISTORIAL_H_
#define HISTORIAL_H_

#include <iostream>
#include "player.h"

using namespace std;

const int MAX_HISTORIAL = 5;

class Historial {
private:
    Player data[MAX_HISTORIAL];
    int head;     // Posicion del primero en la fila 
    int tail;     // Posicion donde se guardara el siguiente
    int counter;  // Cuantos elementos hay en la fila

public:
    Historial() {
        head = 0;
        tail = 0;
        counter = 0;
    }

    bool empty() {
        return counter == 0;
    }

    bool full() {
        return counter == MAX_HISTORIAL;
    }

    // Agrega al final de la fila. Devuelve false si esta llena
    bool enqueue(Player p) {
        if (full()) {
            return false;
        }
        data[tail] = p;
        tail = (tail + 1) % MAX_HISTORIAL;
        counter++;
        return true;
    }

    // Elimina el primero de la fila. Devuelve false si esta vacia
    bool dequeue() {
        if (empty()) {
            return false;
        }
        head = (head + 1) % MAX_HISTORIAL;
        counter--;
        return true;
    }

    // Regresa el primero de la fila (el mas viejo)
    Player front() {
        if (empty()) {
            return Player();
        }
        return data[head];
    }

    void clear() {
        head = 0;
        tail = 0;
        counter = 0;
    }

    // Registra una partida, si la fila esta llena, sale la mas vieja
    void add(Player p) {
        if (full()) {
            dequeue();
        }
        enqueue(p);
    }

    // Imprime de la partida mas vieja a la mas reciente
    void print() {
        if (empty()) {
            cout << "\nAun no hay partidas en el historial." << endl;
            return;
        }

        cout << "\n  ULTIMAS " << MAX_HISTORIAL << " PARTIDAS " << endl;
        int i = head;
        for (int n = 0; n < counter; n++) {
            cout << n + 1 << ". " << data[i].getName()
                 << " - " << data[i].getScore() << " pts" << endl;
            i = (i + 1) % MAX_HISTORIAL;
        }
    }
};

#endif