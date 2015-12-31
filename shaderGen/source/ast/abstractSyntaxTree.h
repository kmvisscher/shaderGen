#pragma once
#ifndef __AST_DRIVER_H__
#define __AST_DRIVER_H__

#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include "common/types.h"

#include "abstractSyntaxNode.h"

class ASTComment
{
public:

    enum Level
    {
        Hint,
        Warning,
        Error
    };

    ASTComment( Level level, U32 lineOrig, const std::string &msg ) :
        mLevel( level ), mSourceLine( lineOrig ), mMsg( msg )
    {}

    Level GetLevel() const
    {
        return mLevel;
    }

    U32 GetSourceLine() const
    {
        return mSourceLine;
    }

    const std::string &GetMsg() const
    {
        return mMsg;
    }

private:

    Level mLevel;
    U32 mSourceLine;
    std::string mMsg;
};

class ASTDriver
{
public:

    ASTDriver();

    template< class T >
    T *Create()
    {
        T *result = new T( this, GenIndex() );
        Init( result );
        return result;
    }

    template< class T, class D0 >
    T *Create( const D0 &d0 )
    {
        T *result = new T( this, GenIndex(), d0 );
        Init( result );
        return result;
    }

    template< class T, class D0, class D1 >
    T *Create( const D0 &d0, const D1 &d1 )
    {
        T *result = new T( this, GenIndex(), d0, d1 );
        Init( result );
        return result;
    }

    template< class T, class D0, class D1, class D2 >
    T *Create( const D0 &d0, const D1 &d1, const D2 &d2 )
    {
        T *result = new T( this, GenIndex(), d0, d1, d2 );
        Init( result );
        return result;
    }

    template< class T, class D0, class D1, class D2, class D3 >
    T *Create( const D0 &d0, const D1 &d1, const D2 &d2, const D3 &d3 )
    {
        T *result = new T( this, GenIndex(), d0, d1, d2, d3 );
        Init( result );
        return result;
    }

    template< class T, class D0, class D1, class D2, class D3, class D4 >
    T *Create( const D0 &d0, const D1 &d1, const D2 &d2, const D3 &d3, const D4 &d4 )
    {
        T *result = new T( this, GenIndex(), d0, d1, d2, d3, d4 );
        Init( result );
        return result;
    }

    std::stack < ASTNode * > &GetScopeNodes()
    {
        return mScopeNodes;
    }

    void ReportComment( const ASTComment &comment )
    {
        // if an error occured
        if ( comment.GetLevel() == ASTComment::Level::Error )
        {
            mInvalidSource = true;
        }

        mComments.push_back( comment );
    }

    const std::vector< ASTComment > &GetComments() const
    {
        return mComments;
    }

    bool DriverIsValid() const
    {
        return !mInvalidSource;
    }

private:

    template< class T >
    void Init( T *result )
    {
        mAllocedNodes.emplace_back( result );
    }

    size_t GenIndex()
    {
        return mNodeAdvance++;
    }

    size_t mNodeAdvance;
    bool mInvalidSource;

    std::vector< ASTNode * > mAllocedNodes;
    std::stack < ASTNode * > mScopeNodes;
    std::vector< ASTComment > mComments;
};






#endif