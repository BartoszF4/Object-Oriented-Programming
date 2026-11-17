#pragma once

#include <map>
#include <ostream>

class Poly
{
public:
    class CoefficientProxy
    {
    public:
        CoefficientProxy(Poly &polynomial, unsigned exponent);
        CoefficientProxy &operator=(double value);
        CoefficientProxy &operator=(const CoefficientProxy &other);
        operator double() const;

    private:
        Poly &polynomial;
        unsigned exponent;
    };

    Poly(double constant = 0.0);

    CoefficientProxy operator[](unsigned exponent);
    double operator[](unsigned exponent) const;
    double operator()(double x) const;

    Poly &operator+=(const Poly &other);
    Poly &operator-=(const Poly &other);
    Poly &operator*=(const Poly &other);

    friend std::ostream &operator<<(std::ostream &out, const Poly &polynomial);

private:
    std::map<unsigned, double> coefficients;

    double getCoefficient(unsigned exponent) const;
    void setCoefficient(unsigned exponent, double value);
    void addToCoefficient(unsigned exponent, double value);
};

Poly operator+(Poly left, const Poly &right);
Poly operator-(Poly left, const Poly &right);
Poly operator*(Poly left, const Poly &right);