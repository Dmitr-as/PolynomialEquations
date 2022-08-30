#ifndef POLYNOMIAL_EQUATIONS_H
#define POLYNOMIAL_EQUATIONS_H

#include <list>
#include <memory>
#include <iostream>

#include "root.h"

namespace PolynomialEquation {

enum POLINOM_TYPES {
    ERROR,
    LINER,
    QUADRATIC,
    CUBIC,
    OTHER
};

enum ROOTS_TYPES {
    ERROR_ROOTS,
    LINE,
    QUADRAT_REAL,
    //QUADRAT_DUAL_REAL,
    QUADRAT_IMAGE,
    CUB_REAL,
    //CUB_DUAL_REAL,
    //CUB_TRIPLE_REAL,
    CUB_IMAGE,
    OTHER_ROOTS
};

class AbstractPolynomialEquationRoots
{
public:
    virtual ~AbstractPolynomialEquationRoots() { /*std::cout << "delete AbstractPolynomialEquationRoots";*/ }
    virtual int rootsType() const = 0;
    virtual std::unique_ptr<AbstractPolynomialRoot> root(int number) const = 0;

    friend std::ostream &operator<< (std::ostream &out, const AbstractPolynomialEquationRoots *root) {
        out << root->toString();
        return out;
    }
protected:
    virtual std::string toString() const = 0;
};

//--------------------------------------------------------

class AbstractPolynomialEquation
{
public:
    virtual ~AbstractPolynomialEquation() { deleteRoots(); }
    virtual int equationType() const = 0;
    virtual std::list<double> coefficients() const = 0;
    virtual double value( const double &x ) const = 0;
    virtual std::complex<double> value( const std::complex<double> &x ) const = 0;
    virtual std::complex<double> value( const std::unique_ptr<AbstractPolynomialRoot> &x ) {
        if(x->isReal())
            return std::complex<double>( value( x->real() ) );
        return value( x->toComplex() );
    }
    virtual const AbstractPolynomialEquationRoots *roots() const = 0;
    const std::unique_ptr<AbstractPolynomialRoot> root(int number) const { return roots()->root(number); }
    virtual std::list<std::unique_ptr<AbstractPolynomialEquation>> decomposed() const = 0;
    virtual bool isNormal() const = 0;

    friend std::ostream &operator<< (std::ostream &out, const AbstractPolynomialEquation &equation) {
        out << equation.toString() + " = 0.";
        return out;
    }
protected:
    virtual std::string toString() const = 0;
    mutable AbstractPolynomialEquationRoots *myroots = nullptr;
    void deleteRoots() const;
private:
};

inline void AbstractPolynomialEquation::deleteRoots() const
{
    if(myroots) {
        delete myroots;
        myroots = nullptr;
    }
}

}

#endif // POLYNOMIAL_EQUATIONS_H
