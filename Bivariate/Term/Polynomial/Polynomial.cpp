#include <cmath>

#include "Bivariate/Term/Polynomial/Polynomial.hpp"
#include "Vector2D.hpp"


using Polynomial = Bivariate::Term::Polynomial;


Polynomial::Polynomial (double coefficient, double exponent):
    coefficient {coefficient},
    exponent    {exponent}
{}


double Polynomial::evaluate (Vector2D<double> point)
{
    return coefficient * pow(point.x, exponent);
}