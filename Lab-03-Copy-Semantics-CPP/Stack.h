#pragma once

#include <stddef.h>

class Stack {
  public:
	Stack();
	Stack(const Stack& other);
	Stack& operator=(const Stack& other);
	~Stack();
	void push(int element);
	int pop();
	bool isEmpty() const;

  private:
	bool isFull() const;
	bool growCapacity();
	void copyElementsFrom(const Stack& other);
	void replaceElementsWithCapacity(size_t newCapacity);
	int* elements;
	size_t size;
	size_t capacity;
};
