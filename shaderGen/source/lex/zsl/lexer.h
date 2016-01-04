#pragma once
#ifndef __ZSL_LEXER_H__
#define __ZSL_LEXER_H__

#include "lex/zsl/zslRegex.h"

#include <string>

class ASTDriver;
class ASTNode;

namespace ZslLexer
{
    class Tokenizer;


    void HandleBlock( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > &regexNodes );
    void HandleLiteral( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > & );
    void HandleReference( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > & );

    void ConvertUnary( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > & );
    void ConvertBinary( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > &regexNodes );
    void ConvertComparison( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > &regexNodes );
    void ConvertAssignment( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > &regexNodes );

    ASTNode *CreateBlock( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile );
    ASTNode *CreateLiteral( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile );
    ASTNode *CreateReference( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile );
    ASTNode *CreateUnary( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile );
    ASTNode *CreateBinary( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile );
    ASTNode *CreateComparison( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile );
    ASTNode *CreateAssignment( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile );

    void InterpetGroup0( ASTDriver *driver, RegexStream &regexStream );
    void InterpetGroup1( ASTDriver *driver, RegexStream &regexStream );
    void InterpetGroup2( ASTDriver *driver, RegexStream &regexStream );
    void InterpetGroup3( ASTDriver *driver, RegexStream &regexStream );
    void InterpetTokenStream( ASTDriver *driver, const Tokenizer &tokens );

    void ProcessSourceFile( ASTDriver *driver, const std::string &file );

    ASTDriver *ParseSource( const std::string &file );
};

#endif

