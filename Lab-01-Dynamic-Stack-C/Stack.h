#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct
{
    int *elements;
    size_t size;
    size_t capacity;
} Stack;

void init(Stack *s);
void destroy(Stack *s);
void push(Stack *s, int element);
int pop(Stack *s);
bool isEmpty(const Stack *s);