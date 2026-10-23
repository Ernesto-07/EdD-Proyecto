/*
 * main.cpp
 *
 *  Created on: 25/09/2026
 *      Author: Ernesto Beltran
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#include "player.h"
#include "scores.h"
#include "game.h"
#include "historial.h"
#include "busquedas.h"

using namespace std;

const string ARCHIVO = "jugs.txt";

void cargarArchivo(vector<Player>& lista) {
    ifstream archivo(ARCHIVO.c_str());
    if (!archivo.is_open()) {
        return; // Si no existe, se empieza con la lista vacia
    }

    string nombre;
    int puntos;
    while (archivo >> nombre >> puntos) { // O(n)
        lista.push_back(Player(nombre, puntos)); // O(1) amortizado
    }
    archivo.close();
}

int main() {
    srand(time(0));

    vector<Player> listaJugadores;
    Historial historial;
    Game juego;
    int opcion = 0;

    cargarArchivo(listaJugadores);

    while (opcion != 6) {
        cout << "\n MENU PRINCIPAL " << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Ver Leaderboard" << endl;
        cout << "3. Ver Historial reciente" << endl;
        cout << "4. Buscar por puntaje (binaria)" << endl;
        cout << "5. Buscar por nombre (secuencial)" << endl;
        cout << "6. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string nombre;
            cout << "Ingresa tu nombre: ";
            cin >> nombre;

            int puntos = juego.play(); // O(1): maximo 15 movimientos

            Player nuevoJugador(nombre, puntos);
            listaJugadores.push_back(nuevoJugador); // O(1) amortizado
            historial.add(nuevoJugador);            // O(1)

        } else if (opcion == 2) {
            if (listaJugadores.size() == 0) {
                cout << "\nAun no hay jugadores registrados." << endl;
            } else {
                Sorts<Player> ordenador;
                vector<Player> listaOrdenada = ordenador.mergeSort(listaJugadores); // O(n log(n))

                cout << "\n  TABLA DE POSICIONES " << endl;
                for (int i = 0; i < listaOrdenada.size(); i++) { // O(n)
                    cout << i + 1 << ". " << listaOrdenada[i].getName()
                         << " - " << listaOrdenada[i].getScore() << " pts" << endl;
                }
            }

        } else if (opcion == 3) {
            historial.print(); // O(1), maximo 5 elementos

        } else if (opcion == 4) {
            if (listaJugadores.size() == 0) {
                cout << "\nAun no hay jugadores registrados." << endl;
            } else {
                int puntaje;
                cout << "Puntaje a buscar: ";
                cin >> puntaje;

                Sorts<Player> ordenador;
                vector<Player> listaOrdenada = ordenador.mergeSort(listaJugadores); // O(n log(n))

                int pos = bs_rec(listaOrdenada, listaOrdenada.size(), puntaje); // O(log(n))
                if (pos == -1) {
                    cout << "\nNo hay jugadores con " << puntaje << " pts." << endl;
                } else {
                    // Puede haber varios con el mismo puntaje: se buscan los vecinos
                    // Peor caso: O(n) si todos tienen el mismo puntaje
                    int ini = pos;
                    int fin = pos;
                    while (ini > 0 && listaOrdenada[ini - 1].getScore() == puntaje) ini--;
                    while (fin < listaOrdenada.size() - 1 && listaOrdenada[fin + 1].getScore() == puntaje) fin++;

                    cout << "\nJugadores con " << puntaje << " pts:" << endl;
                    for (int i = ini; i <= fin; i++) {
                        cout << "Posicion " << i + 1 << ": " << listaOrdenada[i].getName() << endl;
                    }
                }
            }

        } else if (opcion == 5) {
            if (listaJugadores.size() == 0) {
                cout << "\nAun no hay jugadores registrados." << endl;
            } else {
                string nombre;
                cout << "Nombre a buscar: ";
                cin >> nombre;

                int pos = bs_seq(listaJugadores, listaJugadores.size(), nombre); // O(n)
                if (pos == -1) {
                    cout << "\nNo existe el jugador " << nombre << "." << endl;
                } else {
                    cout << "\n" << listaJugadores[pos].getName() << " - "
                         << listaJugadores[pos].getScore() << " pts" << endl;
                }
            }
        }
    }

    cout << "Gracias por jugar" << endl;
    return 0;
}
