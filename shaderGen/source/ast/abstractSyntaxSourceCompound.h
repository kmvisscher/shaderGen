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

    U32 GetSourceLine() const
    {
        return mSourceLine;
    }

    void SetSourceLine( U32 line )
    {
        mSourceLine = line;
    }

    const std::string &GetSourceFile() const
    {
        return mSourceFile;
    }

    void SetSourceFile( const std::string &file )
    {
        mSourceFile = file;
    }

    virtual ~ASTSourceCompound() {}

private:

    U32 mSourceLine;
    std::string mSourceFile;
};

#endif
