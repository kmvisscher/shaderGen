#include "common/util.h"

#include "ast/abstractSyntaxHub.h"
#include "ast/abstractSyntaxNode.h"
#include "ast/abstractSyntaxTree.h"

#include "lex/zsl/zslTokenizer.h"
#include "lex/zsl/zslCompoundSection.h"

bool ZslLexer::HandleCompoundSection( ASTDriver *driver, Tokenizer::iterator &it )
{
    const Token &token = *( it );

    // compound tokens only make sense if they are single character
    if ( !token.IsChar() )
    {
        return false;
    }

    if ( token.Equals( "{" ) )
    {
        ASTNode *parent = driver->GetScopeNodes().top();

        // add a new scope node
        ASTNode *newHub = driver->Create< ASTHub >( token.SourceLineOrigin(), token.SourceFileOrigin(), "Compound" );

        parent->AddChild( newHub );

        driver->GetScopeNodes().push( newHub );
    }
    else if ( token.Equals( "}" ) )
    {
        // pop the last scope
        driver->GetScopeNodes().pop();
    }
    else
    {
        // not a comment region
        return false;
    }

    return true;
}
