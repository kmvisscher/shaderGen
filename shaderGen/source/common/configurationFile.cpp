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

#include "common/configurationFile.h"
#include "common/util.h"
#include "common/file.h"

//#include "api/console.h"

#include <fstream>

LibStruct::ConfigurationFile::ConfigurationFile()
{
}

std::string LibStruct::ConfigurationFile::GetString( const std::string &key ) const
{
    auto it = mStrings.find( key );

    if ( it != mStrings.end() )
    {
        return it->second;
    }
    else
    {
        //Console::Warning( LOG( "The given key is either no string or doesn't exist." ) );
    }

    return "";
}


bool LibStruct::ConfigurationFile::GetBool( const std::string &key ) const
{
    auto it = mBools.find( key );

    if ( it != mBools.end() )
    {
        return it->second;
    }
    else
    {
        //Console::Warning( LOG( "The given key is either no bool or doesn't exist." ) );
    }

    return false;
}

F32 LibStruct::ConfigurationFile::GetFloat( const std::string &key ) const
{
    auto it = mFloats.find( key );

    if ( it != mFloats.end() )
    {
        return it->second;
    }
    else
    {
        //Console::Warning( LOG( "The given key is either no float or doesn't exist." ) );
    }

    return 0.0f;
}

S32 LibStruct::ConfigurationFile::GetInt( const std::string &key ) const
{
    auto it = mInts.find( key );

    if ( it != mInts.end() )
    {
        return it->second;
    }
    else
    {
        //Console::Warning( LOG( "The given key is either no int or doesn't exist." ) );
    }

    return 0;
}

bool LibStruct::ConfigurationFile::IsStringKey( const std::string &key ) const
{
    return mStrings.find( key ) != mStrings.end();
}

bool LibStruct::ConfigurationFile::IsFloatKey( const std::string &key ) const
{
    return mFloats.find( key ) != mFloats.end();
}

bool LibStruct::ConfigurationFile::IsBoolKey( const std::string &key ) const
{
    return mBools.find( key ) != mBools.end();
}

bool LibStruct::ConfigurationFile::IsIntKey( const std::string &key ) const
{
    return mInts.find( key ) != mInts.end();
}

bool LibStruct::ConfigurationFile::HasKey( const std::string &key ) const
{
    return mKeysUsed.find( key ) != mKeysUsed.end();
}

LibStruct::ConfigurationFile::ParseError LibStruct::ConfigurationFile::SetString( const std::string &key,
        const std::string &value,
        bool changeInFile /* = true */ )
{
    if ( IsStringKey( key ) )
    {
        mStrings[ key ] = value;

        if ( changeInFile )
        {
            return ChangeKey( key, Util::Format( "\"%s\"", value ) ) ? ParseError::None : ParseError::FailedToOpenFile;
        }

        return ParseError::None;
    }

    return ParseError::InvalidKey;
}


LibStruct::ConfigurationFile::ParseError LibStruct::ConfigurationFile::SetBool( const std::string &key, bool value,
        bool changeInFile /* = true */ )
{
    if ( IsBoolKey( key ) )
    {
        mBools[ key ] = value;

        if ( changeInFile )
        {
            const std::string strValue = value ? "true" : "false";

            if ( ChangeKey( key, strValue ) )
            {
                return ParseError::None;
            }

            return ParseError::FailedToOpenFile;
        }


        return ParseError::None;
    }

    return ParseError::InvalidKey;
}

LibStruct::ConfigurationFile::ParseError LibStruct::ConfigurationFile::SetFloat( const std::string &key, F32 value,
        bool changeInFile /* = true */ )
{
    if ( IsFloatKey( key ) )
    {
        mFloats[ key ] = value;

        if ( changeInFile )
        {
            if ( ChangeKey( key, Util::ToString( value ) ) )
            {
                return ParseError::None;
            }

            return ParseError::FailedToOpenFile;
        }

        return ParseError::None;
    }

    return ParseError::InvalidKey;
}

LibStruct::ConfigurationFile::ParseError LibStruct::ConfigurationFile::SetInt( const std::string &key, S32 value,
        bool changeInFile /* = true */ )
{
    if ( IsIntKey( key ) )
    {
        mInts[ key ] = value;

        if ( changeInFile )
        {
            if ( ChangeKey( key, Util::ToString( value ) ) )
            {
                return ParseError::None;
            }

            return ParseError::FailedToOpenFile;
        }

        return ParseError::None;
    }

    return ParseError::InvalidKey;
}

bool LibStruct::ConfigurationFile::AddStringKey( const std::string &key, const std::string &defaultValue,
        const std::string &comment /*= ""*/ )
{
    if ( HasKey( key ) || key.empty() )
    {
        return false;
    }

    mKeysUsed[ key ]    = false;
    mComments[ key ]    = comment;
    mStrings[ key ]     = defaultValue;

    mKeys.push_back( key );

    return true;
}

bool LibStruct::ConfigurationFile::AddBoolKey( const std::string &key, bool defaultValue,
        const std::string &comment /*= ""*/ )
{
    if ( HasKey( key ) || key.empty() )
    {
        return false;
    }

    mKeysUsed[ key ]    = false;
    mComments[ key ]    = comment;
    mBools[ key ]       = defaultValue;

    mKeys.push_back( key );

    return true;
}

