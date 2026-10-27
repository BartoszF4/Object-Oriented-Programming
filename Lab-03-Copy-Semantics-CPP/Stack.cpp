#include "Stack.h"
#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const size_t INITIAL_CAPACITY = 4;
static const size_t GROWTH_FACTOR = 2;

static int* allocateElements(size_t count)
{
	if (count == 0) {
		return nullptr;
	}
	int* allocated = (int*)malloc(count * sizeof(int));
	if (allocated == nullptr) {
		std::cerr << "Stack: failed to allocate memory\n";
		exit(EXIT_FAILURE);
	}
	return allocated;
}

Stack::Stack()
{
	elements = allocateElements(INITIAL_CAPACITY);
	size = 0;
	capacity = INITIAL_CAPACITY;
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

Stack::Stack(const Stack& other)
{
	elements = allocateElements(other.size);
	capacity = other.size;
	copyElementsFrom(other);
}

void Stack::copyElementsFrom(const Stack& other)
{
	if (!other.isEmpty()) {
		memcpy(elements, other.elements, other.size * sizeof(int));
	}
	size = other.size;
}

Stack& Stack::operator=(const Stack& other)
{
	if (this == &other) {
		return *this;
	}
	if (other.size > capacity) { 
		replaceElementsWithCapacity(other.size);
	}
	copyElementsFrom(other);
	return *this;
}

void Stack::replaceElementsWithCapacity(size_t newCapacity)
{
	int* newElements = allocateElements(newCapacity);
	free(elements);
	elements = newElements;
	capacity = newCapacity;
}
