#ifndef QUADRATICEQUATION_H
#define QUADRATICEQUATION_H

#include "abstract_polynomial_equations.h"
#include "linerequation.h"

namespace PolynomialEquation {

class QuadraticNormalEquation : public AbstractPolynomialEquation
{
public:
    QuadraticNormalEquation(const double &coef1, const double &coef0);
    virtual ~QuadraticNormalEquation() {}
    void setCoef0(const double &coef0);
    void setCoef1(const double &coef1);

    QuadraticNormalEquation operator+( const double &val );
    QuadraticNormalEquation operator-( const double &val );
    QuadraticNormalEquation operator+( const QuadraticNormalEquation &eq );
    //QuadraticNormalEquation operator-( const QuadraticNormalEquation &eq );
    QuadraticNormalEquation operator+( const LinerNormalEquation &eq );
    QuadraticNormalEquation operator-( const LinerNormalEquation &eq );

    double discriminant() const;
    virtual int equationType() const override { return QUADRATIC; }
    virtual std::list<double> coefficients() const override { std::list<double> list; list.push_back( my0 ); list.push_back( my1 ); list.push_back( 1 ); return list; }
    virtual double value( const double &x ) const override { return (x + my1)*x + my0; }
    virtual std::complex<double> value( const std::complex<double> &x ) const override { return (x + my1)*x + my0; }
    virtual const AbstractPolynomialEquationRoots *roots() const override;
    virtual std::list< std::unique_ptr<AbstractPolynomialEquation> > decomposed() const override;
    virtual bool isNormal() const override {return true;}
protected:
    virtual std::string toString() const override;
private:
    double my0;
    double my1;
};

//-----------------------------------------------------

class QuadraticRealEquationRoots : public AbstractPolynomialEquationRoots
{
public:
    QuadraticRealEquationRoots(const double &root1, const double &root2);
    virtual ~QuadraticRealEquationRoots() {}
    virtual int rootsType() const override {return QUADRAT_REAL;}
    virtual std::unique_ptr<AbstractPolynomialRoot> root(int number) const override;

protected:
    virtual std::string toString() const override;
private:
    double myx1;
    double myx2;
};

//-----------------------------------------------------

class QuadraticImageEquationRoots : public AbstractPolynomialEquationRoots
{
public:
    QuadraticImageEquationRoots(const double &real, const double &image);
    virtual ~QuadraticImageEquationRoots() {}
    virtual int rootsType() const override {return QUADRAT_IMAGE;}
    virtual std::unique_ptr<AbstractPolynomialRoot> root(int number) const override;

protected:
    virtual std::string toString() const override;
private:
    double myre;
    double myim;
};

}
#endif // QUADRATICEQUATION_H
