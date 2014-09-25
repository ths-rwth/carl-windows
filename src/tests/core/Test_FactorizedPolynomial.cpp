#include "gtest/gtest.h"
#include "carl/core/MultivariatePolynomial.h"
#include "carl/core/FactorizedPolynomial.h"

#include <cln/cln.h>


using namespace carl;

TEST(FactorizedPolynomial, Construction)
{
    VariablePool& vpool = VariablePool::getInstance();
    Variable x = vpool.getFreshVariable();
    vpool.setName(x, "x");
    Variable y = vpool.getFreshVariable();
    vpool.setName(y, "y");
    Variable z = vpool.getFreshVariable();
    vpool.setName(z, "z");
    typedef MultivariatePolynomial<cln::cl_RA> P;
    P fxy({(cln::cl_RA)1*x*y});
    P fxyz({(cln::cl_RA)1*x*y*z});
    
    Cache<PolynomialFactorizationPair<P>> fpCache;
    fpCache.print();
    FactorizedPolynomial<P> fpA( fxy, fpCache );
    fpCache.print();
    FactorizedPolynomial<P> fpB( fxyz, fpCache );
    fpCache.print();
    FactorizedPolynomial<P> restA( P( 2 ), fpCache );
    FactorizedPolynomial<P> restB( P( 2 ), fpCache );
    
    FactorizedPolynomial<P> fpC( commonDivisor( fpA, fpB, restA, restB ) );
    
    //FactorizedPolynomial<P> fpGCD( gcd( fpA, fpB ) );
    fpCache.print();
}