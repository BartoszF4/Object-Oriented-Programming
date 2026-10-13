#include "Stack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 4
#define GROWTH_FACTOR 2

void init(Stack* s)
{
	s->elements = malloc(INITIAL_CAPACITY * sizeof(int));
	s->size = 0;
	s->capacity = 0;
	if (s->elements != NULL) {
		s->capacity = INITIAL_CAPACITY;
	}
}

void destroy(Stack* s)
{
	free(s->elements);
}

static bool isFull(const Stack* s)
{
	return s->size == s->capacity;
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

static bool growCapacity(Stack* s)
{
	if (!canGrowFrom(s->capacity)) {
		return false;
	}
	size_t newCapacity = nextCapacity(s->capacity);
	int* resizedElements = realloc(s->elements, newCapacity * sizeof(int));
	if (resizedElements == NULL) {
		return false;
	}
	s->elements = resizedElements;
	s->capacity = newCapacity;
	return true;
}

void push(Stack* s, int element)
{
	if (isFull(s) && !growCapacity(s)) {
		fprintf(stderr, "Stack: failed to allocate memory\n");
		return;
	}
	s->elements[s->size] = element;
	s->size++;
}

bool isEmpty(const Stack* s)
{
	return s->size == 0;
}

int pop(Stack* s)
{
	if (isEmpty(s)) {
		fprintf(stderr, "Stack: pop called on empty stack\n");
		exit(EXIT_FAILURE);
	}
	s->size--;
	return s->elements[s->size];
}
