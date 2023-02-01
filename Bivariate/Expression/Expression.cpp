#include "Bivariate/Expression/Expression.hpp"

#include "Vector2D.hpp"
#include "Bivariate/Term/Generic.hpp"


Bivariate::Expression::Expression (std::vector<Bivariate::Term::Generic *> terms): terms { terms }
{}

double Bivariate::Expression::evaluate (Vector2D<double> point)
{
    double value = 0;

    for (auto iterator = this->terms.begin(); iterator != this->terms.end(); iterator++)
    {
        value += (*iterator)->evaluate(point);
    }

    return value;
}