#ifndef POLYNOMIALROOT_H
#define POLYNOMIALROOT_H

#include <complex>
#include <iostream>

/**
 * @brief Интерфейс для классов корня уравнения
 */

class AbstractPolynomialRoot //: public AAbstractPolynomialRoot
{
public:
    ~AbstractPolynomialRoot() { /* std::cout << "AbstractPolynomialRoot delete\n"; */ }
    virtual std::complex<double> toComplex() const = 0;
    virtual double real() const = 0;
    virtual double image() const = 0;
    virtual bool isReal() const = 0;
};

//--------------------------------------------------------
/**
 * @brief Действительный корень
 */
class RealPolynomialRoot : public AbstractPolynomialRoot
{
public:
    RealPolynomialRoot( const double &x )
        : myx(x) {}
    virtual std::complex<double> toComplex() const override { return std::complex<double>(myx, 0); }
    virtual double real() const override { return myx; }
    virtual double image() const override { return 0; }
    virtual bool isReal() const override { return true; }
private:
    double myx;
};

//--------------------------------------------------------
/**
 * @brief Мнимый корень
 */
class ImagePolynomialRoot : public AbstractPolynomialRoot
{
public:
    ImagePolynomialRoot( const double &r, const double &i )
        : myr(r), myi(i) {}
    virtual std::complex<double> toComplex() const override { return std::complex<double>(myr, myi); }
    virtual double real() const override { return myr; }
    virtual double image() const override { return myi; }
    virtual bool isReal() const override { return false; }
private:
    double myr, myi;
};



#endif // POLYNOMIALROOT_H
