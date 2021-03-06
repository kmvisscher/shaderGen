//
// Format.h
//
// $Id: //poco/1.4/Foundation/include/Poco/Format.h#2 $
//
// This file is modified by Zefiros Software!
//
// Library: Foundation
// Package: Core
// Module:  Format
//
// Definition of the format freestanding function.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef __ENGINE_FORMAT_H__
#define __ENGINE_FORMAT_H__

#include <boost/any.hpp>

#include <vector>
#include <string>

/// @addtogroup Utility
/// @{

namespace Util
{

    /**
    * @name String Formatters
    * This function implements the c sprintf like formatting in a type
    * safe way. There are different versions available each with a different argument count,
    * supporting up to eight formatting variables. If eight variables are not enough, one can also
    * use a vector to give all the formatting variables.
    *
    *  A formatting variable must be prefixed with a '\%' character, after the '\%' character.
    *  The format should follow the following syntax:
    *
    *  @code
    *       %[<index>][<flags>][<width>][.<precision>][<modifier>]<type>
    *  @endcode
    *
    *  Where only the "<type>" declaration is required and the rest is optional.
    *
    *  The following types are available for usage.
    *       - \%b Holds a Boolean value ( bool; true = 1, false = 0 ).
    *       - \%c Holds a character ( char/U8 ).
    *       - \%i Holds a signed decimal integer ( S* ).
    *       - \%d Holds a signed decimal integer ( S* ).
    *       - \%o Holds an unsigned octal integer ( U* ).
    *       - \%u Holds an unsigned decimal integer ( U* ).
    *       - \%x Holds an unsigned hexadecimal integer ( lowercase; U* ).
    *       - \%X Holds an unsigned hexadecimal integer ( uppercase; U* ).
    *       - \%e Holds a floating point value in the form [-]d.ddde[<sign>]dd[d] ( F* ).
    *       - \%E Holds a floating point value in the form [-]d.dddE[<sign>]dd[d] ( F* ).
    *       - \%f Holds a floating point value in the form [-]d.ddd.dddd ( F* ).
    *       - \%s Holds a std::string.
    *       - \%z Holds a std::size_t value.
    *
    *  The following flags are supported:
    *      - - Left align the result within the given field width.
    *      - + Prefix the output value with a sign (+ or -) if the output value is of a signed type.
    *      - 0 if width is prefixed with0, zeros are added until the minimum width is reached.
    *      - # For o, x, X, the # flag prefixes any nonzero output value with 0, 0x, or 0X, respectively;
    *          For e, E, f, the flag forces the output value to contain a decimal point in all cases.
    *
    *  The following modifiers are supported:
    *      - (none) The argument is char/U8 (%c), S32 (%d, %i), unsigned (%o, %u, %x, %X), double (%e, %E, %f) or string (%s).
    *      - l The argument is long (%d, %i), unsigned long (%o, %u, %x, %X) or long double (%e, %E, %f).
    *      - L The argument is long long (%d, %i), unsigned long long (%o, %u, %x, %X).
    *      - h The argument is short (%d, %i), unsigned short (%o, %u, %x, %X) or float (%e, %E, %f).
    *      - ? The argument is any signed or unsigned int, short, long or 64-bit integer (%d, %i, %o, %x, %X).
    *
    *  The width is a nonnegative number specifying the amount of characters that should be printed at minimum. The
    *  remaining space is either filled with whitespace or zeros, depending on the set flags.
    *
    * Example:
    * @code
    * std::string str;
    * str = Util::Format( "Hello %s", std::string( "World!" ) ); // str now holds "Hello World!"
    * str = Util::Format( "This is a test float: %f", 10.0f ); // str now holds "This is a test float: 10.0"
    * str = Util::Format( "second: %[1]d, first: %[0]d", 1, 2 ); // str now holds "second: 2, first: 1"
    * @endcode
    *
    * @param  fmt         Holds the formatter string containing the data and the places of where to put the
    *                     formatter variables.
    * @param  v[1,...,8]  Holds the Poco::Any object with the value encapsulated. The Poco::Any acts as a
    *                     type safe void *.
    *
    * @return The formatted string.
    *
    * @warning   @li   Don't try to use a c-string or any other variable type than the ones listed in the
    *                  function description, since the formatter won't know how to convert those types
    *                  and therefore throw an exception.
    *
    * @warning   @li   The behaviour when the formatting variables count and the amount of variables
    *                  referenced in the formatting string differ, is undefined, so it is best to avoid those
    *                  situations.
    */

    ///@{

    std::string Format( const std::string &fmt, const boost::any &value );

    std::string Format( const std::string &fmt, const boost::any &value1, const boost::any &value2 );

    std::string Format( const std::string &fmt, const boost::any &value1, const boost::any &value2,
                        const boost::any &value3 );

    std::string Format( const std::string &fmt, const boost::any &value1, const boost::any &value2,
                        const boost::any &value3, const boost::any &value4 );

    std::string Format( const std::string &fmt, const boost::any &value1, const boost::any &value2,
                        const boost::any &value3, const boost::any &value4, const boost::any &value5 );

    std::string Format( const std::string &fmt, const boost::any &value1, const boost::any &value2,
                        const boost::any &value3, const boost::any &value4, const boost::any &value5, const boost::any &value6 );

    std::string Format( const std::string &fmt, const boost::any &value1, const boost::any &value2,
                        const boost::any &value3, const boost::any &value4, const boost::any &value5, const boost::any &value6,
                        const boost::any &value7 );

    std::string Format( const std::string &fmt, const boost::any &value1, const boost::any &value2,
                        const boost::any &value3, const boost::any &value4, const boost::any &value5, const boost::any &value6 ,
                        const boost::any &value7, const boost::any &value8 );

    std::string Format( const std::string &fmt, const boost::any &value1, const boost::any &value2,
                        const boost::any &value3, const boost::any &value4, const boost::any &value5, const boost::any &value6 ,
                        const boost::any &value7, const boost::any &value8, const boost::any &value9 );
                        
    std::string Format( const std::string &fmt, const boost::any &value1, const boost::any &value2,
                        const boost::any &value3, const boost::any &value4, const boost::any &value5, const boost::any &value6 ,
                        const boost::any &value7, const boost::any &value8, const boost::any &value9, const boost::any &value10 );                     

    std::string Format( const std::string &fmt, const boost::any &value1, const boost::any &value2,
                        const boost::any &value3, const boost::any &value4, const boost::any &value5, const boost::any &value6 ,
                        const boost::any &value7, const boost::any &value8, const boost::any &value9, const boost::any &value10, const boost::any &value11 );
                        
    std::string Format( const std::string &fmt, const boost::any &value1, const boost::any &value2,
                        const boost::any &value3, const boost::any &value4, const boost::any &value5, const boost::any &value6 ,
                        const boost::any &value7, const boost::any &value8, const boost::any &value9, const boost::any &value10, const boost::any &value11,
                        const boost::any &value12 );
    /**
     * This function is a bit different from the other String Formatters. There isn't a predefined number
     * of formatting variables used, since you can just fill the vector with as many variables as you like.
     * This function is used internally by the other String Formatters.
     *
     * @see     String Formatters
     *
     * @param   fmt Describes the format to use.
     * @param   v   The const std::vector< boost::any > & to process.
     *
     * @return  The formatted string.
     */

    void Format( std::string &result, const std::string &fmt, const std::vector< boost::any > &values );

    /// @}
}

/// @}

#endif