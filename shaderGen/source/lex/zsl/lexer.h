#pragma once
#ifndef __ZSL_LEXER_H__
#define __ZSL_LEXER_H__

#include "ast/abstractSyntaxTree.h"

#include "lex/zsl/tokenizer.h"

#include <sstream>
#include <string>
#include <fstream>

namespace ZslLexer
{
    void ProcessSourceFile(ASTDriver *driver, const std::string &file)
    {
        std::ifstream infile(file);

        std::string line;
        U32 sourceLineIndex = 0;
        while ( std::getline(infile, line) )
        {
            std::cout << line << std::endl;

            sourceLineIndex++;
        }
    }


    ASTDriver * ParseSource(const std::string &file)
    {
        // read file line by line
        ASTDriver *driver = new ASTDriver;

        ProcessSourceFile(driver, file);

        return driver;
    }
};

#endif