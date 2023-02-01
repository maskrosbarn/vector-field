#ifndef __BIVARIATE_POLYNOMIAL_TERM_H
#define __BIVARIATE_POLYNOMIAL_TERM_H


#include "Bivariate/Bivariate.hpp"
#include "Bivariate/Term/Generic.hpp"
#include "Vector2D.hpp"


class Bivariate::Term::Polynomial: public Bivariate::Term::Generic
{
private:
    double coefficient, exponent;

public:
    Polynomial (double, double);
    double evaluate (Vector2D<double>);
};


#endif