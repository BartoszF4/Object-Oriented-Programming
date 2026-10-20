#include "Stack.h"
#include <iostream>
#include <stdint.h>
#include <stdlib.h>

static const size_t INITIAL_CAPACITY = 4;
static const size_t GROWTH_FACTOR = 2;

Stack::Stack()
{
	elements = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
	size = 0;

	if (elements != nullptr) {
		capacity = INITIAL_CAPACITY;
	}
	else {
		std::cerr << "Stack: incorrect initialization\n";
		exit(EXIT_FAILURE);
	}
}

Stack::~Stack()
{
	free(elements);
}

static bool canGrowFrom(size_t capacity)
{
	return capacity <= SIZE_MAX / GROWTH_FACTOR / sizeof(int);
}

static size_t nextCapacity(size_t capacity)
{
	if (capacity == 0) {
		return INITIAL_CAPACITY;
	}
	return capacity * GROWTH_FACTOR;
}

bool Stack::isFull() const
{
	return size == capacity;
}

bool Stack::growCapacity()
{
	if (!canGrowFrom(capacity)) {
		return false;
	}
	size_t newCapacity = nextCapacity(capacity);
	int* resizedElements = (int*)(realloc(elements, newCapacity * sizeof(int)));
	if (resizedElements == nullptr) {
		return false;
	}
	elements = resizedElements;
	capacity = newCapacity;
	return true;
}

void Stack::push(int element)
{
	if (isFull() && !growCapacity()) {
		std::cerr << "Stack: failed to allocate memory\n";
		exit(EXIT_FAILURE);
	}
	elements[size] = element;
	size++;
}

bool Stack::isEmpty() const
{
	return size == 0;
}

int Stack::pop()
{
	if (isEmpty()) {
		std::cerr << "Stack: pop called on empty stack\n";
		exit(EXIT_FAILURE);
	}
	size--;
	return elements[size];
}
