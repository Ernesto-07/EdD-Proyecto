/*
 * main.cpp
 * Proyecto EdD
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "player.h"
#include "dlist.h"
#include "scores.h"
#include "game.h"
#include "busquedas.h"
#include "archivo.h"

using namespace std;

const int TOP = 10;
const int RECIENTES = 5;

// Lee un numero y vuelve a preguntar si se escribe otra cosa
int leerEntero() {
    int n;
    cin >> n;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Entrada invalida, escribe un numero: ";
        cin >> n;
    }
    return n;
}

int main() {
    srand(time(0));

    DList<Player> listaJugadores;
    Game juego;
    int opcion = 0;

    cargarArchivo(listaJugadores); // O(n)

    while (opcion != 6) {
        cout << "\n MENU PRINCIPAL " << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Ver Leaderboard" << endl;
        cout << "3. Ver Historial reciente" << endl;
        cout << "4. Buscar partidas por nombre" << endl;
        cout << "5. Buscar por puntaje" << endl;
        cout << "6. Salir" << endl;
        cout << "Selecciona una opcion: ";
        opcion = leerEntero();

        if (opcion == 1) {
            string nombre;
            cout << "Ingresa tu nombre: ";
            cin >> nombre;

            int puntos = juego.play();                      // O(1)
            listaJugadores.add(Player(nombre, puntos));     // O(1)
            guardarArchivo(listaJugadores);                 // O(n)

        } else if (opcion == 2) {
            if (listaJugadores.empty()) {
                cout << "\nAun no hay jugadores registrados." << endl;
            } else {
                Sorts<Player> ordenador;
                DList<Player> listaOrdenada = ordenador.mergeSort(listaJugadores); // O(n log(n))

                cout << "\n  TOP " << TOP << " " << endl;
                DListIterator<Player> it(&listaOrdenada);
                bool hay = it.begin();
                int i = 1;
                while (hay && i <= TOP) {                   // O(1)
                    cout << i << ". " << it().getName()
                         << " - " << it().getScore() << " pts" << endl;
                    hay = ++it;
                    i++;
                }
            }

        } else if (opcion == 3) {
            if (listaJugadores.empty()) {
                cout << "\nAun no hay partidas en el historial." << endl;
            } else {
                int saltar = listaJugadores.length() - RECIENTES;
                if (saltar < 0) {
                    saltar = 0;
                }

                cout << "\n  ULTIMAS PARTIDAS (de la mas vieja a la mas reciente) " << endl;
                DListIterator<Player> it(&listaJugadores);
                bool hay = it.begin();
                for (int i = 0; i < saltar; i++) {          // O(n)
                    hay = ++it;
                }
                int n = 1;
                while (hay) {                               // O(1)
                    cout << n << ". " << it().getName()
                         << " - " << it().getScore() << " pts" << endl;
                    hay = ++it;
                    n++;
                }
            }

        } else if (opcion == 4) {
            if (listaJugadores.empty()) {
                cout << "\nAun no hay jugadores registrados." << endl;
            } else {
                string nombre;
                cout << "Nombre a buscar: ";
                cin >> nombre;

                cout << "\nPartidas de " << nombre << ":" << endl;
                int encontradas = buscarPorNombre(listaJugadores, nombre); // O(n)
                if (encontradas == 0) {
                    cout << "No existe el jugador " << nombre << "." << endl;
                }
            }

        } else if (opcion == 5) {
            if (listaJugadores.empty()) {
                cout << "\nAun no hay jugadores registrados." << endl;
            } else {
                cout << "Puntaje a buscar: ";
                int puntaje = leerEntero();

                Sorts<Player> ordenador;
                DList<Player> listaOrdenada = ordenador.mergeSort(listaJugadores); // O(n log(n))

                cout << "\nJugadores con " << puntaje << " pts:" << endl;
                int encontrados = buscarPorPuntaje(listaOrdenada, puntaje);        // O(n)
                if (encontrados == 0) {
                    cout << "No hay jugadores con " << puntaje << " pts." << endl;
                }
            }

        } else if (opcion != 6) {
            cout << "\nOpcion no valida. Elige un numero del 1 al 6." << endl;
        }
    }

    cout << "Gracias por jugar" << endl;
    return 0;
}