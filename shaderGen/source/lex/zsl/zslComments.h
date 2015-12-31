#pragma once
#ifndef __ZSL_LEXCOMMENTS_H__
#define __ZSL_LEXCOMMENTS_H__

#include <string>

class ASTDriver;

namespace ZslLexer
{
    class Tokenizer;

    bool HandleCommentRegion( ASTDriver *driver, Tokenizer::iterator &it, const Tokenizer::iterator &end );

};

#endif