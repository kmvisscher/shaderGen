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

#pragma once
#ifndef __ENGINE_DIRECTORY_H__
#define __ENGINE_DIRECTORY_H__

#include <vector>
#include <string>

/// @addtogroup Filesystem
/// @{

/**
 * Namespace collection of functions that handles all the directory (filesystem) specific functions.
 *
 * @note    Every path without an extension would be considered a directory.
 */

namespace Directory
{
    /// @name Queries
    /// @{

    /**
     * Queries if a given directory exists, it will return false on file paths.
     *
     * @param   directory   Pathname of the directory.
     *
     * @return  true if it exists, false if it doesn't.
     */

    bool Exists( const std::string &directory );

    /**
     * List directories in a given directory.
     *
     * @note    The directories can be removed/altered while you process them, so make sure the
     *          directory does exists if you do anything with it.
     *
     * @param   directory   Path of the directory we want to scan.
     * @param   recursive   (optional) Whether we want the scan to be recursively or not, default is
     *                      false.
     *
     * @return  A vector with all the directories in the directory.
     */

    std::vector< std::string > List( const std::string &directory, bool recursive = false );

    /// @}

    /// @name Modifiers
    /// @{

    /**
     * Deletes the given filepath, does nothing when the directory didn't exist. Naturally it won't
     * delete file paths.
     *
     * @param   filepath    The filepath to delete.
     */

    void Delete( const std::string &filepath );

    /**
     * Deletes the given directory recursively, does nothing when the directory didn't exist.
     * Naturally it won't delete file paths.
     *
     * @param   filepath    The filepath to delete.
     */

    void DeleteAll( const std::string &filepath );

    /**
     * Creates the given directory. The uppermost parent path
     * should exist, for the directory to be created.
     *
     * @param   directory   Pathname of the directory.
     *
     * @return  true if it succeeds, false if it fails.
     */

    bool Create( const std::string &directory );

    /**
     * Creates all directories in the given path.
     *
     * For example:
     * @code
     *      Directory::CreateAll( "common/folderA/folderB" );
     * @endcode
     *
     * Will ensure these folders are all created:
     *      - common
     *      - common/folderA
     *      - common/folderA/folderB.
     *
     * @param   directories The directories.
     *
     * @return  true if it succeeds, false if it fails.
     */

    bool CreateAll( const std::string &directories );

    /**
     * Copies the given directory, to an other directory. Won't do anything
     * when the from directory doesn't exist, or when the 'to' directory alread exists.
     *
     * @note    Contents won't be copied to the other folder.
     *
     * @param   from    The source of the directory.
     * @param   to      Where to copy the directory to.
     *
     * @return  true if it succeeds, false if it fails.
     */

    bool Copy( const std::string &from, const std::string &to );

    /**
     * Moves the given directory, and all of its contents, to an other directory. Won't do anything
     * when the from directory doesn't exist, or when the 'to' directory alread exists.
     *
     * @param   from    The source of the directory.
     * @param   to      Where to move the directory to.
     *
     * @return  true if it succeeds, false if it fails.
     */

    bool Move( const std::string &from, const std::string &to );

    /// @}

}

/// @}

#endif