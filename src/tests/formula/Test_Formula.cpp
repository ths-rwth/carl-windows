#include "gtest/gtest.h"
#include "../../carl/core/MultivariatePolynomial.h"
#include "../../carl/core/VariablePool.h"
#include "../../carl/formula/Formula.h"
#include "../../carl/util/stringparser.h"

#ifdef USE_CLN_NUMBERS
#include <cln/cln.h>
typedef cln::cl_RA Rational;
typedef cln::cl_I Integer;
#else
#include <gmpxx.h>
typedef mpq_class Rational;
typedef mpz_class Integer;
#endif

using namespace carl;

typedef MultivariatePolynomial<Rational> Pol;
typedef Constraint<Pol> Constr;
typedef Formula<Pol> FormulaT;

TEST(Formula, Construction)
{
    Variable x = VariablePool::getInstance().getFreshVariable( "x", VariableType::VT_REAL );
    Variable y = VariablePool::getInstance().getFreshVariable( "y", VariableType::VT_REAL );
    Variable i1 = VariablePool::getInstance().getFreshVariable( "i1", VariableType::VT_INT );
    Variable i2 = VariablePool::getInstance().getFreshVariable( "i2", VariableType::VT_INT );
    Variable i3 = VariablePool::getInstance().getFreshVariable( "i3", VariableType::VT_INT );
//    Variable i = newArithmeticVariable( "i", VariableType::VT_INT );
    Variable b = VariablePool::getInstance().getFreshVariable( "b", VariableType::VT_BOOL );
//    Sort sortS = newSort( "S" );
//    Sort sortT = newSort( "T" );
//    Variable u = VariableNamePool::getInstance().newUninterpretedVariable( "u" );
//    Variable v = VariableNamePool::getInstance().newUninterpretedVariable( "v" );
//    UVariable uu( u, sortS );
//    UVariable uv( v, sortT );

    // Next we see an example how to create polynomials, which form the left-hand sides of the constraints:
    Pol px( x );
    Pol py( y );
    Pol lhsA = px.pow(2) - py;
    Pol lhsB = Rational(4) * px + py - Rational(8) * py.pow(7);
    Pol lhsD = px*py;
    Pol pi1( i1 );
    Pol pi2( i2 );
    Pol pi3( i3 );
    Pol lhsC = Rational(2) * pi1 + Rational(2) * pi2 + Rational(2) * pi3 - Rational(5);
    
    // Constraints can then be constructed as follows:
    Constr constraintA = Constr( lhsD, Relation::EQ );
    
    // Uninterpreted functions are 
    
    // Now, we can construct the atoms of the Boolean Ast
    const Formula<Pol> atomA = Formula<Pol>( constraintA );
    const Formula<Pol> atomB = Formula<Pol>( lhsB, Relation::EQ );
    const Formula<Pol> atomC = Formula<Pol>( b );
    const Formula<Pol> inEq = Formula<Pol>( lhsC, Relation::EQ );
    std::cout << inEq << std::endl;
    EXPECT_TRUE( inEq.getType() == FormulaType::FALSE );
    
    // and the Ast itself:
    Formulas<Pol> subAstsA;
    subAstsA.push_back( Formula<Pol>( FormulaType::NOT, atomC ) );
    subAstsA.push_back( atomA );
    subAstsA.push_back( atomB );
    const Formula<Pol> phiA( FormulaType::AND, subAstsA );
    const Formula<Pol> phiC( FormulaType::OR, Formula<Pol>( FormulaType::NOT, atomA ), atomC );
    const Formula<Pol> phiE( FormulaType::IMPLIES, phiA, phiC );
    std::cout << phiE << std::endl;
}

TEST(Formula, BooleanConstructors)
{
    Variable b1 = freshBooleanVariable("b1");
    Variable b2 = freshBooleanVariable("b2");
    
    FormulaT True = FormulaT(FormulaType::TRUE);
    EXPECT_TRUE(True.isTrue());
    FormulaT False = FormulaT(FormulaType::FALSE);
    EXPECT_TRUE(False.isFalse());

    FormulaT fb1 = FormulaT(b1);
    EXPECT_EQ(FormulaType::BOOL, fb1.getType());
    FormulaT fb2 = FormulaT(b2);
    EXPECT_EQ(FormulaType::BOOL, fb2.getType());
    
    FormulaT nb1 = FormulaT(FormulaType::NOT, fb1);
    EXPECT_EQ(FormulaType::NOT, nb1.getType());
    
    FormulaT Fimpl = FormulaT(FormulaType::IMPLIES, nb1, fb2);
    FormulaT Fand = FormulaT(FormulaType::AND, nb1, fb2);
    FormulaT For = FormulaT(FormulaType::OR, nb1, fb2);
    FormulaT Fxor = FormulaT(FormulaType::XOR, nb1, fb2);
    FormulaT Fiff = FormulaT(FormulaType::IFF, nb1, fb2);
}
