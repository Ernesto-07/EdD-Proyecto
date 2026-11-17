/*
 * archivo.h
 * Leer y guardar las partidas en jugs.txt (formato: nombre puntos)
 */
#ifndef ARCHIVO_H_
#define ARCHIVO_H_

#include <fstream>
#include <string>
#include "dlist.h"
#include "player.h"

using namespace std;

const string ARCHIVO = "jugs.txt";

// Carga las partidas del archivo a la lista
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
void cargarArchivo(DList<Player>& lista) {
    ifstream archivo(ARCHIVO.c_str());
    if (!archivo.is_open()) {
        return; // Si no existe se empieza con la lista vacia
    }

    string nombre;
    int puntos;
    while (archivo >> nombre >> puntos) {       // O(n)
        lista.add(Player(nombre, puntos));      // O(1)
    }
    archivo.close();
}

// Guarda todas las partidas de la lista en el archivo
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
void guardarArchivo(DList<Player>& lista) {
    ofstream archivo(ARCHIVO.c_str());
    DListIterator<Player> it(&lista);
    bool hay = it.begin();

    while (hay) {                               // O(n)
        archivo << it().getName() << " " << it().getScore() << endl;
        hay = ++it;
    }
    archivo.close();
}

#endif