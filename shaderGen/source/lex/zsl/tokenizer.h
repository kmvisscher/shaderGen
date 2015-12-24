#pragma once
#ifndef __IO_TOKENIZER_H__
#define __IO_TOKENIZER_H__

#include <vector>
#include <string>

#include "common/types.h"


namespace ZslLexer
{
    class Token
    {
    public:

        explicit Token(const std::string &token, U32 sli );

        Token &operator=(Token const &rhs);

        template< class T >
        T  GetValue() const
        {
            return Util::FromString< T >(mToken);
        }

        const std::string &GetToken() const;

        U32 SourceLineOrigin() const;

        bool Equals(const std::string &comp) const;

    private:

        std::string mToken;
        U32 mSourceLineIndex;
    };

    class Tokenizer
    {
    public:

        void Tokenize(const std::string &line, const std::string &delimiters, U32 sourceLine );
        void Clear();

        size_t Size();

        const std::vector< Token > &GetBuffer();

    private:

        std::vector< Token > mBuffer;
    };
}

#endif