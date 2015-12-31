#pragma once
#ifndef __IO_TOKENIZER_H__
#define __IO_TOKENIZER_H__

#include <vector>
#include <string>
#include <unordered_map>

#include "common/types.h"
#include "common/util.h"

#include "zslToken.h"

class ASTDriver;

namespace ZslLexer
{
    class Tokenizer
    {
    public:

        typedef  std::vector< Token >::const_iterator iterator;

        Tokenizer( const std::string &file );

        void Tokenize( const std::string &line, const std::string &delimiters, U32 sourceLine );
        void SubdivideTokens( const std::string &delimiters,
                              const std::unordered_map< std::string, Token::TokenType > &typemap );
        void FilterComments( ASTDriver *driver );
        void Clear();

        const std::string &SourceFileOrigin() const;
        size_t Size() const;
        const iterator Begin() const;
        const iterator End() const;


        const std::vector< Token > &GetBuffer();

    private:

        std::vector< Token > mBuffer;
        std::string mSourceFile;
    };
}

#endif