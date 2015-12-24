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

    ASTDriver() : mNodeAdvance(0)
    {

    }

    template< class T >
    T * Create()
    {
        T *result = new T( this, GenIndex() );
        Init(result);
        return result;
    }

    template< class T, class D0 >
    T * Create( const D0 &d0 )
    {
        T *result = new T( this, GenIndex(), d0 );
        Init(result);
        return result;
    }
        
    template< class T, class D0, class D1 >
    T * Create( const D0 &d0, const D1 &d1  )
    {
        T *result = new T( this, GenIndex(), d0, d1 );
        Init(result);
        return result;
    }
        
    template< class T, class D0, class D1, class D2 >
    T * Create( const D0 &d0, const D1 &d1, const D2 &d2  )
    {
        T *result = new T( this, GenIndex(), d0, d1, d2 );
        Init(result);
        return result;
    }

    template< class T, class D0, class D1, class D2, class D3 >
    T * Create( const D0 &d0, const D1 &d1, const D2 &d2, const D3 &d3  )
    {
        T *result = new T( this, GenIndex(), d0, d1, d2, d3 );
        Init(result);
        return result;
    }
        
    template< class T, class D0, class D1, class D2, class D3, class D4 >
    T * Create( const D0 &d0, const D1 &d1, const D2 &d2, const D3 &d3, const D4 &d4  )
    {
        T *result = new T( this, GenIndex(), d0, d1, d2, d3, d4 );
        Init(result);
        return result;
    }
   
private:

    template< class T >
    void Init(T *result)
    {
        mAllocedNodes.emplace_back(result);
    }

    size_t GenIndex() 
    {
        return mNodeAdvance++;
    }
    
    size_t mNodeAdvance;

    std::vector< ASTNode * > mAllocedNodes;
};






#endif