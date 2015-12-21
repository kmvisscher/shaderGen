#pragma once
#ifndef __AST_SOURCE_COMPOUND_H__
#define __AST_SOURCE_COMPOUND_H__

class ASTSourceCompound
{
public:

    ASTSourceCompound( const U32 &line, const std::string &file ) 
        : mSourceLine( line ), mSourceFile( file ) 
    {
        
    }
    
    virtual ~ASTSourceCompound(){}

private:

    U32 mSourceLine;
    std::string mSourceFile;
};

#endif
