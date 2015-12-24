#include "tokenizer.h"


ZslLexer::Token::Token(const std::string &token, U32 sli) : mToken(token), mSourceLineIndex( sli )
{

}

bool ZslLexer::Token::Equals(const std::string &comp) const
{
    return  comp.compare(mToken) == 0 ? true : false;
}

const std::string &ZslLexer::Token::GetToken() const
{
    return mToken;
}

U32 ZslLexer::Token::SourceLineOrigin() const
{
    return mSourceLineIndex;
}

ZslLexer::Token &ZslLexer::Token::operator=(Token const &rhs)
{
    mToken = rhs.GetToken();

    return *this;
}

void ZslLexer::Tokenizer::Tokenize(const std::string &line, const std::string &delimiters, U32 sourceLine )
{
    std::string::size_type position, lastPosition = 0;

    while (true)
    {
        position = line.find_first_of(delimiters, lastPosition);

        if (position == std::string::npos)
        {
            position = line.length();
        }

        //if we have at least a bit of data in between
        if (position != lastPosition)
        {
            mBuffer.push_back(Token( line.substr(lastPosition, position - lastPosition), sourceLine) );
        }

        if (position == line.length())
        {
            break;
        }

        lastPosition = position + 1;
    }
}

size_t ZslLexer::Tokenizer::Size()
{
    return mBuffer.size();
}


void ZslLexer::Tokenizer::Clear()
{
    mBuffer.clear();
}

const std::vector< ZslLexer::Token > &ZslLexer::Tokenizer::GetBuffer()
{
    return mBuffer;
}