#include <iostream>

#include <polynomial_equations/linerequation.h>

using namespace std;
using namespace PolynomialEquation;

int main()
{
    LinerNormalEquation eq1(1), eq2(-10);
    cout << eq1 << endl;
    cout << eq2 << endl;
    cout << eq1 + eq2 << endl;
    cout << eq1 - eq2 << endl;
    cout << eq2.roots() << endl;
    cout << eq2.root(1)->toComplex() << endl;
    return 0;
}
