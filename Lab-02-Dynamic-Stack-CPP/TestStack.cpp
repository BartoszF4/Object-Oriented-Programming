#include "Stack.h"
#include <assert.h>
#include <iostream>
#include <limits.h>

static const int FIRST_VALUE = 1;
static const int SECOND_VALUE = 2;
static const int THIRD_VALUE = 3;
static const int ZERO_VALUE = 0;
static const size_t MANY_ELEMENTS_COUNT = 1000;
static const size_t SIZES_TO_CHECK = 100;

static void reportPassed(const char* testName)
{
	std::cout << "PASS: " << testName << "\n";
}

static void assertPopReturns(Stack& stack, int expectedValue)
{
	int popped = stack.pop();
	assert(popped == expectedValue);
}

static void pushRange(Stack& stack, size_t count)
{
	for (size_t index = 0; index < count; index++) {
		stack.push((int)(index));
	}
}

static void assertPopsRangeInReverse(Stack& stack, size_t count)
{
	for (size_t index = count; index > 0; index--) {
		assertPopReturns(stack, (int)(index - 1));
	}
}

static void testStackIsEmptyAfterConstruction()
{
	Stack stack;
	assert(stack.isEmpty());
	reportPassed("testStackIsEmptyAfterConstruction");
}

static void testStackIsNotEmptyAfterPush()
{
	Stack stack;
	stack.push(FIRST_VALUE);
	assert(!stack.isEmpty());
	reportPassed("testStackIsNotEmptyAfterPush");
}

static void testPopReturnsPushedElement()
{
	Stack stack;
	stack.push(FIRST_VALUE);
	assertPopReturns(stack, FIRST_VALUE);
	reportPassed("testPopReturnsPushedElement");
}

static void testLIFO()
{
	Stack stack;
	stack.push(FIRST_VALUE);
	stack.push(SECOND_VALUE);
	stack.push(THIRD_VALUE);
	assertPopReturns(stack, THIRD_VALUE);
	assertPopReturns(stack, SECOND_VALUE);
	assertPopReturns(stack, FIRST_VALUE);
	reportPassed("testLIFO");
}

static void testIsStackEmptyAfterPoppingAllItems()
{
	Stack stack;
	stack.push(FIRST_VALUE);
	stack.push(SECOND_VALUE);
	assertPopReturns(stack, SECOND_VALUE);
	assertPopReturns(stack, FIRST_VALUE);
	assert(stack.isEmpty());
	reportPassed("testIsStackEmptyAfterPoppingAllItems");
}

static void testPushBeyondInitialCapacityKeepsAllElements()
{
	Stack stack;
	pushRange(stack, MANY_ELEMENTS_COUNT);
	assertPopsRangeInReverse(stack, MANY_ELEMENTS_COUNT);
	assert(stack.isEmpty());
	reportPassed("testPushBeyondInitialCapacityKeepsAllElements");
}

static void testExtremeValuesArePreserved()
{
	Stack stack;
	stack.push(INT_MAX);
	stack.push(INT_MIN);
	stack.push(ZERO_VALUE);
	assertPopReturns(stack, ZERO_VALUE);
	assertPopReturns(stack, INT_MIN);
	assertPopReturns(stack, INT_MAX);
	reportPassed("testExtremeValuesArePreserved");
}

static void testMultipleStack()
{
	Stack stack1;
	Stack stack2;
	Stack stack3;
	stack1.push(FIRST_VALUE);
	stack1.push(SECOND_VALUE);
	stack2.push(FIRST_VALUE);
	stack3.push(FIRST_VALUE);
	assertPopReturns(stack3, FIRST_VALUE);
	assertPopReturns(stack2, FIRST_VALUE);
	assertPopReturns(stack1, SECOND_VALUE);
	assertPopReturns(stack1, FIRST_VALUE);
	assert(stack3.isEmpty());
	reportPassed("testMultipleStack");
}

static void assertPushAndPopAllOf(size_t count)
{
	Stack stack;
	pushRange(stack, count);
	assertPopsRangeInReverse(stack, count);
	assert(stack.isEmpty());
}

static void testEverySizeUpToLimitWorks()
{
	for (size_t index = 0; index <= SIZES_TO_CHECK; index++) {
		assertPushAndPopAllOf(index);
	}
	reportPassed("testEverySizeUpToLimitWorks");
}

static void testPushAfterPartialPopKeepsOrder()
{
	Stack stack;
	stack.push(FIRST_VALUE);
	stack.push(SECOND_VALUE);
	stack.push(THIRD_VALUE);
	assertPopReturns(stack, THIRD_VALUE);
	assertPopReturns(stack, SECOND_VALUE);
	pushRange(stack, MANY_ELEMENTS_COUNT);
	assertPopsRangeInReverse(stack, MANY_ELEMENTS_COUNT);
	assertPopReturns(stack, FIRST_VALUE);
	reportPassed("testPushAfterPartialPopKeepsOrder");
}

int main()
{
	testStackIsEmptyAfterConstruction();
	testStackIsNotEmptyAfterPush();
	testPopReturnsPushedElement();
	testLIFO();
	testIsStackEmptyAfterPoppingAllItems();
	testPushBeyondInitialCapacityKeepsAllElements();
	testExtremeValuesArePreserved();
	testMultipleStack();
	testEverySizeUpToLimitWorks();
	testPushAfterPartialPopKeepsOrder();
	std::cout << "All tests passed\n";
	return 0;
}
