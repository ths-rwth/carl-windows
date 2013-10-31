#include "Variable.h"
#include "VariablePool.h"

namespace carl
{
    const Variable Variable::NO_VARIABLE = Variable();
    
    std::string varToString(carl::Variable::Arg rhs, bool friendlyVarName)
    {
        return carl::VariablePool::getName(rhs, friendlyVarName);
    }
    
    std::ostream& operator<<(std::ostream& os, carl::Variable::Arg rhs)
    {
        #ifdef CARL_USE_FRIENDLY_VARNAMES
        return os << carl::VariablePool::getName(rhs);
        #else
        return os << "x_" << rhs.getId();
        #endif
    }
}
