#include "Stack.hpp"

Stack::Stack() {

}

Stack::Stack(int size) { // конструктор
    this->size = size;
    arr = new int[size];
    capacity = -1;
}

Stack::Stack(const Stack& other) { // конструктор копирования
    this->size = other.size;
    this->capacity = other.capacity;
    this->arr = new int[size];
    if (capacity >= 0) {
        for (int i = 0; i < other.capacity; i++) {
            this->arr[i] = other.arr[i];
        }
    }
}

Stack::~Stack() { // деструктор
    delete[] arr;
}

void Stack::push(int value) {
    if (capacity == size - 1) {
        int* new_arr = new int[size * 2 + 1];
        for (int i = 0; i < size; i++) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        this->arr = new_arr;

        for (int i = 0; i < size; i++) {
            arr[i] = new_arr[i];
        }
        size = size * 2 + 1;
    }
    capacity++;
    arr[capacity] = value;
}

void Stack::pop() {
    if (capacity >= 0) {
        //arr[capacity] = 0;
        --capacity;
    }
    else {
        cout << "It's empty";
    }
}

bool Stack::empty() {
    return (capacity == 0);
}

int Stack::top() {
    return arr[capacity - 1];
}