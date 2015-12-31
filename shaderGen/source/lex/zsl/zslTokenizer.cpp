#include "zslTokenizer.h"

#include "ast/abstractSyntaxTree.h"

#include "lex/zsl/zslComments.h"


ZslLexer::Tokenizer::Tokenizer( const std::string &file ) : mSourceFile( file )
{

}

void ZslLexer::Tokenizer::Tokenize( const std::string &line, const std::string &delimiters,
                                    U32 sourceLine )
{
    std::string::size_type position, lastPosition = 0;

    while ( true )
    {
        position = line.find_first_of( delimiters, lastPosition );

        if ( position == std::string::npos )
        {
            position = line.length();
        }

        //if we have at least a bit of data in between
        if ( position != lastPosition )
        {
            mBuffer.push_back( Token( line.substr( lastPosition, position - lastPosition ), mSourceFile, sourceLine ) );
        }

        if ( position == line.length() )
        {
            break;
        }

        lastPosition = position + 1;
    }
}

void ZslLexer::Tokenizer::SubdivideTokens( const std::string &delimiters,
                                           const std::unordered_map< std::string, Token::TokenType > &typemap )
{
    std::vector< Token > newTokens;

    for ( auto it = mBuffer.begin(), itend = mBuffer.end(); it != itend; ++it )
    {
        std::string::size_type position, lastPosition = 0;
        const std::string &token = it->GetString();

        // Do not process if numeric
        if ( Util::IsNumeric( token ) )
        {
            Token origToken = ( *it );

            origToken.SetType( Token::TokenType::Numeric );

            newTokens.push_back( origToken );

            continue;
        }

        while ( true )
        {
            position = token.find_first_of( delimiters, lastPosition );

            const bool foundDelimiter = ( position != std::string::npos );

            position = foundDelimiter ? position : token.length();

            //  push the truncated token
            if ( position != lastPosition )
            {
                Token referenceToken( token.substr( lastPosition, position - lastPosition ),
                                      mSourceFile, it->SourceLineOrigin() );

                // find if the token is of non reference type
                auto refIt = typemap.find( referenceToken.GetString() );

                if ( refIt != typemap.end() )
                {
                    referenceToken.SetType( refIt->second );
                }
                else
                {
                    referenceToken.SetType( Token::TokenType::Identifier );
                }

                newTokens.push_back( referenceToken );
            }

            // update last position
            lastPosition = position + 1;

            if ( foundDelimiter )
            {
                // standard delim token
                Token delimToken( token.substr( position, 1 ),
                                  mSourceFile, it->SourceLineOrigin() );

                // first test if we are dealing with a double token.
                std::string::size_type tokPos = token.find_first_of( delimiters, lastPosition );

                // if sequentially positioned
                if ( tokPos == ( lastPosition ) && lastPosition != token.length() )
                {
                    Token doubleToken( token.substr( position, 2 ),
                                       mSourceFile, it->SourceLineOrigin() );

                    // if we can find the double token
                    if ( typemap.find( doubleToken.GetString() ) != typemap.end() )
                    {
                        delimToken = doubleToken;

                        //inc to account for the double token
                        lastPosition++;
                    }
                }

                // find if the token is of non reference type
                auto delimIt = typemap.find( delimToken.GetString() );

                if ( delimIt != typemap.end() )
                {
                    delimToken.SetType( delimIt->second );
                }

                // also push back the delimiter
                newTokens.push_back( delimToken );
            }

            if ( position == token.length() )
            {
                break;
            }
        }

    }

    mBuffer = newTokens;
}

void ZslLexer::Tokenizer::FilterComments( ASTDriver *driver )
{
    std::vector< Token > newTokens;

    for ( auto it = Begin(), itend = End(); it != itend; ++it )
    {
        //try to interpet comment regions
        if ( HandleCommentRegion( driver, it, itend ) )
        {
            continue;
        }
        else
        {
            // this token is cleared as non comment
            newTokens.push_back( ( *it ) );
        }
    }

    mBuffer = newTokens;
}

size_t ZslLexer::Tokenizer::Size() const
{
    return mBuffer.size();
}

const ZslLexer::Tokenizer::iterator ZslLexer::Tokenizer::Begin() const
{
    return mBuffer.begin();
}

const ZslLexer::Tokenizer::iterator ZslLexer::Tokenizer::End() const
{
    return mBuffer.end();
}

const std::string &ZslLexer::Tokenizer::SourceFileOrigin() const
{
    return mSourceFile;
}

void ZslLexer::Tokenizer::Clear()
{
    mBuffer.clear();
}

const std::vector< ZslLexer::Token > &ZslLexer::Tokenizer::GetBuffer()
{
    return mBuffer;
}