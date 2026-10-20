#pragma once

#include <stddef.h>

class Stack
{
public:
    Stack();
    ~Stack();
    void push(int element);
    int pop();
    bool isEmpty() const;

private:
    bool isFull() const;
    bool growCapacity();
    int *elements;
    size_t size;
    size_t capacity;
};