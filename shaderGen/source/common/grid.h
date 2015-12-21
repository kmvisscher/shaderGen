#pragma once
#ifndef __ZEFIROS_MATH_GRID_H__
#define __ZEFIROS_MATH_GRID_H__

#include "alignedVector.h"

namespace LibStruct
{
    template< class Interface >
    class Grid2D : private AlignedVector< AlignedVector< Interface > >
    {
        typedef Interface T;
        typedef AlignedVector< AlignedVector< Interface > > vector;
    public:
    
        Grid2D(){}
        virtual ~Grid2D(){}
    
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
        
        
        void DeepClear()
        {
            for (auto it=begin(),itend=end(); it != itend; ++it )
            {
                (*it).clear();
            }
        }
    };

    template< class Interface >
    class Grid3D : private AlignedVector< AlignedVector< AlignedVector< Interface > > >
    {
        typedef Interface T;
        typedef AlignedVector< AlignedVector< AlignedVector< Interface > > > vector;
    public:
    
        Grid3D(){}
        virtual ~Grid3D(){}
    
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
        
        void DeepClear()
        {
            for (auto it=begin(),itend=end(); it != itend; ++it )
            {
                for (auto jt=it->begin(),jtend=it->end(); jt != jtend; ++jt )
                {
                    (*jt).clear();
                }
            }
        }
    };

}



#endif