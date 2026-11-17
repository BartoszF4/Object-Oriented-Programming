#include "Poly.h"

#include <cmath>

const unsigned constantExponent = 0;
const unsigned linearExponent = 1;
const double unitCoefficient = 1;

static void printSign(std::ostream &out, double coefficient, bool isFirstTerm)
{
    if (!isFirstTerm && coefficient < 0)
    {
        out << " - ";
    }
    else if (!isFirstTerm)
    {
        out << " + ";
    }
    else if (coefficient < 0)
    {
        out << "-";
    }
}

static void printCoefficient(std::ostream &out, double absoluteCoefficient, unsigned exponent)
{
    if (absoluteCoefficient != unitCoefficient || exponent == constantExponent)
    {
        out << absoluteCoefficient;
    }
}

static void printVariable(std::ostream &out, unsigned exponent)
{
    if (exponent == linearExponent)
    {
        out << "x";
    }
    else if (exponent > linearExponent)
    {
        out << "x^" << exponent;
    }
}

static void printTerm(std::ostream &out, unsigned exponent, double coefficient, bool isFirstTerm)
{
    printSign(out, coefficient, isFirstTerm);
    printCoefficient(out, std::abs(coefficient), exponent);
    printVariable(out, exponent);
}

Poly::CoefficientProxy::CoefficientProxy(Poly &polynomial, unsigned exponent)
    : polynomial(polynomial), exponent(exponent)
{
}

Poly::CoefficientProxy &Poly::CoefficientProxy::operator=(double value)
{
    polynomial.setCoefficient(exponent, value);
    return *this;
}

Poly::CoefficientProxy &Poly::CoefficientProxy::operator=(const CoefficientProxy &other)
{
    double value = other;
    return *this = value;
}

Poly::CoefficientProxy::operator double() const
{
    return polynomial.getCoefficient(exponent);
}

Poly::Poly(double constant)
{
    setCoefficient(constantExponent, constant);
}

Poly::CoefficientProxy Poly::operator[](unsigned exponent)
{
    return CoefficientProxy(*this, exponent);
}

double Poly::operator[](unsigned exponent) const
{
    return getCoefficient(exponent);
}

double Poly::operator()(double x) const
{
    double value = 0;
    for (const auto &[exponent, coefficient] : coefficients)
    {
        value += coefficient * std::pow(x, exponent);
    }
    return value;
}

Poly &Poly::operator+=(const Poly &other)
{
    for (const auto &[exponent, coefficient] : other.coefficients)
    {
        addToCoefficient(exponent, coefficient);
    }
    return *this;
}

Poly &Poly::operator-=(const Poly &other)
{
    if (this == &other)
    {
        coefficients.clear();
        return *this;
    }
    for (const auto &[exponent, coefficient] : other.coefficients)
    {
        addToCoefficient(exponent, -coefficient);
    }
    return *this;
}

Poly &Poly::operator*=(const Poly &other)
{
    Poly product;
    for (const auto &[leftExponent, leftCoefficient] : coefficients)
    {
        for (const auto &[rightExponent, rightCoefficient] : other.coefficients)
        {
            product.addToCoefficient(leftExponent + rightExponent, leftCoefficient * rightCoefficient);
        }
    }
    coefficients = product.coefficients;
    return *this;
}

double Poly::getCoefficient(unsigned exponent) const
{
    auto found = coefficients.find(exponent);
    if (found == coefficients.end())
    {
        return 0;
    }
    return found->second;
}

void Poly::setCoefficient(unsigned exponent, double value)
{
    if (value == 0)
    {
        coefficients.erase(exponent);
    }
    else
    {
        coefficients[exponent] = value;
    }
}

void Poly::addToCoefficient(unsigned exponent, double value)
{
    setCoefficient(exponent, getCoefficient(exponent) + value);
}

std::ostream &operator<<(std::ostream &out, const Poly &polynomial)
{
    if (polynomial.coefficients.empty())
    {
        return out << 0;
    }
    bool isFirstTerm = true;
    for (auto term = polynomial.coefficients.rbegin(); term != polynomial.coefficients.rend(); ++term)
    {
        printTerm(out, term->first, term->second, isFirstTerm);
        isFirstTerm = false;
    }
    return out;
}

Poly operator+(Poly left, const Poly &right)
{
    return left += right;
}

Poly operator-(Poly left, const Poly &right)
{
    return left -= right;
}

Poly operator*(Poly left, const Poly &right)
{
    return left *= right;
}