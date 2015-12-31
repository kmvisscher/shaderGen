#pragma once
#ifndef __ZSL_COMPOUND_SECTION_H__
#define __ZSL_COMPOUND_SECTION_H__

#include <string>
#include <stack>

class ASTDriver;

namespace ZslLexer
{
    class Tokenizer;

    bool HandleCompoundSection( ASTDriver *driver,  Tokenizer::iterator &it );
};


#endif