#include "linerequation.h"
#include <string>

namespace PolynomialEquation {

LinerNormalEquation::LinerNormalEquation(const double &coef0) //: AbstractPolynomialEquation()
{
    my0 = coef0;
}

void PolynomialEquation::LinerNormalEquation::setCoef0(const double &coef0)
{
    my0 = coef0;
    deleteRoots();
}

LinerNormalEquation LinerNormalEquation::operator+(const double &val)
{
    return LinerNormalEquation( this->my0 + val );
}

LinerNormalEquation LinerNormalEquation::operator-(const double &val)
{
    return LinerNormalEquation( this->my0 - val );
}

LinerNormalEquation LinerNormalEquation::operator+(const LinerNormalEquation &eq)
{
    return LinerNormalEquation( (this->my0 + eq.my0)/2 );
}

double LinerNormalEquation::operator-(const LinerNormalEquation &eq)
{
    return this->my0 - eq.my0;
}

const AbstractPolynomialEquationRoots *PolynomialEquation::LinerNormalEquation::roots() const
{
    if(!myroots)
        myroots = new LinerEquationRoot( -my0 );
    return myroots;
}

std::list<std::unique_ptr<AbstractPolynomialEquation> > LinerNormalEquation::decomposed() const
{
    std::list<std::unique_ptr<AbstractPolynomialEquation> > root;
    root.push_back( std::make_unique<LinerNormalEquation>( this->my0 ) );
    return root;
}

std::string LinerNormalEquation::toString() const
{
    return std::string("x") + ( my0 > 0 ? std::string("+") : std::string() ) + ( my0 == 0 ? std::string() : std::to_string( my0 ) );
}

LinerEquationRoot::LinerEquationRoot(const double &root)
    : myx1(root)
{
}

std::string LinerEquationRoot::toString() const
{
    return "x = " + std::to_string(myx1) + ".";
}

}
