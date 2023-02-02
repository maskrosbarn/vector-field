#include <vector>

#include <SDL2/SDL.h>

#include "Vector2D.hpp"
#include "Bivariate/Bivariate.hpp"
#include "Application/Application.hpp"


int main (int argc, char const * argv[])
{
    using Constant   = Bivariate::Term::Constant;
    using Polynomial = Bivariate::Term::Polynomial;
    using Expression = Bivariate::Expression;

    Polynomial a(1, 2),
               b(1, 1);
    Constant   c(1);

    Terms terms { &a, &b, &c };

    Expression f(terms);

    Application application(&f);
    application.main_loop();

    return 0;
}