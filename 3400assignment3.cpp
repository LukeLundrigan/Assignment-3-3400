#include "Rational.h"
#include <stdexcept>
using namespace std;

Rational::Rational(Integer numerator, Integer denominator)
	: numerator(numerator), denominator(denominator)
{
	if (denominator == 0)
		throw invalid_argument("Denominator cannot be zero");
}

Rational::Rational(Rational&& other)
	:numerator(other.numerator), denominator(other.denominator)
{
	other.numerator = 0;
	other.denominator = 1;
}

Rational::Rational(const Rational& other)
	:numerator(other.numerator), denominator(other.denominator)
{
}

Rational& Rational::operator=(const Rational& other)
{
	if (this != &other)
	{
		numerator = other.numerator;
		denominator = other.denominator;
	}
	return *this;
}

Rational& Rational::operator=(const Rational&& other)
{
	if (this != &other)
	{
		numerator = other.numerator;
		denominator = other.denominator;
	}
	return *this;
}

Rational Rational::operator+(const Rational& other)
{
	return Rational(
		numerator * other.denominator + other.numerator * denominator,
		denominator * other.denominator
	);
}

Rational Rational::operator-(const Rational& other)
{
	return Rational(
		numerator * other.denominator - other.numerator * denominator,
		denominator * other.denominator
	);
}

Rational Rational::operator*(const Rational& other)
{
	return Rational(
		numerator * other.numerator,
		denominator * other.denominator
	);
}

Rational Rational::operator/(const Rational& other)
{
	if (other.numerator == 0)
		throw invalid_argument("Cannot divide by zero");
	
	return Rational(
		numerator * other.denominator,
		denominator * other.numerator
	);
}

Rational& Rational::operator+=(const Rational& other)
{
	numerator = numerator * other.denominator + other.numerator * denominator;
	denominator *= other.denominator;
	return *this;
}

Rational& Rational::operator-=(const Rational& other)
{
	numerator = numerator * other.denominator - other.numerator * denominator;
	denominator *= other.denominator;
	return *this;
}

Rational& Rational::operator*=(const Rational& other)
{
	numerator *= other.numerator;
	denominator *= other.denominator;
	return *this;
}

Rational& Rational::operator/=(const Rational& other)
{
	if (other.numerator == 0)
		throw invalid_argument("Denominator cannot be zero");

	numerator *= other.denominator;
	denominator *= other.numerator;
	return *this;
}

double Rational::toDouble() const
{
	return static_cast<double>(numerator) / denominator;
}

friend ostream& operator<<(ostream& out, const Rational& r);
{
	return r.print(out);
}

friend istream& operator>>(istream& in, Rational& r);
{
	return r.scan(in);
}

// Keeping the rational in lowest terms would be good as it is cleaner to look at and understand from users POV
// It also can help with run times if the fractions are really big numbers that could be reduced