bool LibStruct::ConfigurationFile::AddFloatKey( const std::string &key, F32 defaultValue,
        const std::string &comment /*= ""*/ )
{
    if ( HasKey( key ) || key.empty() )
    {
        return false;
    }

    mKeysUsed[ key ]    = false;
    mComments[ key ]    = comment;
    mFloats[ key ]      = defaultValue;

    mKeys.push_back( key );

    return true;
}

bool LibStruct::ConfigurationFile::AddIntKey( const std::string &key, S32 defaultValue,
        const std::string &comment /*= ""*/ )
{
    if ( HasKey( key ) || key.empty() )
    {
        return false;
    }

    mKeysUsed[ key ]    = false;
    mComments[ key ]    = comment;
    mInts[ key ]        = defaultValue;

    mKeys.push_back( key );

    return true;
}

bool LibStruct::ConfigurationFile::Load( const std::string &filePath, const std::string &configName,
        ErrorHandler errorHandler /*= nullptr */ )
{
    mFilePath   = filePath;
    mConfigName = configName;

    std::ifstream file( mFilePath );

    size_t lineN = 1;
    std::string line;

    if ( file.is_open() )
    {
        for ( ; getline( file, line ); ++lineN )
        {
            std::string temp = line;

            const size_t startComment = RemoveComment( temp );

            if ( temp.empty() || Util::IsWhiteSpace( temp ) )
            {
                continue;
            }

            if ( !ParseLine( temp, lineN, startComment, errorHandler ) )
            {
                file.close();

                return false;
            }
        }
    }

    file.close();

    // Add all keys we couldn't find in the configuration file
    return FixUnsetKeys( line, lineN );
}

bool LibStruct::ConfigurationFile::ParseLine( const std::string &line, size_t lineNumber, size_t commentStart,
        void ( *errorHandler )( ParseError, const std::string &, const std::string &, std::size_t,
                                const std::string & ) )
{
    size_t seperator = line.find( "=" );

    if ( seperator == line.npos )
    {
        // No seperator means the file is corrupt, however
        // we can try to read the rest and see if
        // that is functional
        if ( errorHandler )
        {
            errorHandler( ParseError::NoSeperator, mConfigName, line, lineNumber, "" );
        }

        return true;
    }

    const std::string key     = Util::Trim( line.substr( 0, seperator ) );
    const std::string value   = Util::Trim( line.substr( seperator + 1, commentStart ) );

    if ( !HasKey( key ) )
    {
        if ( key == "" )
        {
            if ( errorHandler )
            {
                errorHandler( ParseError::NoKey, mConfigName, key, lineNumber, value );
            }

            return true;
        }
        else
        {
            // The file is either corrupt, or has an old key pair in the
            // configuration, just show a warning, keep calm and carry on.
            if ( errorHandler )
            {
                errorHandler( ParseError::NotRegistered, mConfigName, key, lineNumber, value );
            }

            return true;
        }
    }

    if ( mKeysUsed[ key ] != false )
    {
        // There shouldn't be duplicate keys read
        if ( errorHandler )
        {
            errorHandler( ParseError::IsDuplicateKey, mConfigName, key, lineNumber, value );
        }

        return true;
    }

    if ( value == "" )
    {
        if ( errorHandler )
        {
            errorHandler( ParseError::NoValue, mConfigName, key, lineNumber, value );
        }

        return true;
    }

    if ( IsStringKey( key ) )
    {
        if ( (value[0] == '\"' && value[ value.length() - 1 ] == '\"') ||  (value[0] == '\'' &&
                value[ value.length() - 1 ] == '\'') )
        {
            mStrings[ key ] = value.substr( 1, value.length() - 2 );
        }
        else
        {
            if ( errorHandler )
            {
                errorHandler( ParseError::InvalidString, mConfigName, key, lineNumber, value );
            }

            return false;
        }

        mKeysUsed[ key ] = true;
    }
    else if ( IsBoolKey( key ) )
    {
        if ( value == "true" || value == "false" )
        {
            mBools[ key ] = value == "true" ? true : false;
        }
        else if ( value == "0" || value == "1" )
        {
            mBools[ key ] = value == "1" ? true : false;
        }
        else
        {
            if ( errorHandler )
            {
                errorHandler( ParseError::InvalidBool, mConfigName, key, lineNumber, value );
            }

            return false;
        }

        mKeysUsed[ key ] = true;
    }
    else if ( IsFloatKey( key ) )
    {
        try
        {
            mFloats[ key ] = Util::FromString< F32 >( value );
        }
        catch ( const std::invalid_argument & )
        {
            if ( errorHandler )
            {
                errorHandler( ParseError::InvalidFloat, mConfigName, key, lineNumber, value );
            }

            return false;
        }

        mKeysUsed[ key ] = true;
    }
    else if ( IsIntKey( key ) )
    {
        try
        {
            mInts[ key ] = Util::FromString< S32 >( value );
        }
        catch ( const std::invalid_argument & )
        {
            if ( errorHandler )
            {
                errorHandler( ParseError::InvalidInt, mConfigName, key, lineNumber, value );
            }

            return false;
        }

        mKeysUsed[ key ] = true;
    }

    return true;
}

