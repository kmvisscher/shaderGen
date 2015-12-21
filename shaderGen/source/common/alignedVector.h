#ifndef __ALGINED_VECTOR_H__
#define __ALGINED_VECTOR_H__

#include "memory/alignedAllocator.h"

#include "math/simd/vectorize.h"

#include <vector>

namespace LibStruct
{
    template< class Interface >
    class AlignedVector : private std::vector< Interface, AlignedAllocator< Interface, SIMD_ALIGNMENT > >
    {
        typedef Interface T;
        typedef std::vector< Interface, AlignedAllocator< Interface, SIMD_ALIGNMENT > > vector;
    public:
    
        AlignedVector(){}
        AlignedVector( size_t n ) :
            vector( n )
        {}
        AlignedVector( size_t n, Interface type ) :
            vector( n, type )
        {}
        virtual ~AlignedVector(){}
    
        using vector::operator[];
        using vector::begin;
        using vector::end;
        using vector::size;
        using vector::resize;
        using vector::capacity;
        using vector::empty;
        using vector::reserve;
        using vector::shrink_to_fit;
        using vector::front;
        using vector::back;
        using vector::data;
        using vector::assign;
        using vector::push_back;
        using vector::pop_back;
        using vector::insert;
        using vector::erase;
        using vector::swap;
        using vector::clear;
        using vector::emplace;
        using vector::emplace_back;
    };

}

#endif