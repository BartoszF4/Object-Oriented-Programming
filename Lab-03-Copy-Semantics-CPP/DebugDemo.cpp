#include "Stack.h"

static void takeStackByValue(Stack stack)
{
    stack.push(4);
}

static void takeStackByReference(Stack &stack)
{
    stack.push(4);
}

int main()
{
    Stack s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    Stack s2(s1);

    Stack s3 = s1;

    Stack s4;
    s4.push(10);
    s4 = s1;

    takeStackByValue(s1);
    takeStackByReference(s1);
}