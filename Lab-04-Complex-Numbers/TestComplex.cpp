#include "Complex.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>

const double tolerance = 1e-9;
const double pi = M_PI;

bool isClose(double actual, double expected)
{
	return std::fabs(actual - expected) < tolerance;
}

void testConstructorsAndFieldAccess()
{
	Complex number(1, 2);
	assert(number.real == 1 && number.imaginary == 2);
	number.real = 7;
	number.imaginary = -3;
	assert(number == Complex(7, -3));
	assert(Complex().real == 0 && Complex().imaginary == 0);
	assert(Complex(2.5).real == 2.5 && Complex(2.5).imaginary == 0);
}

void testStreamInsertion()
{
	std::ostringstream stream;
	stream << Complex(1.5, 2.5) << " | " << Complex(-3, -4) << " | "
		   << Complex(5, 0);
	assert(stream.str() == "1.5 + 2.5i | -3 - 4i | 5");
	std::ostringstream zeroReal;
	zeroReal << Complex(0, 2);
	assert(zeroReal.str() == "0 + 2i");
}

void testSelfAssignments()
{
	Complex sum(1, 2), difference(1, 2), product(1, 2), quotient(1, 2);
	sum += sum;
	difference -= difference;
	product *= product;
	quotient /= quotient;
	assert(sum == Complex(2, 4));
	assert(difference == Complex(0, 0));
	assert(product == Complex(-3, 4));
	assert(quotient == Complex(1, 0));
}

void testChainedPlusAssignment()
{
	Complex a(1, 2), b(3, 4), c(5, 6);
	a += b += c;
	assert(a == Complex(9, 12));
	assert(b == Complex(8, 10));
	assert(c == Complex(5, 6));
}

void testParenthesizedPlusAssignment()
{
	Complex a(1, 2), b(3, 4), c(5, 6);
	(a += b) += c;
	assert(a == Complex(9, 12));
	assert(b == Complex(3, 4));
	assert(c == Complex(5, 6));
}

void testChainedMultiplyAssignment()
{
	Complex a(1, 2), b(3, 4), c(5, 6);
	a *= b *= c;
	assert(a == Complex(-85, 20));
	assert(b == Complex(-9, 38));
	assert(c == Complex(5, 6));
}

void testParenthesizedMultiplyAssignment()
{
	Complex a(1, 2), b(3, 4), c(5, 6);
	(a *= b) *= c;
	assert(a == Complex(-85, 20));
	assert(b == Complex(3, 4));
	assert(c == Complex(5, 6));
}

void testDivisionAndMultiplication()
{
	Complex a(3, 4), b(5, 6);
	Complex c(2, 11), d(3, 4);
	a *= b;
	c /= d;
	assert(a == Complex(-9, 38));
	assert(c == Complex(2, 1));
}

void testBinaryOperators()
{
	Complex a(1, 2), b(3, 4);
	assert(a + b == Complex(4, 6));
	assert(a - b == Complex(-2, -2));
	assert(a * b == Complex(-5, 10));
	assert(a * b / b == a);
	assert(a == Complex(1, 2) && b == Complex(3, 4));
}

void testAdditionWithNumber()
{
	Complex a(1, 2);
	assert(a + 7.2 == Complex(1 + 7.2, 2));
	assert(7.2 + a == a + 7.2);
	assert(10 - a == Complex(9, -2));
	assert(a == Complex(1, 2));
}

void testMultiplicationWithNumber()
{
	Complex b(3, 4);
	assert(b * 5.1 == Complex(3 * 5.1, 4 * 5.1));
	assert(5.1 * b == b * 5.1);
	assert(5 / Complex(1, 2) == Complex(1, -2));
	assert(b == Complex(3, 4));
}

void testConstOperands()
{
	const Complex a(1, 2);
	const Complex b(3, 4);
	assert(a + b == Complex(4, 6));
	assert(a * b / b == a);
	assert(a + 7.5 == Complex(8.5, 2));
	assert(7.5 + a == Complex(8.5, 2));
	assert(b * 2 == 2 * b);
}

void testEquality()
{
	Complex a(1, 2);
	assert(a == Complex(1, 2));
	assert(!(a != Complex(1, 2)));
	assert(a != Complex(2, 2));
	assert(a != Complex(1, 3));
}

void testEqualityWithNumber()
{
	Complex c(3.5, 0);
	const Complex constantC(3.5, 0);
	assert(c == 3.5);
	assert(3.5 == c);
	assert(constantC == 3.5);
	assert(3.5 == constantC);
	assert(Complex(3.5, 1) != 3.5);
}

void testAmplitude()
{
	const Complex pythagorean(3, 4);
	assert(isClose(pythagorean.getAmplitude(), 5));
	assert(isClose(Complex(-3, -4).getAmplitude(), 5));
	assert(isClose(Complex().getAmplitude(), 0));
}

void testPhase()
{
	const Complex thirdQuadrant(-1, -1);
	assert(isClose(Complex(1, 0).getPhase(), 0));
	assert(isClose(Complex(0, 2).getPhase(), pi / 2));
	assert(isClose(Complex(-1, 0).getPhase(), pi));
	assert(isClose(Complex(0, -1).getPhase(), -pi / 2));
	assert(isClose(thirdQuadrant.getPhase(), -3 * pi / 4));
}

int main()
{
	testConstructorsAndFieldAccess();
	testStreamInsertion();
	testSelfAssignments();
	testChainedPlusAssignment();
	testParenthesizedPlusAssignment();
	testChainedMultiplyAssignment();
	testParenthesizedMultiplyAssignment();
	testDivisionAndMultiplication();
	testBinaryOperators();
	testAdditionWithNumber();
	testMultiplicationWithNumber();
	testConstOperands();
	testEquality();
	testEqualityWithNumber();
	testAmplitude();
	testPhase();
	std::cout << "All tests passed\n";
}