size_t LibStruct::ConfigurationFile::GetCommentPosition( const std::string &line ) const
{
    std::string cur     = "";
    std::string prev    = "";
    S32 countQ1 = 0;
    S32 countQ2 = 0;

    for ( size_t i = 0; i < line.length(); ++i )
    {
        cur = line[i];

        // filter out comments in strings such as: '#'
        if ( cur == "'" && prev != "\\" )
        {
            ++countQ1;
        }
        // filter out comments in strings such as: "#"
        else if ( cur == "\"" && prev != "\\" )
        {
            ++countQ2;
        }
        else
        {
            if ( cur == "#" && ( countQ1 & 0x01 ) == 0 && ( countQ2 & 0x01 ) == 0 )
            {
                return i;
            }
        }

        prev = cur;
    }

    return line.npos;
}

size_t LibStruct::ConfigurationFile::RemoveComment( std::string &line ) const
{
    if ( line.find( '\'' ) != line.npos || line.find( '\"' ) != line.npos )
    {
        const size_t commentPos = GetCommentPosition( line );

        if ( commentPos != line.npos )
        {
            line.erase( commentPos, line.npos );
        }

        return commentPos;
    }
    else
    {
        const size_t pos = line.find( '#' );

        if ( pos != line.npos )
        {
            line.erase( pos, line.npos );
        }

        return line.npos;
    }
}

bool LibStruct::ConfigurationFile::ChangeKey( const std::string &key, const std::string &value ) const
{
    if ( !File::Exists( mFilePath ) )
    {
        return false;
    }

    std::string line, tmpFile;
    std::ifstream filein( mFilePath );
    std::ofstream fileout( tmpFile );

    if ( filein.is_open() && fileout.is_open() )
    {
        if ( !filein.eof() )
        {
            getline( filein, line );
        }

        bool shouldContinue = true;

        while ( shouldContinue )
        {
            std::string nextline;
            getline( filein, nextline );

            const size_t seperator = line.find( "=" );

            if ( seperator == line.npos )
            {
                if ( filein.eof() && nextline.empty() )
                {
                    shouldContinue = false;
                }
                else
                {
                    fileout << line << std::endl;
                }
            }
            else
            {
                std::string comment = "";
                const std::string tkey  = Util::Trim( line.substr( 0, seperator ) );

                size_t commentPos = GetCommentPosition( line );

                if ( commentPos != line.npos )
                {
                    comment = Util::Trim( line.substr( commentPos, line.npos ) );
                }

                if ( tkey == key )
                {
                    fileout << key << " = " <<  value << comment;
                }
                else
                {
                    fileout << line;
                }

                if ( !filein.eof() )
                {
                    fileout  << std::endl;
                }
                else
                {
                    shouldContinue = false;
                }
            }

            line = nextline;
        }

        filein.close();
        fileout.close();

        File::Move( tmpFile, mFilePath, true );
    }
    else
    {
        return false;
    }

    return true;
}

bool LibStruct::ConfigurationFile::FixUnsetKeys( const std::string &lastLine, std::size_t lineCount )
{
    bool success = true;
    std::vector< std::pair< std::string, std::string > > usedKeys;

    for ( const std::string &key : mKeys )
    {
        if ( mKeysUsed[ key ] == false )
        {
            std::string value;

            if ( IsBoolKey( key ) )
            {
                value = mBools[ key ] ? "true" : "false";
            }
            else if ( IsFloatKey( key ) )
            {
                value = Util::ToString( mFloats[ key ] );
            }
            else if ( IsIntKey( key ) )
            {
                value = Util::ToString( mInts[ key ] );
            }
            else if ( IsStringKey( key ) )
            {
                value = Util::Format( "\"%s\"", mStrings[ key ] );
            }

            usedKeys.push_back( std::pair< std::string, std::string >( key, value ) );
        }
    }

    if ( !usedKeys.empty() )
    {
        std::ofstream file( mFilePath, std::ios::out | std::ios::app );

        if ( file.is_open() )
        {
            for ( auto it = usedKeys.begin(), end = usedKeys.end(); it != end; )
            {
                const std::pair< std::string, std::string > &keyValue = *it;
                const std::string &key = keyValue.first;
                const std::string &value = keyValue.second;

                if ( mKeysUsed[ key ] == false )
                {

                    if ( it == usedKeys.begin() && !Util::IsWhiteSpace( lastLine ) && lineCount != 0 )
                    {
                        file << "\n\n";
                    }

                    if ( !mComments[ key ].empty() )
                    {
                        file << "# " << Util::Replace( mComments[ key ], "\n", "\n# " ) << "\n";
                    }

                    file << key << " = " << value;

                    if ( ++it != usedKeys.end() )
                    {
                        file << std::endl << std::endl;
                    }
                }
            }
        }
        else
        {
            success = false;
        }

        file.close();
    }

    return success;
}