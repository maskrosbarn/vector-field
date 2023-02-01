#include <vector>

#include "Bivariate/Expression/Expression.hpp"
#include "Bivariate/Term/Generic.hpp"
#include "Bivariate/Term/Constant/Constant.hpp"
#include "Bivariate/Term/Polynomial/Polynomial.hpp"


namespace Bivariate
{
    namespace Term
    {
        class Constant;
        class Polynomial;
    }

    class Expression;
}


typedef std::vector<Bivariate::Term::Generic *> Terms;