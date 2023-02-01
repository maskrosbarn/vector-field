#include "Bivariate/Term/Constant/Constant.hpp"
#include "Vector2D.hpp"


using Constant = Bivariate::Term::Constant;


Constant::Constant (double value):
    value { value }
{}


double Constant::evaluate (Vector2D<double> point)
{
    return value;
}