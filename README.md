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
* **Testing Suite (`TestStack.cpp`)**: Extends the testing suite from Lab 01 using C++ syntax (`std::cout`, references) and introduces more exhaustive edge-case testing, including partial popping order verification and loop-based boundary testing up to specified limits.

### 📁 [Lab 03 - Copy Semantics & Debugging](./Lab-03-Copy-Semantics-CPP)
This module introduces the "Rule of Three" (Destructor, Copy Constructor, Copy Assignment Operator) to ensure safe deep-copy semantics and prevent dangling pointers or memory leaks during object duplication.
* **Copy Constructor**: Implements a deep copy of the stack elements. Optimized to allocate memory matching exactly the `size` of the source stack, rather than its full allocated `capacity`, to minimize memory footprint.
* **Copy Assignment Operator (`operator=`)**: Implements safe state assignment. Checks for self-assignment (`this == &other`) and reuses existing heap allocations when the target capacity is sufficient, strictly avoiding unnecessary `free()` and `malloc()` calls.
* **Advanced Test Suite (`TestStack.cpp`)**: Comprehensive tests for edge cases: assigning larger to smaller stacks, smaller to larger, handling empty stacks, and verifying self-assignment immunity.
* **GDB Debugging (`DebugDemo.cpp`)**: Analyzes the implicit invocation of copy constructors and assignment operators when passing objects by value versus by reference.

---

## Compilation & Execution
You can compile the Lab projects using standard GNU compilers with strict warning flags. For example, to compile Lab 03:

```bash
g++ -g -Wall -pedantic Stack.cpp TestStack.cpp -o stack_copy_semantics
./stack_copy_semantics
