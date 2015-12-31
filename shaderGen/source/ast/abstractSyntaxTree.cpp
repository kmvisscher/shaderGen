#include "abstractSyntaxTree.h"

#include "ast/abstractSyntaxHub.h"


ASTDriver::ASTDriver() : mNodeAdvance( 0 ), mInvalidSource( false )
{
    mScopeNodes.push( Create< ASTHub >( 0, "Program", "Root" ) );
}
