#include <iostream>

#include "polynomial_equations/quadraticequation.h"
#include "test.h"

using namespace std;
using namespace PolynomialEquation;

int main()
{
    QuadraticNormalEquation ceq( 3, 2 );
    cout << ceq << endl;
    cout << ceq.roots() << endl;
    ceq = ceq + ceq;
    cout << ceq << endl;
    cout << ceq.roots() << endl;
    LinerNormalEquation leq(2);
    auto ceqsum = ceq + leq;
    cout << ceqsum << endl;
    cout << ceqsum.roots() << endl;
    auto ceqn = ceq - leq;
    cout << ceqn << endl;
    cout << ceqn.roots() << endl;

    int step = 1;
    for(int a = -1000; a < 1000; a += step) {
        for(int b = -1000; b < 1000; b += step) {
            QuadraticNormalEquation ceq( a, b );
            auto err1 = ceq.value( ceq.roots()->root(1)->toComplex() );
            auto err2 = ceq.value( ceq.roots()->root(2)->toComplex() );
            if( !is_null( err1 ) || !is_null( err2 ) ) {
                cout << ceq << endl;
                cout << ceq.roots() << endl;
                cout << err1 << endl;
                cout << err2 << endl;
                cout << "------------------\n\n";
            }

        }
    }

    return 0;
}
