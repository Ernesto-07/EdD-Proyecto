/*
 * scores.h
 *
 *  Created on: 25/09/2026
 *      Author: Ernesto Beltran
 */
#ifndef SCORES_H_
#define SCORES_H_

#include <vector>

using namespace std;

template <class T>
class Sorts {
private:
	// Mejor caso: O(n)
	// Caso promedio: O(n)
	// Peor caso: O(n)
	void mergeArray(vector<T>& A, vector<T>& B, int low, int mid, int high) { // O(n)
		int i_izq = low; // O(1)
		int i_der = mid + 1; // O(1)
		int i_ord = low; // O(1)

		while (i_izq <= mid && i_der <= high) { // O(n)
			if (A[i_izq] >= A[i_der]) { // O(1)
				B[i_ord] = A[i_izq]; // O(1)
				i_izq++; // O(1)
			} else {
				B[i_ord] = A[i_der]; // O(1)
				i_der++; // O(1)
			}
			i_ord++; // O(1)
		}

		while (i_izq <= mid) { // O(n)
			B[i_ord] = A[i_izq]; // O(1)
			i_izq++; // O(1)
			i_ord++; // O(1)
		}
		while (i_der <= high) { // O(n)
			B[i_ord] = A[i_der]; // O(1)
			i_der++; // O(1)
			i_ord++; // O(1)
		}

		for (int i = low; i <= high; i++) { // O(n)
			A[i] = B[i]; // O(1)
		}
	}

	// Mejor caso: O(n log(n))
	// Caso promedio: O(n log(n))
	// Peor caso: O(n log(n))
	void mergeSplit(vector<T>& A, vector<T>& B, int low, int high) { // O(n log(n))
		if (low < high) { // O(1)
			int mitad = (low + high) / 2; // O(1)
			mergeSplit(A, B, low, mitad); // O(log(n))
			mergeSplit(A, B, mitad + 1, high); // O(log(n))
			mergeArray(A, B, low, mitad, high); // O(n)
		}
	}

public:
	// Mejor caso: O(n log(n))
	// Caso promedio: O(n log(n))
	// Peor caso: O(n log(n))
	vector<T> mergeSort(vector<T> source) { // O(n log(n))
		vector<T> v = source; // O(n)
		vector<T> tmp(v.size()); // O(n)
		mergeSplit(v, tmp, 0, v.size() - 1); // O(n log(n))
		return v; // O(1)
	}
};

#endif 