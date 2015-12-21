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

#include "common/directory.h"
#include "common/path.h"

#include <boost/filesystem.hpp>

#include <iostream>

namespace Directory
{

    bool Exists( const std::string &directory )
    {
        bool isDir = boost::filesystem::exists( directory ) && boost::filesystem::is_directory( directory );
        
        return isDir;
    }

    std::vector< std::string > List( const std::string &directory, bool recursive /*= false */ )
    {
        std::vector< boost::filesystem::path > contents = Path::List( directory, recursive );
        std::vector< std::string > directories;

        for ( auto it = contents.begin(), end = contents.end(); it != end; ++it )
        {
            const boost::filesystem::path fsPath = *it;

            if ( boost::filesystem::is_directory( fsPath ) )
            {
                directories.push_back( Path::FixStyle( fsPath.generic_string() ) );
            }
        }

        return directories;
    }

    void Delete( const std::string &filepath )
    {
        if ( Exists( filepath ) )
        {
            try
            {
                boost::filesystem::remove( filepath );
            }
            catch ( const boost::filesystem::filesystem_error & )
            {
                // We tried to delete a non empty folder, which is not allowed with this function
            }
        }
    }

    void DeleteAll( const std::string &filepath )
    {
        if ( Exists( filepath ) )
        {
            boost::filesystem::remove_all( filepath );
        }
    }

    bool Create( const std::string &directory )
    {
        boost::filesystem::path path( directory ), parent;

        if ( directory.back() != '/' || path.has_parent_path() )
        {
            parent = path.parent_path();

            if ( parent.has_parent_path() )
            {
                if ( boost::filesystem::is_directory( parent.parent_path() ) )
                {
                    return boost::filesystem::create_directory( directory );
                }
            }
        }

        return false;
    }

    bool CreateAll( const std::string &directories )
    {
        try
        {
            boost::filesystem::create_directories( directories );
        }
        catch ( const boost::filesystem::filesystem_error & )
        {
            return false;
        }

        return Exists( directories );
    }

    bool Copy( const std::string &from, const std::string &to )
    {
        if ( Exists( from ) && !Exists( to ) )
        {
            if ( boost::filesystem::absolute( from ) != boost::filesystem::absolute( to ) && !Path::IsParent( from, to ) )
            {
                boost::filesystem::copy_directory( from, to );

                return true;
            }
        }

        return false;
    }

    bool Move( const std::string &from, const std::string &to )
    {
        if ( Exists( from ) && !Exists( to ) )
        {
            if ( boost::filesystem::absolute( from ) != boost::filesystem::absolute( to ) && !Path::IsParent( from, to ) )
            {
                boost::filesystem::rename( from, to );

                return true;
            }
        }

        return false;
    }

}