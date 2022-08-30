#ifndef LINEREQUATION_H
#define LINEREQUATION_H

#include "abstract_polynomial_equations.h"

namespace PolynomialEquation {

class LinerNormalEquation : public AbstractPolynomialEquation
{
public:
    LinerNormalEquation(const double &coef0);
    void setCoef0(const double &coef0);
    LinerNormalEquation operator+( const double &val );
    LinerNormalEquation operator-( const double &val );
    LinerNormalEquation operator+( const LinerNormalEquation &eq );
    double operator-( const LinerNormalEquation &eq );
    virtual int equationType() const override {return LINER;}
    virtual std::list<double> coefficients() const override { std::list<double> list; list.push_back( my0 ); list.push_back( 1 ); return list; }
    virtual double value( const double &x ) const override { return x + my0; }
    virtual std::complex<double> value( const std::complex<double> &x ) const override { return x + my0; }
    virtual const AbstractPolynomialEquationRoots *roots() const override;
    virtual std::list<std::unique_ptr<AbstractPolynomialEquation>> decomposed() const override;
    virtual bool isNormal() const override {return true;}
protected:
    virtual std::string toString() const override;
private:
    double my0;
};

//--------------------------------------------------------

class LinerEquationRoot : public AbstractPolynomialEquationRoots
{
public:
    LinerEquationRoot(const double &root);
    virtual ~LinerEquationRoot() {}
    virtual int rootsType() const override {return LINE;}
    virtual std::unique_ptr<AbstractPolynomialRoot> root(int number) const override { return number == 1 ? std::make_unique<RealPolynomialRoot>(myx1) : nullptr; }
protected:
    virtual std::string toString() const override;

private:
    double myx1;
};

}

#endif // LINEREQUATION_H
