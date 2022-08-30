#include "cubicequation.h"
#include "linerequation.h"
#include "quadraticequation.h"

const double SQRT_3 = sqrt( 3 );

namespace PolynomialEquation {

int sgn( double a ) {
    if( a > 0 )
        return 1;
    if( a < 0 )
        return -1;
    return 0;
}

CubicNormalEquation::CubicNormalEquation(const double &coef2, const double &coef1, const double &coef0)
    : my0(coef0), my1(coef1), my2(coef2)
{
}

void CubicNormalEquation::setCoef0(const double &coef0)
{
    my0 = coef0;
    deleteRoots();
}

void CubicNormalEquation::setCoef1(const double &coef1)
{
    my1 = coef1;
    deleteRoots();
}

void CubicNormalEquation::setCoef2(const double &coef2)
{
    my2 = coef2;
    deleteRoots();
}

CubicNormalEquation CubicNormalEquation::operator+(const CubicNormalEquation &eq)
{
    return CubicNormalEquation( (this->my2+eq.my2)/2, (this->my1+eq.my1)/2, (this->my0+eq.my0)/2 );
}

CubicNormalEquation CubicNormalEquation::operator+( const LinerNormalEquation &eq )
{
    auto coef = eq.coefficients();
    return CubicNormalEquation( this->my2, this->my1 + 1, this->my0 + coef.front() );
}

CubicNormalEquation CubicNormalEquation::operator-( const LinerNormalEquation &eq )
{
    auto coef = eq.coefficients();
    return CubicNormalEquation( this->my2, this->my1 - 1, this->my0 - coef.front() );
}

CubicNormalEquation CubicNormalEquation::operator+( const QuadraticNormalEquation &eq )
{
    auto coef = eq.coefficients();
    return CubicNormalEquation( this->my2 + 1, this->my1 + *next( coef.begin() ), this->my0 + coef.front() );
}

CubicNormalEquation CubicNormalEquation::operator-( const QuadraticNormalEquation &eq )
{
    auto coef = eq.coefficients();
    return CubicNormalEquation( this->my2 - 1, this->my1 - *next( coef.begin() ), this->my0 - coef.front() );
}

double CubicNormalEquation::discriminant() const //
{
    auto q = qu();
    auto r = re();
    return q*q*q - r*r;
}

double CubicNormalEquation::qu() const
{
    return (my2*my2 - my1*3) / 9;
}

double CubicNormalEquation::re() const
{
    return (my2 * (my2*my2*2 - my1*9) + 27*my0) / 54;
}

double CubicNormalEquation::fi() const
{
    auto q = qu();
    auto q_cub = q*q*q;
    auto r = re();
    auto s = q*q*q - r*r;
    if( s > 0 )
        return acos( r/sqrt(q_cub) ) / 3;
    else {
        if( q > 0 ) {
            return acosh( fabs( r )/sqrt( q_cub ) ) / 3;
        } else {
            return asinh( fabs( r )/sqrt( -q_cub ) ) / 3;
        }
    }
}

const AbstractPolynomialEquationRoots *CubicNormalEquation::roots() const
{
    if(!myroots) {
        auto r = re();
        auto q = qu();
        auto a_3 = my2 / 3;
        auto s = q*q*q - r*r;
        if(r==0 && q==0) {
            auto x1 = - a_3;
            myroots = new CubicRealEquationRoots( x1, x1, x1 );
            return myroots;
        }
        if( s == 0 ) {
            auto x1 = -2 * cbrt(r) - a_3;
            auto x23 = cbrt(r) - a_3;
            myroots = new CubicRealEquationRoots( x1, x23, x23 );
            return myroots;
        }

        auto f = fi();
        if( s > 0 ) {
            auto q_sqrt = sqrt( q );
            auto x1 = - 2 * q_sqrt * cos( f ) - a_3;
            auto x2 = - 2 * q_sqrt * cos( f + 2.0 * M_PI / 3 ) - a_3;
            auto x3 = - 2 * q_sqrt * cos( f - 2.0 * M_PI / 3 ) - a_3;
            myroots = new CubicRealEquationRoots( x1, x2, x3 );
        } else {
            if( q == 0) {
                auto x = - cbrt( my0 - a_3*a_3*a_3 ) - a_3;
                auto re = -( my2 + x )/2;
                auto im = sqrt( fabs( (my2 - 3*x)*(my2 + x) - 4*my1 ) )/2;
                myroots = new CubicImageEquationRoots( x, re, im );
                return myroots;
            }
            if( q > 0 ) {
                auto q_sqrt = sqrt( q );
                auto x = - q_sqrt * 2.0 * sgn(r) * cosh( f ) - a_3;
                auto re = q_sqrt * sgn(r) * cosh( f ) - a_3;
                auto im = SQRT_3 * q_sqrt * sinh( f );
                myroots = new CubicImageEquationRoots( x, re, im );
            } else {
                auto q_sqrt = sqrt( -q );
                auto x = - q_sqrt * 2.0 * sgn(r) * sinh( f ) - a_3;
                auto re = q_sqrt * sgn(r) * sinh( f ) - a_3;
                auto im = SQRT_3 * q_sqrt * cosh( f );
                myroots = new CubicImageEquationRoots( x, re, im );
            }
        }
    }
    return myroots;
}

std::list<std::unique_ptr<AbstractPolynomialEquation> > CubicNormalEquation::decomposed() const
{
    std::list<std::unique_ptr<AbstractPolynomialEquation> > eqs;
    eqs.push_back( std::make_unique<LinerNormalEquation>( -this->roots()->root( 1 )->real() ) );
    if( roots()->rootsType() == CUB_REAL ) {
        eqs.push_back( std::make_unique<LinerNormalEquation>( -this->roots()->root( 2 )->real() ) );
        eqs.push_back( std::make_unique<LinerNormalEquation>( -this->roots()->root( 3 )->real() ) );
    }
    else if( roots()->rootsType() == CUB_IMAGE ) {
        eqs.push_back( std::make_unique<QuadraticNormalEquation>( -2.0*this->roots()->root( 2 )->real(), fabs( this->roots()->root( 2 )->toComplex() ) ) );
    }
    return eqs;
}

std::string CubicNormalEquation::toString() const
{
    return std::string("x^3")
            + ( my2 > 0 ? std::string("+") : std::string() ) + ( my2==0 ? std::string() : ( std::to_string( my2 ) + std::string("*x^2") ) )
            + ( my1 > 0 ? std::string("+") : std::string() ) + ( my1==0 ? std::string() : ( std::to_string( my1 ) + std::string("*x") ) )
            + ( my0 > 0 ? std::string("+") : std::string() ) + ( my0==0 ? std::string() : std::to_string( my0 ) );
}

//-----------------------------------------------------------

CubicRealEquationRoots::CubicRealEquationRoots(const double &root1, const double &root2, const double &root3)
    : myx1( root1 ), myx2( root2 ), myx3( root3 )
{
}

std::unique_ptr<AbstractPolynomialRoot> CubicRealEquationRoots::root(int number) const
{
    switch (number) {
    case 1:
        return std::make_unique<RealPolynomialRoot>(myx1);
    case 2:
        return std::make_unique<RealPolynomialRoot>(myx2);
    case 3:
        return std::make_unique<RealPolynomialRoot>(myx3);
    default:
        return nullptr;
    }
}

std::string CubicRealEquationRoots::toString() const
{
    return "x1 = " + std::to_string( myx1 )
            + "; x2 = " + std::to_string( myx2 )
            + "; x3 = " + std::to_string( myx3 );
}

CubicImageEquationRoots::CubicImageEquationRoots(const double &root, const double &real, const double &image)
    : myx1( root ), myre( real ), myim( image )
{
}

//-----------------------------------------------------------

std::unique_ptr<AbstractPolynomialRoot> CubicImageEquationRoots::root(int number) const
{
    switch (number) {
    case 1:
        return std::make_unique<RealPolynomialRoot>(myx1);
    case 2:
        return std::make_unique<ImagePolynomialRoot>(myre, myim);
    case 3:
        return std::make_unique<ImagePolynomialRoot>(myre, -myim);
    default:
        return nullptr;
    }
}

std::string CubicImageEquationRoots::toString() const
{
    return "x1 = " + std::to_string( myx1 )
            + "; x2 = " + (myre == 0 ? std::string() : std::to_string( myre ) + std::string(" + ")) + "j" + std::to_string( myim )
            + "; x3 = " + (myre == 0 ? std::string() : std::to_string( myre ) + std::string(" ")) + "- j" + std::to_string( myim )
            + ".";
}

}
