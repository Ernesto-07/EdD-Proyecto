/*
 * scores.h
 */
#ifndef SCORES_H_
#define SCORES_H_

#include "dlist.h"

using namespace std;

template <class T>
class Sorts {
private:
	// Mezcla dos listas que ya estan ordenadas en una lista nueva
	// Mejor caso: O(n)
	// Caso promedio: O(n)
	// Peor caso: O(n)
	DList<T> mergeList(DList<T>& izq, DList<T>& der) {
		DList<T> resultado;
		DListIterator<T> i(&izq);
		DListIterator<T> d(&der);
		bool hayI = i.begin();
		bool hayD = d.begin();

		while (hayI && hayD) {              // O(n)
			if (i() >= d()) {               // O(1)
				resultado.add(i());         // O(1)
				hayI = ++i;
			} else {
				resultado.add(d());         // O(1)
				hayD = ++d;
			}
		}
		while (hayI) {                      // O(n)
			resultado.add(i());
			hayI = ++i;
		}
		while (hayD) {                      // O(n)
			resultado.add(d());
			hayD = ++d;
		}
		return resultado;
	}

	// Divide la lista a la mitad, ordena cada mitad y las mezcla
	// Mejor caso: O(n log(n))
	// Caso promedio: O(n log(n))
	// Peor caso: O(n log(n))
	DList<T> mergeSplit(DList<T>& lista) {
		int n = lista.length();
		if (n <= 1) {
			return lista;
		}

		DList<T> izq;
		DList<T> der;
		DListIterator<T> it(&lista);
		int mitad = n / 2;

		for (int k = 0; k < mitad; k++) {   // O(n)
			izq.add(it());
			++it;
		}
		for (int k = mitad; k < n; k++) {   // O(n)
			der.add(it());
			++it;
		}

		DList<T> ordIzq = mergeSplit(izq);  // O(n/2 log(n/2))
		DList<T> ordDer = mergeSplit(der);  // O(n/2 log(n/2))
		return mergeList(ordIzq, ordDer);   // O(n)
	}

public:
	// Mejor caso: O(n log(n))
	// Caso promedio: O(n log(n))
	// Peor caso: O(n log(n))
	DList<T> mergeSort(DList<T>& lista) {
		return mergeSplit(lista);
	}
};

#endif