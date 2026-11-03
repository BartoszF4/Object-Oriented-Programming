#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
  public:
	double real, imaginary;
	Complex(double realPart = 0.0, double imaginaryPart = 0.0);
	Complex& operator+=(const Complex& other);
	Complex& operator-=(const Complex& other);
	Complex& operator*=(const Complex& other);
	Complex& operator/=(const Complex& other);
	double getAmplitude() const;
	double getPhase() const;
};

Complex operator+(Complex left, const Complex& right);
Complex operator-(Complex left, const Complex& right);
Complex operator*(Complex left, const Complex& right);
Complex operator/(Complex left, const Complex& right);

bool operator==(const Complex& left, const Complex& right);
bool operator!=(const Complex& left, const Complex& right);

std::ostream& operator<<(std::ostream& outputStream, const Complex& number);

#endif
