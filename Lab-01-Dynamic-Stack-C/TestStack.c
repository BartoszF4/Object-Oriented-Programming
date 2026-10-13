#include "Stack.h"
#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#define FIRST_VALUE 1
#define SECOND_VALUE 2
#define THIRD_VALUE 3
#define ZERO_VALUE 0
#define MANY_ELEMENTS_COUNT 1000
#define PASS_MESSAGE_FORMAT "PASS: %s\n"

static void reportPassed(const char* testName)
{
	printf(PASS_MESSAGE_FORMAT, testName);
}

static void assertPopReturns(Stack* stack, int expectedValue)
{
	int popped = pop(stack);
	assert(popped == expectedValue);
}

static void pushRange(Stack* stack, size_t count)
{
	for (size_t index = 0; index < count; index++) {
		push(stack, (int)index);
	}
}

static void assertPopsRangeInReverse(Stack* stack, size_t count)
{
	for (size_t index = count; index > 0; index--) {
		assertPopReturns(stack, (int)(index - 1));
	}
}

void testStackIsEmptyAfterInit()
{
	Stack stack;
	init(&stack);
	assert(isEmpty(&stack));
	assert(stack.size == 0);
	assert(stack.capacity > 0);
	destroy(&stack);
	reportPassed("testStackIsEmptyAfterInit");
}

void testStackIsNotEmptyAfterPush()
{
	Stack stack;
	init(&stack);
	push(&stack, FIRST_VALUE);
	assert(!isEmpty(&stack));
	destroy(&stack);
	reportPassed("testStackIsNotEmptyAfterPush");
}

void testPopReturnsPushedElement()
{
	Stack stack;
	init(&stack);
	push(&stack, FIRST_VALUE);
	assertPopReturns(&stack, FIRST_VALUE);
	destroy(&stack);
	reportPassed("testPopReturnsPushedElement");
}

void testLIFO()
{
	Stack stack;
	init(&stack);
	push(&stack, FIRST_VALUE);
	push(&stack, SECOND_VALUE);
	push(&stack, THIRD_VALUE);
	assertPopReturns(&stack, THIRD_VALUE);
	assertPopReturns(&stack, SECOND_VALUE);
	assertPopReturns(&stack, FIRST_VALUE);
	destroy(&stack);
	reportPassed("testLIFO");
}

void testIsStackEmptyAfterPoppingAllItems()
{
	Stack stack;
	init(&stack);
	push(&stack, FIRST_VALUE);
	push(&stack, SECOND_VALUE);
	assertPopReturns(&stack, SECOND_VALUE);
	assertPopReturns(&stack, FIRST_VALUE);
	assert(isEmpty(&stack));
	destroy(&stack);
	reportPassed("testIsStackEmptyAfterPoppingAllItems");
}

void testPushBeyondInitialCapacityKeepsAllElements()
{
	Stack stack;
	init(&stack);
	pushRange(&stack, MANY_ELEMENTS_COUNT);
	assertPopsRangeInReverse(&stack, MANY_ELEMENTS_COUNT);
	assert(isEmpty(&stack));
	destroy(&stack);
	reportPassed("testPushBeyondInitialCapacityKeepsAllElements");
}

void testCapacityIsNeverSmallerThanSize()
{
	Stack stack;
	init(&stack);
	for (size_t index = 0; index < MANY_ELEMENTS_COUNT; index++) {
		push(&stack, (int)index);
		assert(stack.capacity >= stack.size);
	}
	destroy(&stack);
	reportPassed("testCapacityIsNeverSmallerThanSize");
}

void testCapacityGrowsWhenStackIsFull()
{
	Stack stack;
	init(&stack);
	size_t capacityBefore = stack.capacity;
	pushRange(&stack, capacityBefore + 1);
	assert(stack.capacity > capacityBefore);
	destroy(&stack);
	reportPassed("testCapacityGrowsWhenStackIsFull");
}

void testExtremeValuesArePreserved()
{
	Stack stack;
	init(&stack);
	push(&stack, INT_MAX);
	push(&stack, INT_MIN);
	push(&stack, ZERO_VALUE);
	assertPopReturns(&stack, ZERO_VALUE);
	assertPopReturns(&stack, INT_MIN);
	assertPopReturns(&stack, INT_MAX);
	destroy(&stack);
	reportPassed("testExtremeValuesArePreserved");
}

void testPushFailsSafelyWhenCapacityCannotGrow()
{
	Stack stack;
	init(&stack);
	size_t capacityBefore = stack.capacity;
	stack.size = SIZE_MAX;
	stack.capacity = SIZE_MAX;
	push(&stack, FIRST_VALUE);
	assert(stack.size == SIZE_MAX);
	assert(stack.capacity == SIZE_MAX);
	stack.size = 0;
	stack.capacity = capacityBefore;
	destroy(&stack);
	reportPassed("testPushFailsSafelyWhenCapacityCannotGrow");
}

void testMultipleStack()
{
	Stack stack1;
	Stack stack2;
	Stack stack3;
	init(&stack1);
	init(&stack2);
	init(&stack3);
	push(&stack1, FIRST_VALUE);
	push(&stack1, SECOND_VALUE);
	push(&stack2, FIRST_VALUE);
	push(&stack3, FIRST_VALUE);
	destroy(&stack1);
	destroy(&stack2);
	destroy(&stack3);
	reportPassed("testMultipleStack");
}

int main()
{
	testStackIsEmptyAfterInit();
	testStackIsNotEmptyAfterPush();
	testPopReturnsPushedElement();
	testLIFO();
	testIsStackEmptyAfterPoppingAllItems();
	testPushBeyondInitialCapacityKeepsAllElements();
	testCapacityIsNeverSmallerThanSize();
	testCapacityGrowsWhenStackIsFull();
	testExtremeValuesArePreserved();
	testPushFailsSafelyWhenCapacityCannotGrow();
	testMultipleStack();
	printf("All tests passed\n");
	return 0;
}
