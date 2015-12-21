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

#include "common/file.h"
#include "common/path.h"
#include "common/util.h"

#include <boost/filesystem.hpp>

#include <fstream>

namespace File
{

    bool Exists( const std::string &filepath )
    {
        return //Path::HasExtension( filepath ) &&
            boost::filesystem::is_regular_file( filepath ) &&
            boost::filesystem::exists( filepath );
    }

    U64 GetSize( const std::string &filepath )
    {
        if ( Exists( filepath ) )
        {
            return boost::filesystem::file_size( filepath );
        }

        return 0;
    }

    bool IsEmpty( const std::string &filepath )
    {
        return boost::filesystem::is_empty( filepath );
    }

    bool AreEqual( const std::string &filePath1, const std::string &filePath2 )
    {
        if ( !File::Exists( filePath1 ) || !File::Exists( filePath2 ) )
        {
            return false;
        }

        std::fstream file1( filePath1 ), file2( filePath2 );
        std::string string1, string2;

        bool equal = true;

        while ( !file1.eof() && equal )
        {
            std::getline( file1, string1 );
            std::getline( file2, string2 );

            if ( string1 != string2 )
            {
                equal = false;
            }
        }

        return equal;
    }

    bool IsSame( const std::string &filePath1, const std::string &filePath2 )
    {
        return boost::filesystem::equivalent( filePath1, filePath2 );
    }

    std::string ReadAllText( const std::string &filepath )
    {
        // Stop if there is nothing to read
        // and just return a null string
        if ( !Exists( filepath ) )
        {
            return "";
        }

        // Open and read the file
        std::ifstream ifs( filepath );
        const std::string content( ( std::istreambuf_iterator< char >( ifs ) ),
                                   ( std::istreambuf_iterator< char >() ) );
        return content;
    }

    std::time_t GetLastModified( const std::string &path )
    {
        return boost::filesystem::last_write_time( path );
    }

    std::vector< std::string > List( const std::string &directory, bool recursive /*= false */ )
    {
        const std::vector< boost::filesystem::path > contents = Path::List( directory, recursive );
        std::vector< std::string > resultContents;

        for ( auto it = contents.begin(), end = contents.end(); it != end; ++it )
        {
            const boost::filesystem::path fsPath = *it;

            if ( boost::filesystem::is_regular_file( fsPath ) )
            {
                resultContents.push_back( fsPath.generic_string() );
            }
        }

        return resultContents;
    }

    void SetLastModified( const std::string &path, std::time_t time )
    {
        boost::filesystem::last_write_time( path, time );
    }

    void Clear( const std::string &filepath )
    {
        // only if the file exists
        if ( Exists( filepath ) )
        {
            std::ofstream f( filepath );
            f.close();
        }
    }

    void Delete( const std::string &filepath )
    {
        if ( Exists( filepath ) )
        {
            boost::filesystem::remove( filepath );
        }
    }

    bool Move( const std::string &from, const std::string &to, const bool overwrite /*= false */ )
    {
        if ( Exists( from ) && boost::filesystem::absolute( from ) != boost::filesystem::absolute( to ) )
        {
            const bool exists = Exists( to );

            if ( !exists )
            {
                boost::filesystem::rename( from, to );

                return true;
            }
            else if ( exists && overwrite )
            {
                File::Delete( to );
                boost::filesystem::rename( from, to );

                return true;
            }
        }

        return false;
    }

    bool Copy( const std::string &from, const std::string &to, bool overwrite /*= false */ )
    {
        if ( Exists( from ) && boost::filesystem::absolute( from ) != boost::filesystem::absolute( to ) )
        {
            const bool exists = Exists( to );

            if ( !exists || ( exists && overwrite ) )
            {
                boost::filesystem::copy_file( from, to, boost::filesystem::copy_option::overwrite_if_exists );
                return true;
            }
        }

        return false;
    }

}