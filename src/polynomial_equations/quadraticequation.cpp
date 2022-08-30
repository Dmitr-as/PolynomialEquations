#include "quadraticequation.h"
//#include "linerequation.h"


namespace PolynomialEquation
{

QuadraticNormalEquation::QuadraticNormalEquation(const double &coef1, const double &coef0)
    : my0(coef0), my1(coef1)
{
}

void QuadraticNormalEquation::setCoef0(const double &coef0)
{
    my0 = coef0;
    deleteRoots();
}

void QuadraticNormalEquation::setCoef1(const double &coef1)
{
    my1 = coef1;
    deleteRoots();
}

QuadraticNormalEquation QuadraticNormalEquation::operator+( const double &val )
{
    return QuadraticNormalEquation( this->my1, this->my0 + val );
}

QuadraticNormalEquation QuadraticNormalEquation::operator-( const double &val )
{
    return QuadraticNormalEquation( this->my1, this->my0 - val );
}

QuadraticNormalEquation QuadraticNormalEquation::operator+(const QuadraticNormalEquation &eq)
{
    return QuadraticNormalEquation( (this->my1+eq.my1)/2, (this->my0+eq.my0)/2 );
}

QuadraticNormalEquation QuadraticNormalEquation::operator-(const LinerNormalEquation &eq)
{
    return QuadraticNormalEquation( this->my1 - 1, this->my0 - eq.coefficients().front() );
}

QuadraticNormalEquation QuadraticNormalEquation::operator+(const LinerNormalEquation &eq)
{
    return QuadraticNormalEquation( this->my1 + 1, this->my0 + eq.coefficients().front() );
}

double QuadraticNormalEquation::discriminant() const
{
    return my1*my1 - 4*my0;
}

const AbstractPolynomialEquationRoots *QuadraticNormalEquation::roots() const
{
    if(!myroots) {
        auto d = discriminant();
        if(d < 0)
            myroots = new QuadraticImageEquationRoots( -my1/2, sqrt(-d)/2 );
        else
            myroots = new QuadraticRealEquationRoots( (-my1 - sqrt( d ) )/2, (-my1 + sqrt( d ) )/2 );
    }
    return myroots;
}

std::list<std::unique_ptr<AbstractPolynomialEquation> > QuadraticNormalEquation::decomposed() const
{
    std::list<std::unique_ptr<AbstractPolynomialEquation> > eqs;
    if( this->roots()->rootsType() == QUADRAT_REAL ) {
        eqs.push_back( std::make_unique<LinerNormalEquation>( -this->roots()->root( 1 )->real() ) );
        eqs.push_back( std::make_unique<LinerNormalEquation>( -this->roots()->root( 2 )->real() ) );
    }
    else if( this->roots()->rootsType() == QUADRAT_IMAGE ) {
        eqs.push_back( std::make_unique<QuadraticNormalEquation>( *this ) );
    }
    return eqs;
}

std::string QuadraticNormalEquation::toString() const
{
    return std::string("x^2")
            + ( my1 > 0 ? std::string("+") : std::string("") ) + ( my1==0 ? std::string("") : std::to_string( my1 ) + std::string("*x") )
            + ( my0 > 0 ? std::string("+") : std::string("") ) + ( my0==0 ? std::string("") : std::to_string( my0 ) );
}


//----------------------------------------------------------
QuadraticRealEquationRoots::QuadraticRealEquationRoots(const double &root1, const double &root2)
    : myx1( root1 ), myx2( root2 )
{
}

std::unique_ptr<AbstractPolynomialRoot> QuadraticRealEquationRoots::root(int number) const
{
    switch (number) {
    case 1:
        return std::make_unique<RealPolynomialRoot>(myx1);
    case 2:
        return std::make_unique<RealPolynomialRoot>(myx2);
    default:
        return nullptr;
    }
}

std::string QuadraticRealEquationRoots::toString() const
{
    return "x1 = " + std::to_string( myx1 ) + "; x2 = " + std::to_string( myx2 ) + ".";
}

QuadraticImageEquationRoots::QuadraticImageEquationRoots(const double &real, const double &image)
    : myre( real ), myim( image )
{
}

std::unique_ptr<AbstractPolynomialRoot> QuadraticImageEquationRoots::root(int number) const
{
    switch (number) {
    case 1:
        return std::make_unique<ImagePolynomialRoot>(myre, myim);
    case 2:
        return std::make_unique<ImagePolynomialRoot>(myre, -myim);
    default:
        return nullptr;
    }
}

std::string QuadraticImageEquationRoots::toString() const
{
    return "x1 = " + std::to_string( myre ) + " + j" + std::to_string( myim )
            + "; x2 = " + std::to_string( myre ) + " - j" + std::to_string( myim ) + ".";
}




}
