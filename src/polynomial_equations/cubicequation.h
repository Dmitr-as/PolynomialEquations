#ifndef CUBICEQUATION_H
#define CUBICEQUATION_H

#include "linerequation.h"
#include "quadraticequation.h"

namespace PolynomialEquation {

class CubicNormalEquation : public AbstractPolynomialEquation
{
public:
    CubicNormalEquation(const double &coef2, const double &coef1, const double &coef0);
    void setCoef0(const double &coef0);
    void setCoef1(const double &coef1);
    void setCoef2(const double &coef2);

    CubicNormalEquation operator+( const CubicNormalEquation &eq );
    CubicNormalEquation operator+( const LinerNormalEquation &eq );
    CubicNormalEquation operator-( const LinerNormalEquation &eq );
    CubicNormalEquation operator+( const QuadraticNormalEquation &eq );
    CubicNormalEquation operator-( const QuadraticNormalEquation &eq );

    double discriminant() const;
    double qu() const;
    double re() const;
    double fi() const;
    virtual int equationType() const override {return CUBIC;}
    virtual std::list<double> coefficients() const override { std::list<double> list; list.push_back( my0 ); list.push_back( my1 ); list.push_back( my2 ); list.push_back( 1 ); return list; }
    virtual double value( const double &x ) const override { return ( (x + my2)*x + my1 ) * x + my0; }
    virtual std::complex<double> value( const std::complex<double> &x ) const override { return ( (x + my2)*x + my1 ) * x + my0; }
    virtual const AbstractPolynomialEquationRoots *roots() const override;
    virtual std::list<std::unique_ptr<AbstractPolynomialEquation>> decomposed() const override;
    virtual bool isNormal() const override {return true;}
protected:
    virtual std::string toString() const override;
private:
    double my0;
    double my1;
    double my2;
};

class CubicRealEquationRoots : public AbstractPolynomialEquationRoots
{
public:
    CubicRealEquationRoots(const double &root1, const double &root2, const double &root3);
    virtual ~CubicRealEquationRoots() {}
    virtual int rootsType() const override {return CUB_REAL;}
    virtual std::unique_ptr<AbstractPolynomialRoot> root(int number) const override;

protected:
    virtual std::string toString() const override;
private:
    double myx1;
    double myx2;
    double myx3;
};

class CubicImageEquationRoots : public AbstractPolynomialEquationRoots
{
public:
    CubicImageEquationRoots(const double &root, const double &real, const double &image);
    virtual ~CubicImageEquationRoots() {}
    virtual int rootsType() const override {return CUB_IMAGE;}
    virtual std::unique_ptr<AbstractPolynomialRoot> root(int number) const override;

protected:
    virtual std::string toString() const override;
private:
    double myx1;
    double myre;
    double myim;
};

}
#endif // CUBICEQUATION_H
