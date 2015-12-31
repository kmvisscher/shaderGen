#pragma once
#ifndef __ZSL_LEXER_H__
#define __ZSL_LEXER_H__

#include <string>

class ASTDriver;

namespace ZslLexer
{
    class Tokenizer;

    void InterpetTokenStream( ASTDriver *driver,  const Tokenizer &tokens );

    void ProcessSourceFile( ASTDriver *driver, const std::string &file );

    ASTDriver *ParseSource( const std::string &file );
};

#endif