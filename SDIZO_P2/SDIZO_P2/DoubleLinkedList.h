#pragma once

template <class T>
class ElemList {									//Helper class which have data and pointer for next and previous value
public:
	ElemList();
	T data;
	ElemList *next, *prev;
};

template <class T>
class DoubleLinkedList {
public:
	DoubleLinkedList();								//Constructor
	~DoubleLinkedList();							//Destructor
	T back();										//Returns the last element in the list
	void pushBack(T data);						//Adds a new element 'data' at the end of the list
	void popBack();									//Removes the last element of the list, and reduces size of the list by 1
	bool isEmpty();									//Returns whether the list is empty(1) or not(0)
	int size();										//Returns the number of elements in the list
	T at(int index);								//Returns element at a specified position
	DoubleLinkedList<T> revert();
	void sort();
	void clear();									//Clear all list

private:
	ElemList<T> *head, *tail;
	int amount;
};

template <class T>
ElemList<T>::ElemList() {	//constructor of helper class.
	next = nullptr;
	prev = nullptr;
}

template <class T>
DoubleLinkedList<T>::DoubleLinkedList() {
	head = nullptr;
	tail = nullptr;
	amount = 0;
}

template <class T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
	clear();	//In destructor we need to clear all data
}

template <class T>
T DoubleLinkedList<T>::back() {
	return tail->data;	// return first element
}

template <class T>
void DoubleLinkedList<T>::pushBack(T data) {
	ElemList<T> * elem = new ElemList<T>;
	elem->data = data;
	elem->prev = tail;	// have pointer to tail in list.
	elem->next = nullptr;

	if (tail != nullptr)
		tail->next = elem;	// add as last element at 0 position
	else
		head = elem;

	tail = elem;	// new element is new tail

	amount++;
}

template <class T>
void DoubleLinkedList<T>::popBack() {
	if (amount == 0)
		return;
	if (tail->prev != nullptr) {
		ElemList<T> * newTail = tail->prev;
		newTail->next = nullptr;
		delete tail;
		tail = newTail;
	}
	else {
		delete tail;
		head = tail = nullptr;
	}
	amount--;
}

template <class T>
bool DoubleLinkedList<T>::isEmpty() {
	if (amount == 0)
		return true;
	else
		return false;
}

template <class T>
int DoubleLinkedList<T>::size() {
	return amount;
}

template <class T>
T DoubleLinkedList<T>::at(int index) {
	int i = 0;
	ElemList<T> *tmp = tail; //Enumerate from beginig of List. Just like an array. from 0 to size
	while (tmp != nullptr){
		if (i == index)
			return tmp->data;
		i++;
		tmp = tmp->prev;
	}
}

template <class T>
void DoubleLinkedList<T>::clear() {	// Pop all elements just to be sure to release all memory
	while (amount > 0) {
		popBack();
	}
}

template <class T>
DoubleLinkedList<T> DoubleLinkedList<T>::revert() {	// Pop all elements just to be sure to release all memory
	DoubleLinkedList<T> reverted;

	for (int i = 0; i < amount; i++)
		reverted.pushBack(at(i));

	return reverted;
}

