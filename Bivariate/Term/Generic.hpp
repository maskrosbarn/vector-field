#ifndef __GENERIC_TERM_H
#define __GENERIC_TERM_H


#include "Vector2D.hpp"


namespace Bivariate
{
    namespace Term
    {
        class Generic
        {
        public:
            virtual ~Generic () = default;
            virtual double evaluate (Vector2D<double>) = 0;
        };
    }
}


#endif