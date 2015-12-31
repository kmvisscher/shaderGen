#pragma once
#ifndef __ZSL_REGEXPR_H__
#define __ZSL_REGEXPR_H__

#include <vector>
#include <string>

#include "common/types.h"
#include "common/util.h"

#include "zslToken.h"

#include "ast/abstractSyntaxNode.h"

namespace ZslLexer
{
    class Tokenizer;

    enum Associativity
    {
        None,
        LeftToRight,
        RightToLeft
    };

    class RegexNode
    {
    public:

        RegexNode( Token::TokenType type, const Token *token ) :
            mName( Util::Format( "type:%u", ( U32 )type ) ), mNodeLink( nullptr ), mTokenLink( token )
        {}

        RegexNode( const std::string &name, ASTNode *node ) :
            mName( name ), mNodeLink( node ), mTokenLink( nullptr )
        {}


    private:

        std::string mName;
        ASTNode *mNodeLink;
        const Token *mTokenLink;
    };

    class ZslRegexStream
    {
    public:

        ZslRegexStream( const Tokenizer &tokens );

    private:

        std::vector< RegexNode > mRegexStream;
    };
}

#endif