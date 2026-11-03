#include "Complex.h"
#include <cmath>
#include <stdexcept>

Complex::Complex(double realPart, double imaginaryPart)
	: real(realPart), imaginary(imaginaryPart)
{
}

std::ostream& operator<<(std::ostream& outputStream, const Complex& number)
{
	outputStream << number.real;
	if (number.imaginary != 0) {
		const char* sign = number.imaginary < 0 ? " - " : " + ";
		outputStream << sign << std::fabs(number.imaginary) << "i";
	}
	return outputStream;
}

Complex& Complex::operator+=(const Complex& other)
{
	real += other.real;
	imaginary += other.imaginary;
	return *this;
}

Complex& Complex::operator-=(const Complex& other)
{
	real -= other.real;
	imaginary -= other.imaginary;
	return *this;
}

Complex& Complex::operator*=(const Complex& other)
{
	double newReal = real * other.real - imaginary * other.imaginary;
	double newImaginary = real * other.imaginary + imaginary * other.real;
	real = newReal;
	imaginary = newImaginary;
	return *this;
}

Complex& Complex::operator/=(const Complex& other)
{
	if (other == Complex())
		throw std::domain_error("division by zero");
	double newReal = real * other.real + imaginary * other.imaginary;
	double newImaginary = imaginary * other.real - real * other.imaginary;
	double divisorSquaredMagnitude =
		other.real * other.real + other.imaginary * other.imaginary;
	real = newReal / divisorSquaredMagnitude;
	imaginary = newImaginary / divisorSquaredMagnitude;
	return *this;
}

Complex operator+(Complex left, const Complex& right)
{
	left += right;
	return left;
}

Complex operator-(Complex left, const Complex& right)
{
	left -= right;
	return left;
}

Complex operator*(Complex left, const Complex& right)
{
	left *= right;
	return left;
}

Complex operator/(Complex left, const Complex& right)
{
	left /= right;
	return left;
}

bool operator==(const Complex& left, const Complex& right)
{
	return left.real == right.real && left.imaginary == right.imaginary;
}

bool operator!=(const Complex& left, const Complex& right)
{
	return !(left == right);
}

double Complex::getAmplitude() const
{
	return std::sqrt(real * real + imaginary * imaginary);
}

double Complex::getPhase() const
{
	return std::atan2(imaginary, real);
}
