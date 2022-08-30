#ifndef TEST_H
#define TEST_H

#include <math.h>
#include <complex.h>
#include <float.h>

#define MAX_ERR 2E-10

bool is_null( const double &value ) {
    if( fabs(value) /*== 0*/ < MAX_ERR ) {
        return true;
    }
    return false;
}

bool is_null( const std::complex<double> &value ) {
    if( fabs(value) /*== 0*/ < MAX_ERR ) {
        return true;
    }
    return false;
}

#endif // TEST_H

