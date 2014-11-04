/**
 * @file UFInstanceManager.cpp
 * @author Gereon Kremer <gereon.kremer@cs.rwth-aachen.de>
 * @author Florian Corzilius <corzilius@cs.rwth-aachen.de>
 * @since 2014-10-30
 * @version 2014-10-30
 */

#include "UFInstanceManager.h"

using namespace std;

namespace carl
{   
    ostream& UFInstanceManager::print( ostream& _out, const UFInstance& _ufi ) const
    {
        assert( _ufi.id() != 0 );
        assert( _ufi.id() < mUFInstances.size() );
        const UFInstanceContent& ufic = *mUFInstances[_ufi.id()];
        _out << "(" << ufic.uninterpretedFunction().name();
        for( auto& arg : ufic.args() )
        {
            _out << " " << arg;
        }
        _out << ")";
        return _out;
    }
    
    UFInstance UFInstanceManager::newUFInstance( const UFInstanceContent* _ufic )
    {
        auto iter = mUFInstanceIdMap.find( _ufic );
        // Check if this uninterpreted function content has already been created
        if( iter != mUFInstanceIdMap.end() )
        {
            delete _ufic;
            return UFInstance( iter->second );
        }
        // Create the uninterpreted function instance
        mUFInstanceIdMap.emplace( _ufic, mUFInstances.size() );
        UFInstance ufi( mUFInstances.size() );
        mUFInstances.push_back( _ufic );
        return ufi;
    }
    
    bool UFInstanceManager::argsCorrect( const UFInstanceContent& _ufic )
    {
        if( !(_ufic.uninterpretedFunction().domain().size() == _ufic.args().size()) )
        {
            return false;
        }
        for( size_t i = 0; i < _ufic.uninterpretedFunction().domain().size(); ++i )
        {
            if( !(_ufic.uninterpretedFunction().domain().at(i) == _ufic.args().at(i).domain()) )
            {
                return false;
            }
        }
        return true;
    }
}