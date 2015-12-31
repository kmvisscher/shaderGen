#include "common/util.h"

#include "ast/abstractSyntaxTree.h"

#include "lex/zsl/zslTokenizer.h"
#include "lex/zsl/zslComments.h"

bool ZslLexer::HandleCommentRegion( ASTDriver *driver, Tokenizer::iterator &it, const Tokenizer::iterator &end )
{
    const Token &token = *( it );

    // dual tokens only make sense if they are single character
    if ( token.Size() != 2 )
    {
        return false;
    }

    if ( token.Equals( "//" ) )
    {
        //confirmed comment discard the rest of the tokens on this line
        const U32 currentLineNumber = token.SourceLineOrigin();

        // we do not want to parse the tokens yet, so look
        // at the future token
        for ( ; ( it + 1 ) != end; ++it )
        {
            const Token &futureToken = *( it + 1 );

            if ( futureToken.SourceLineOrigin() != currentLineNumber )
            {
                //this future token is from another line so quit
                break;
            }
        }
    }
    else if ( token.Equals( "/*" ) )
    {
        // multi-line comment so now we have to look for its counterpart
        bool foundCounterPart = false;

        // the counterpart needs two tokens, so look in the future
        // inc as we want to start on a new token
        for ( it++; it != end; ++it )
        {
            const Token &currentToken = *( it );

            if ( currentToken.Equals( "*/" ) )
            {
                //found the counterpart
                foundCounterPart = true;

                break;
            }
            // an error condition is the start of a new multiline comment
            // so check for that
            else if ( currentToken.Equals( "/*" ) )
            {
                // ERROR
                driver->ReportComment( ASTComment( ASTComment::Error, currentToken.SourceLineOrigin(),
                                                   Util::Format( "Start of multi-line comment on line %u expected an [*/], instead a new multi-line comment was started with [/*]",
                                                                 token.SourceLineOrigin() ) ) );
            }
        }

        if ( !foundCounterPart )
        {
            // ERROR
            driver->ReportComment( ASTComment( ASTComment::Error, it->SourceLineOrigin(),
                                               Util::Format( "Start of multi-line comment on line %u expected an [*/], instead no terminus was found",
                                                             token.SourceLineOrigin() ) ) );
        }
    }
    else
    {
        // not a comment region
        return false;
    }

    return true;
}

