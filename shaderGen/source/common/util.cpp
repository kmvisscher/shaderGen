/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2014 Koen Visscher, Paul Visscher and individual contributors.
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

#include "common/types.h"
#include "common/util.h"

#include <boost/algorithm/string.hpp>
#include <iostream>

template<>
std::string Util::ToString( const F32 &value )
{
    return std::to_string( value );
}

template<>
std::string Util::ToString( const F64 &value )
{
    return std::to_string( value );
}

template<>
std::string Util::ToString( const S32 &value )
{
    return std::to_string( value );
}

template<>
std::string Util::ToString( const S64 &value )
{
    return std::to_string( value );
}

template<>
std::string Util::ToString( const U32 &value )
{
    return std::to_string( value );
}

template<>
std::string Util::ToString( const U64 &value )
{
    return std::to_string( value );
}

template<>
F32 Util::FromString( const std::string &str )
{
    return std::stof( str );
}

template<>
F64 Util::FromString( const std::string &str )
{
    return std::stod( str );
}

template<>
S32 Util::FromString( const std::string &str )
{
    return std::stoi( str );
}

template<>
S64 Util::FromString( const std::string &str )
{
    return std::stoll( str );
}

template<>
U32 Util::FromString( const std::string &str )
{
    return std::stoi( str );
}

template<>
U64 Util::FromString( const std::string &str )
{
    return std::stoull( str );
}

std::string Util::WStringToString( const std::wstring &wstr )
{
    return std::string( wstr.begin(), wstr.end() );
}

std::wstring Util::StringToWString( const std::string &s )
{
    std::wstring ws;
    ws.assign( s.begin(), s.end() );
    return ws;
}

bool Util::IsWhiteSpace( const std::string &str )
{
    std::string trim = str;
    boost::trim( trim );
    return trim == "";
}

std::string Util::Trim( const std::string &str )
{
    std::string nstr = str;
    boost::algorithm::trim( nstr );
    return nstr;
}

std::string Util::Replace( const std::string &str, const std::string &search, const std::string &format )
{
    std::string nstr = str;
    boost::algorithm::replace_all( nstr, search, format );
    return nstr;
}

std::string Util::Capitalise( std::string str )
{
    str[0] = ( char )toupper( str[0] );
    return str;
}

namespace boost
{
    void throw_exception( std::exception const &e )
    {
        throw e;
    }
}

size_t Util::HashCombine( size_t const &seed, size_t const &val )
{
    //rotating hash combine!
    return seed ^ ( val + 0x9e3779b9 + ( seed << 6 ) + ( seed >> 2 ) );
}

std::vector< std::string > Util::StringSplit( const std::string &str, char sep, bool trim /*= false */ )
{
    std::vector< std::string > output;

    std::string::size_type pos = 0, prevPos = 0;

    //loop over all delimiter positions
    while ( ( pos = str.find( sep, prevPos + 1 ) ) != std::string::npos )
    {   
        std::string token = str.substr( prevPos, pos - prevPos );

        if ( trim )
        {
            token = Trim( token );
        }

        output.push_back( token );

        prevPos = ( pos + 1 );
    }

    //wont catch the last bit
    std::string token = str.substr( prevPos, str.size() );

    if ( trim )
    {
        token = Trim( token );
    }

    output.push_back( token );

    return output;
}

std::string Util::FromFlags( const U8 convFlags )
{
	std::string rstring;
	
	for ( U32 i=0; i < 8; ++i )
	{
		if ( convFlags & ( 1 << i ) )
			
			rstring += '1';
		else
			rstring += '0';
		
	}
	
	return rstring;
}

std::string Util::FromFlags( const U32 convFlags )
{
	std::string rstring;
	
	for ( U32 i=0; i < 32; ++i )
	{
		if ( convFlags & ( 1 << i ) )
			
			rstring += '1';
		else
			rstring += '0';
		
	}
	
	return rstring;
}

std::string Util::FromFlags( const U64 convFlags )
{
	std::string rstring;
	
	for ( U32 i=0; i < 64; ++i )
	{
		if ( convFlags & ( (U64)1 << i ) )
			
			rstring += '1';
		else
			rstring += '0';
		
	}
	
	return rstring;
}

//http://stackoverflow.com/questions/109023/how-to-count-the-number-of-set-bits-in-a-32-bit-integer
S32 BitCount( S32 i )
{
     i = i - ((i >> 1) & 0x55555555);
     i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
     return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

S32 Util::CountFlags( const U64 convFlags )
{
    S32 count1 = BitCount( (S32)convFlags );
    S32 count2 = BitCount( (S32)(convFlags >> 32 ) );
    return count1+count2;
}
