//
// Created by kacper on 14.03.2022.
//

#pragma once

#include <cstdio>
#include <string>

template<typename T>
class DynamicArray {
    //Class variables
    T *head = nullptr;
    size_t size = 0;

public:
    DynamicArray();
    DynamicArray(const DynamicArray<T> &existingArray);
    DynamicArray(int start, int end); //Generate array with elements from start int number to end int number
    ~DynamicArray();

    T at(int index) const;
    T *begin();
    T *end();
    T &operator[](const size_t &index); //Overload of [] operator
    DynamicArray<T> &operator=(DynamicArray<T> other); //Overload of = operator
    bool operator==(DynamicArray<T> other); //Overload of == operator

    void swap(int index1, int index2); //Swap index 1 with index 2
    void addBack(const T &val); //Add val at the end of the table
    void addFront(const T &val); //Add val at the beginning of the table
    void removeBack(); //Remove element from the end of the table
    void removeFront(); //Remove element from the front of the table
    void remove(const size_t &position); //Remove element from the front of the table
    void clear();
    bool contains(T element);
    bool isEmpty();


    //Return curr size of the table
    int getSize() const {
        return this->size;
    }

    void print();
    std::string serialize();
};
