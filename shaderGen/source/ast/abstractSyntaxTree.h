#pragma once
#ifndef __AST_DRIVER_H__
#define __AST_DRIVER_H__

#include <vector>
#include <string>
#include <iostream>

#include "common/types.h"

#include "abstractSyntaxNode.h"

class ASTDriver
{
public:

    template< class T >
    ASTNode * Create()
    {
        ASTNode *result = new T( this, GenIndex() );
        mAllocedNodes.emplace_back( result );
        return result;
    }

    template< class T, class D0 >
    ASTNode * Create( const D0 &d0 )
    {
        ASTNode *result = new T( this, GenIndex(), d0 );
        mAllocedNodes.emplace_back( result );
        return result;
    }
        
    template< class T, class D0, class D1 >
    ASTNode * Create( const D0 &d0, const D1 &d1  )
    {
        ASTNode *result = new T( this, GenIndex(), d0, d1 );
        mAllocedNodes.emplace_back( result );
        return result;
    }
        
    template< class T, class D0, class D1, class D2 >
    ASTNode * Create( const D0 &d0, const D1 &d1, const D2 &d2  )
    {
        ASTNode *result = new T( this, GenIndex(), d0, d1, d2 );
        mAllocedNodes.emplace_back( result );
        return result;
    }

    template< class T, class D0, class D1, class D2, class D3 >
    ASTNode * Create( const D0 &d0, const D1 &d1, const D2 &d2, const D3 &d3  )
    {
        ASTNode *result = new T( this, GenIndex(), d0, d1, d2, d3 );
        mAllocedNodes.emplace_back( result );
        return result;
    }
        
    template< class T, class D0, class D1, class D2, class D3, class D4 >
    ASTNode * Create( const D0 &d0, const D1 &d1, const D2 &d2, const D3 &d3, const D4 &d4  )
    {
        ASTNode *result = new T( this, GenIndex(), d0, d1, d2, d3, d4 );
        mAllocedNodes.emplace_back( result );
        return result;
    }
   
private:

    size_t GenIndex() const
    {
        return mAllocedNodes.size();
    }
    
    std::vector< ASTNode * > mAllocedNodes;
};






#endif