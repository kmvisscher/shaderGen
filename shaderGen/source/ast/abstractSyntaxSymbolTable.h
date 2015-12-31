#pragma once
#ifndef __ABSTRACT_SYNTAX_SYMBOLS__
#define __ABSTRACT_SYNTAX_SYMBOLS__

#include "abstractSyntaxNode.h"

#include <string>
#include <vector>

class TypeSymbol
{
public:

    TypeSymbol( const std::string &name, const ASTNode::ASTDataType type ) :
        mName( name ), mType( type )
    {

    }

private:

    std::string mName;
    ASTNode::ASTDataType mType;
};

class FunctionSymbol
{
public:

    FunctionSymbol( const std::string &name, const std::vector< TypeSymbol > &parameters ) :
        mName( name ), mParameters( parameters )
    {

    }

private:

    std::string mName;
    const std::vector< TypeSymbol > mParameters
};

class ASTSymbols
{
public:


private:


};

#endif