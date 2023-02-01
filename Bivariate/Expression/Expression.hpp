#ifndef BIVARIATEEXPRESSION_H
#define BIVARIATEEXPRESSION_H

#include "Bivariate/Bivariate.hpp"

#include <vector>

#include "Vector2D.hpp"
#include "Bivariate/Term/Generic.hpp"


class Bivariate::Expression
{
private:
    std::vector<Bivariate::Term::Generic *> terms;

public:
    Expression (std::vector<Bivariate::Term::Generic *>);
    double evaluate (Vector2D<double>);
};

#endif