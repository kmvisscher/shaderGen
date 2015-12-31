#include "zslToken.h"



ZslLexer::Token::Token( const std::string &token, const std::string &file, U32 sli ) :
    mToken( token ), mSourceFile( file ), mSourceLineIndex( sli )
{

}

bool ZslLexer::Token::Equals( const std::string &comp ) const
{
    return  comp.compare( mToken ) == 0 ? true : false;
}

bool ZslLexer::Token::IsChar() const
{
    return Size() == 1;
}

void ZslLexer::Token::SetType( const TokenType &type )
{
    mTokenType = type;
}

ZslLexer::Token::TokenType ZslLexer::Token::GetType() const
{
    return mTokenType;
}

size_t ZslLexer::Token::Size() const
{
    return mToken.size();
}

const std::string &ZslLexer::Token::GetString() const
{
    return mToken;
}

U32 ZslLexer::Token::SourceLineOrigin() const
{
    return mSourceLineIndex;
}

const std::string &ZslLexer::Token::SourceFileOrigin() const
{
    return mSourceFile;
}

ZslLexer::Token &ZslLexer::Token::operator=( Token const &rhs )
{
    mTokenType = rhs.GetType();
    mToken = rhs.GetString();
    mSourceFile = rhs.SourceFileOrigin();
    mSourceLineIndex = rhs.SourceLineOrigin();

    return *this;
}


