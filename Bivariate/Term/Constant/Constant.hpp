#ifndef __BIVARIATE_CONSTANT_TERM_H
#define __BIVARIATE_CONSTANT_TERM_H


#include "Bivariate/Bivariate.hpp"
#include "Bivariate/Term/Generic.hpp"
#include "Vector2D.hpp"


class Bivariate::Term::Constant: public Bivariate::Term::Generic
{
private:
    double value;

public:
    Constant (double);
    double evaluate (Vector2D<double>);
};


#endif