# Object-Oriented Programming (C++)

This repository contains assignments and projects developed during the 3rd-semester Object-Oriented Programming course. The coursework bridges the gap between procedural memory management in C and advanced object-oriented paradigms in C++.

## Repository Structure

### 📁 [Lab 01 - Dynamic Stack (C)](./Lab-01-Dynamic-Stack-C)
Although the course focuses on C++, the introductory assignment serves as a rigorous recap of C memory management. 
* **Implementation (`Stack.c`, `Stack.h`)**: A dynamically allocating integer stack. The stack intelligently scales its capacity using `malloc` and `realloc` with a predefined growth factor rather than expanding cell-by-cell.
* **Testing Suite (`TestStack.c`)**: A comprehensive, custom test suite verifying LIFO behavior, proper capacity scaling, extreme value preservation, and safe failure handling when memory allocation bounds are exceeded.
* **Memory Safety**: Designed to be entirely leak-free, verified using `valgrind`.

### 📁 [Lab 02 - Dynamic Stack (C++)](./Lab-02-Dynamic-Stack-CPP)
This assignment refactors the procedural C stack from Lab 01 into a proper Object-Oriented C++ class architecture, serving as a transition into C++ paradigms.
* **OOP Refactoring (`Stack.cpp`, `Stack.h`)**: Encapsulates the stack state (elements array, size, capacity) into private member variables. Procedural `init()` and `destroy()` functions are replaced by a C++ `Constructor` and `Destructor` for automatic resource acquisition and release.
* **Memory Management**: Retains the underlying `malloc`/`realloc`/`free` allocation strategy to explicitly demonstrate low-level memory handling within a C++ class context (prior to the introduction of `new` and `delete` operators).
* **Testing Suite (`TestStack.cpp`)**: Extends the testing suite from Lab 01 using C++ syntax (`std::cout`, references) and introduces more exhaustive edge-case testing, including partial popping order verification (`testPushAfterPartialPopKeepsOrder`) and loop-based boundary testing up to specified limits (`testEverySizeUpToLimitWorks`).

---

## Compilation & Execution
You can compile the Lab projects using standard GNU compilers with strict warning flags. For example, to compile Lab 02:

```bash
g++ -g -Wall -pedantic *.cpp -o stack_cpp
./stack_cpp
