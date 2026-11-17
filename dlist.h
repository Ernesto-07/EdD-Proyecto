/*
 * dlist.h
 * Lista doblemente ligada 
 */
#ifndef DLIST_H_
#define DLIST_H_

#include <cstddef>

template <class T> class DList;
template <class T> class DListIterator;

template <class T>
class DLink {
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);

	T value;
	DLink<T> *previous;
	DLink<T> *next;

	friend class DList<T>;
	friend class DListIterator<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
class DList {
public:
	DList();
	DList(const DList<T>&);
	~DList();

	void addFirst(T);
	void add(T);
	int  length() const;
	bool empty() const;
	void clear();
	void operator= (const DList&);

private:
	DLink<T> *head;
	DLink<T> *tail;
	int size;

	friend class DListIterator<T>;
};

// O(1)
template <class T>
DList<T>::DList() {
	head = NULL;
	tail = NULL;
	size = 0;
}

// O(n)
template <class T>
DList<T>::~DList() {
	clear();
}

// O(1)
template <class T>
bool DList<T>::empty() const {
	return size == 0;
}

// O(1)
template <class T>
int DList<T>::length() const {
	return size;
}

// O(1)
template <class T>
void DList<T>::addFirst(T val)  {
	DLink<T> * nuevo_nodo = new DLink<T>(val);

	if (empty()) {
		head = nuevo_nodo;
		tail = nuevo_nodo;
	} else {
		head->previous = nuevo_nodo;
		nuevo_nodo->next = head;
		head = nuevo_nodo;
	}
	size++;
}

// Agrega al final y es O(1) porque tail apunta al ultimo
template <class T>
void DList<T>::add(T val)  {
	if (empty()) {
		addFirst(val);
	} else {
		DLink<T> * nuevo_nodo = new DLink<T>(val);
		nuevo_nodo->previous = tail;
		tail->next = nuevo_nodo;
		tail = nuevo_nodo;
		size++;
	}
}

// O(n)
template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

// O(n)
template <class T>
DList<T>::DList(const DList<T> &source)  {
	DLink<T> *p, *q;

	if (source.empty()) {
		size = 0;
		head = 0;
		tail = 0;
	} else {
		p = source.head;
		head = new DLink<T>(p->value);
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new DLink<T>(p->value, q, 0);
			p = p->next;
			q = q->next;
		}
		tail = q;
		size = source.size;
	}
}

// O(n)
template <class T>
void DList<T>::operator=(const DList<T> &source)  {
	DLink<T> *p, *q;

	if (this == &source) {
		return;
	}

	clear();
	if (source.empty()) {
		size = 0;
		head = 0;
		tail = 0;
	} else {
		p = source.head;
		head = new DLink<T>(p->value);
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new DLink<T>(p->value, q, 0);
			p = p->next;
			q = q->next;
		}
		tail = q;
		size = source.size;
	}
}

template <class T>
class DListIterator {
public:
	DListIterator(DList<T>*);

	bool begin();
	T&   operator() ();
	bool operator++ ();

private:
	DLink<T> *current;
	DList<T> *theList;
};

template <class T>
DListIterator<T>::DListIterator(DList<T> *aList) : theList(aList) {
	begin();
}

// Se pone en el primer elemento y regresa false si la lista esta vacia, O(1)
template <class T>
bool DListIterator<T>::begin() {
	current = theList->head;
	return (current != 0);
}

// Regresa el elemento actual O(1)
template <class T>
T& DListIterator<T>::operator() ()  {
	return current->value;
}

// Avanza al siguiente y regresa false si ya no hay mas, O(1)
template <class T>
bool DListIterator<T>::operator++ () {
	if (current != 0) {
		current = current->next;
	}
	return (current != 0);
}

#endif /* DLIST_H_ */