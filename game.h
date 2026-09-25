/*
 * game.h
 *
 *  Created on: 25/09/2026
 *      Author: Ernesto Beltran
 */
#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Game {
public:
    int play() {
        int posX = 0;
        int posY = 7; // Inicia abajo a la izquierda
        int baseX = rand() % 8; // Objetivo arriba aleatorio
        int baseY = 0;
        int movimientos = 15;
        char tecla;

        cout << "\n NAVEGACION ESPACIAL " << endl;
        cout << "Mueve tu nave [^] hasta la base (H) usando w, a, s, d" << endl;

        while ((posX != baseX || posY != baseY) && movimientos > 0) {
            // Dibujar el mapa (Matriz 8x8)
            cout << "\nMapa del sector:" << endl;
            for (int y = 0; y < 8; y++) {
                for (int x = 0; x < 8; x++) {
                    if (x == posX && y == posY) {
                        cout << "[^] "; // Jugador
                    } else if (x == baseX && y == baseY) {
                        cout << "(H) "; // Base
                    } else {
                        cout << " .  "; // Espacio
                    }
                }
                cout << endl;
            }

            cout << "Combustible (Movimientos restantes): " << movimientos << endl;
            cout << "Ingresa movimiento (w/a/s/d): ";
            cin >> tecla;

            // Mover segun la tecla
            if (tecla == 'w' || tecla == 'W') posY--;
            else if (tecla == 's' || tecla == 'S') posY++;
            else if (tecla == 'a' || tecla == 'A') posX--;
            else if (tecla == 'd' || tecla == 'D') posX++;

            // Validar limites del mapa (0 a 7)
            if (posX < 0) posX = 0;
            if (posX > 7) posX = 7;
            if (posY < 0) posY = 0;
            if (posY > 7) posY = 7;

            movimientos--;
        }

        // Evaluacion al finalizar la partida
        if (posX == baseX && posY == baseY) {
            // Puntaje basico: Movimientos restantes * 150 + Bono fijo de 1000
            int puntaje = (movimientos * 150) + 1000;
            cout << "\nLlegaste a la base con exito" << endl;
            cout << "Puntaje obtenido: " << puntaje << " pts" << endl;
            return puntaje;
        } else {
            cout << "\nTe quedaste sin movimientos. Mision fallida." << endl;
            return 0;
        }
    }
};

#endif