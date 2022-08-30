#include <iostream>
#include <polynomial_equations/cubicequation.h>
#include <test.h>

using namespace std;
using namespace PolynomialEquation;

bool correct_qube_root( const CubicNormalEquation &eq, int num ) {
    auto r = eq.roots()->root(num);
    if( ! is_null( eq.value( r->toComplex() ) ) || r != r ) {
        cout << eq << endl;
        cout << "r" + std::to_string( num ) + "=" << r->toComplex() << endl;
        cout << eq.value( r->toComplex() ) << endl;
        cout << eq.qu() << " " << eq.re() << " " << eq.discriminant() << '\n';
        cout << "------------------\n";
        return false;
    }
    return true;
}


int main()
{
    CubicNormalEquation ceq( -1, 3, -3 );
    cout << ceq << endl;
    cout << ceq.roots() << endl;
    auto eqs = ceq.decomposed();
    for(const auto &eq : eqs) {
        cout << *eq.get() << endl;
    }

    int count = 0 ;
    int step = 1;
    for(int a = -1000; a < 1000; a = a + step) {
        for(int b = -1000; b < 1000; b = b + step) {
            for(int c = -1000; c < 1000; c = c + step) {
                CubicNormalEquation ceq( a, b, c );
                if( !correct_qube_root( ceq, 1 ) )
                    count++;
                if( !correct_qube_root( ceq, 2 ) )
                    count++;
                if( !correct_qube_root( ceq, 3 ) )
                    count++;

            }
        }
    }
    cout << "err roots count = " << count << endl;



    return 0;
}
