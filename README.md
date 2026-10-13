# Object-Oriented Programming (C++)

This repository contains assignments and projects developed during the 3rd-semester Object-Oriented Programming course. The coursework bridges the gap between procedural memory management in C and advanced object-oriented paradigms in C++.

## Repository Structure

### 📁 [Lab 01 - Dynamic Stack (C)](./Lab-01-Dynamic-Stack-C)
Although the course focuses on C++, the introductory assignment serves as a rigorous recap of C memory management. 
* **Implementation (`Stack.c`, `Stack.h`)**: A dynamically allocating integer stack. The stack intelligently scales its capacity using `malloc` and `realloc` with a predefined growth factor rather than expanding cell-by-cell.
* **Testing Suite (`TestStack.c`)**: A comprehensive, custom test suite verifying LIFO behavior, proper capacity scaling (`testCapacityGrowsWhenStackIsFull`), extreme value preservation, and safe failure handling when memory allocation bounds are exceeded (`testPushFailsSafelyWhenCapacityCannotGrow`).
* **Memory Safety**: Designed to be entirely leak-free, verified using `valgrind`.

#### Compilation
You can compile the Lab 01 project using the GCC compiler with strict warning flags:
```bash
gcc -g -Wall -pedantic *.c -o stack
