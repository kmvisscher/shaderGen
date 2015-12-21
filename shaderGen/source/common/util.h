/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2015 Koen Visscher, Paul Visscher and individual contributors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @endcond
 */

#pragma once
#ifndef __UTIL_H__
#define __UTIL_H__

#include "common/format.h"
#include "common/types.h"

#include <sstream>
#include <string>
#include <vector>

/// @addtogroup Utility
/// @{


/// @addtogroup Macros
/// @{

/// @name Preprocessing
/// @{

/// Evil msvc bug fix hackery
#define ___EXPAND( x ) x

#define ___CONCAT( a, b ) a ## b

/**
 * A macro that concats two other macro names.
 *
 * @param   a   The first macro.
 * @param   b   The second macro.
 */

#define CONCAT( a, b ) ___CONCAT( a, b )

#define ___VA_SIZE( _1, _2, _3, _4, _5, _6, __count, ... ) __count

/**
 * A macro that counts the amount of arguments given in a
 * variable argument macro.
 */

#define VA_SIZE( ... ) ___EXPAND( ___VA_SIZE( __VA_ARGS__, _6, _5, _4, _3, _2, _1 ) )

/**
 * A macro that allows us to overload macros on a given amount of arguments.s
 *
 * Example:
 * @code
 * #define OVERLOAD(...) VA_SELECT( OVERLOAD, __VA_ARGS__ )
 * #define OVERLOAD_1( a )      foobar( a )
 * #define OVERLOAD_2( a, b )   foobar( a, b )
 * @endcode
 *
 * @note    The preprocessor does not differentiate between zero and one argument!
 *
 * @param   macroName   The name of the macro we are going to overload.
 */

#define VA_SELECT( macroName, ... ) CONCAT( macroName, VA_SIZE(__VA_ARGS__) )(__VA_ARGS__)

/// @}

/// @name Bitflags
/// @{

/**
 * A macro that checks if a bit flag is set on a flag holder. The flag 0x00 will always return
 * as set.
 *
 * @code
 *      IS_SET( 0x01 | 0x02, 0x01 | 0x02 ); //  returns true
 * @endcode
 *
 * @param   flag        The flags.
 * @param   flagvalue   The flag value.
 */

#define IS_SET( flag, flagvalue ) ( ( (flag) & (flagvalue) ) == (flagvalue) )

/**
 * A macro that checks whether one of the given flags is set. Here the flag 0x00 is never set.
 *
 * @code
 *      HAS_SET( 0x01 | 0x02, 0x01 | 0x02 | 0x04 ); //  returns true
 * @endcode
 *
 * @param   flag        The flag.
 * @param   flagvalues  The flagvalues.
 */

#define HAS_SET( flag, flagvalues ) ( ( (flag) & (flagvalues) ) != 0 )

/// @}

/// @name Freeing Memory
/// @{

/**
 * A macro that defines checks if a pointer exists before releasing it
 * and sets it to nullptr.
 *
 * @param   ptr The pointer.
 */

#define SAFE_RELEASE( ptr ) if( ptr ) { ptr->Release(); ptr = nullptr; }

/**
 * A macro that releases the pointer if it exists, deletes it and sets it to nullptr
 *
 * @param   ptr The pointer to delete.
 */

#define SAFE_RELEASE_DELETE( ptr )  if( ptr ) { ptr->Release(); delete ptr; ptr = nullptr; }

/**
 * A macro that deletes a pointer and sets it to nullptr.
 *
 * @param   ptr The pointer.
 */

#define SAFE_DELETE( ptr ) { delete ptr; ptr = nullptr; }

/**
 * A macro that deletes an array pointer and sets it to nullptr.
 *
 * @param   ptr The pointer.
 */

#define SAFE_ARRAY_DELETE( ptr ) { delete[] ptr; ptr = nullptr; }

/**
 * Throws an exception is a more stylish way :).
 *
 * @param   exception   The exception.
 */

#define BLOODY_HELL( exception ) throw(exception)

/// @}


/// @}

/**
 *A collection of utility functions.
 */
namespace Util
{
    /// @name String converters
    /// @{

    /**
     * Convert this object into a string representation.
     *
     * @tparam  typename    T   Type to convert to string.
     * @param   value       T   The value to convert.
     *
     * @return  The value as a string.
     */

    template <typename tT>
    std::string ToString( const tT &value )
    {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    template<>
    std::string ToString< F32 >( const F32 &value );

    template<>
    std::string ToString< F64 >( const F64 &value );

    template<>
    std::string ToString< S32 >( const S32 &value );

    template<>
    std::string ToString< S64 >( const S64 &value );

    template<>
    std::string ToString< U32 >( const U32 &value );

    template<>
    std::string ToString< U64 >( const U64 &value );

    /**
     * Converts a string to the given type.
     *
     * @tparam  typename    T  Type of the typename t.
     * @param   str The string to convert to the given type.
     *
     * @return  The to the type converted string.
     */

    template <typename tT>
    tT FromString( const std::string &str )
    {
        std::istringstream ss( str );
        tT result;
        return ss >> result ? result : 0;
    }

    template<>
    F32 FromString< F32 >( const std::string &str );

    template<>
    F64 FromString< F64 >( const std::string &str );

    template<>
    S32 FromString< S32 >( const std::string &str );

    template<>
    S64 FromString< S64 >( const std::string &str );

    template<>
    U32 FromString< U32 >( const std::string &str );

    template<>
    U64 FromString< U64 >( const std::string &str );

    /**
     * Converts a std::wstring to a std::string.
     *
     * @param   wstr    The wstring to convert.
     *
     * @return  The string.
     */

    std::string WStringToString( const std::wstring &wstr );

    /**
     * Converts a std::string to a std::wstring.
     *
     * @param   str   The string to convert.
     *
     * @return  The wstring.
     */

    std::wstring StringToWString( const std::string &str );

    /// @}

    /// @addtogroup String utilities
    /// @{

    /**
     * Query if 'string' is white space.
     *
     * @param   string  The string.
     *
     * @return  true if white space, false if not.
     */

    bool IsWhiteSpace( const std::string &str );

    std::string Trim( const std::string &str );

    std::vector< std::string > StringSplit( const std::string &str, char sep, bool trim = false );

    std::string Replace( const std::string &str, const std::string &search, const std::string &format );

    /**
     * Capitalises the given string, by uppercasing the first letter.
     *
     * @param   str The string.
     *
     * @return  The capitalised string.
     */

    std::string Capitalise( std::string str );

    /// @}

    /// @addtogroup Traits
    /// @{

    /**
     * Determines whether the child type can be used when we use the
     * base type as the base class. This holds true when the child class
     * derives from the parent class, or is the same class.
     *
     * @tparam  tChild  Type of the child.
     * @tparam  tParent Type of the base.
     *
     * The member value holds true if it is accepted, false otherwise.
     */
    template< typename tChild, typename tParent >
    struct IsChildParent
    : std::integral_constant < bool, ( std::is_base_of<tParent, tChild >::value ||
                                       std::is_same< tChild, tParent >::value ) >
      {
      };

    /// @}

    size_t HashCombine( size_t const &seed, size_t const &val );
    
    std::string FromFlags( const U8  convFlags );
    std::string FromFlags( const U32 convFlags );
    std::string FromFlags( const U64 convFlags );
    
    S32 CountFlags( const U64 convFlags );

};

/// @}

#endif