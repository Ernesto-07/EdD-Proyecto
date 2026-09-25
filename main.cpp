/*
 * main.cpp
 *
 *  Created on: 25/09/2026
 *      Author: Ernesto Beltran
 */
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#include "player.h"
#include "scores.h"
#include "game.h"

using namespace std;

int main() {
    srand(time(0));
    
    vector<Player> listaJugadores;
    Game juego;
    int opcion = 0;

    while (opcion != 3) {
        cout << "\n MENU PRINCIPAL " << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Ver Leaderboard" << endl;
        cout << "3. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string nombre;
            cout << "Ingresa tu nombre: ";
            cin >> nombre;

            // Inicia el juego y obtiene la puntuacion alcanzada
            int puntos = juego.play();
            
            // Crea al jugador y lo guarda en la lista
            Player nuevoJugador(nombre, puntos);
            listaJugadores.push_back(nuevoJugador);
            // Uso el push_back para agregar el nuevo jugador al final del vector listaJugadores
            // Si lo necesito usar porque asi es, si no podria generar error de memoria

        } else if (opcion == 2) {
            // Comprueba si la lista no tiene elementos guardados
            if (listaJugadores.size() == 0) {
                cout << "\nAun no hay jugadores registrados." << endl;
            } else {
                // Crea la herramienta para ordenar a los jugadores.
                Sorts<Player> ordenador;
                vector<Player> listaOrdenada = ordenador.mergeSort(listaJugadores);

                cout << "\n  TABLA DE POSICIONES " << endl;
                for (int i = 0; i < listaOrdenada.size(); i++) {
                    cout << i + 1 << ". " << listaOrdenada[i].getName() 
                         << " - " << listaOrdenada[i].getScore() << " pts" << endl;
                }
            }
        }
    }

    cout << "Gracias por jugar" << endl;
    return 0;
}