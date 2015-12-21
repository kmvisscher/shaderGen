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
#ifndef __ENGINE_FILE_H__
#define __ENGINE_FILE_H__

#include "common/types.h"
#include "common/path.h"

#include <fstream>
#include <vector>
#include <string>
#include <ctime>

/// @addtogroup Filesystem
/// @{

/**
 * Namespace collection of function that handles all file(system) specific functions.
 *
 * @note    A file should always have an extensions, otherwise it will be handled as a directory by some functions.
 */

namespace File
{

    /// @name Queries
    /// @{

    /**
     * Queries if a given file exists, requires to point to a file and not a directory since it will
     * return false otherwise. For a path to be considered to point to a file, one should always specify
     * an extension.
     *
     * @param   filepath    The pathname of the file.
     *
     * @return  true if it exists, false otherwise.
     */

    bool Exists( const std::string &filepath );

    /**
     * Gets the file size, if it exists, in bytes. If the file doesn't exists, the size returned
     * will be 0.
     *
     * @note    Takes the filepath as-is.
     *
     * @param   filePath    The pathname of the file.
     *
     * @return  The file size in bytes.
     */

    U64 GetSize( const std::string &filepath );

    /**
     * Query if the file on the given filepath is empty.
     *
     * @note    Takes the filepath as-is.
     *
     * @param   filepath    The filepath.
     *
     * @return  true if empty, false if not.
     */

    bool IsEmpty( const std::string &filepath );

    /**
     * Check whether the contents of two files are equal, however this function is only meant
     * to work on text files.
     *
     * @note    Takes the filepath as-is
     *
     * @param   filePath1   The first file path.
     * @param   filePath2   The second file path.
     *
     * @return  true if the files are equal, false otherwise.
     */

    bool AreEqual( const std::string &filePath1, const std::string &filePath2 );

    /**
     * Query if whether both given filepaths point to the same physical file.
     *
     * @note    Takes the filepath as-is.
     *
     * @param   filePath1   The first file path.
     * @param   filePath2   The second file path.
     *
     * @return  true if same, false if not.
     */

    bool IsSame( const std::string &filePath1, const std::string &filePath2 );

    /**
     * Reads a whole text file and puts it in a string. If the file doesn't exist it will return an
     * empty string.
     *
     * @note    Takes the filepath as-is.
     *
     * @param   filepath    The filepath.
     *
     * @return  The file contents in a string.
     */

    std::string ReadAllText( const std::string &filepath );

    /**
     * Gets the last modified.
     *
     * @note    Takes the filepath as-is.
     *
     * @param   path    Full pathname of the file.
     *
     * @return  The last modified.
     */

    std::time_t GetLastModified( const std::string &path );

    /**
     * List al files in the given directory, either recursively or not recursive
     * as indicated by the user. (defaults to non-recursive)
     *
     * @note    Takes the filepath as-is
     *
     * @note    The files can be removed/altered while you process them, so make sure the file does
     *          exists if you do anything with it.
     *
     * @param   directory   Pathname of the directory.
     * @param   recursive   (optional) whether the directory scan should be recursive.
     *
     * @return  A vector with all the files in the directory.
     */

    std::vector< std::string > List( const std::string &directory, bool recursive = false );

    /// @}

    /// @name Modifiers
    /// @{

    /**
     * Sets the time on which the file is last modified.
     *
     * @note    Takes the filepath as-is.
     *
     * @param   path    Full pathname of the file.
     * @param   time    The time.
     */

    void SetLastModified( const std::string &path, std::time_t time );

    /**
     * Clears the file from all data, if the file on the filepath exists, otherwise it won't do
     * anything.
     *
     * @note    Takes the filepath as-is
     *
     * @param   filepath    The path to the file.
     */

    void Clear( const std::string &filepath );

    /**
     * Deletes the file, if it exists, described by filepath.
     *
     * @note    Takes the filepath as-is
     *
     * @param   filepath    The filepath.
     */

    void Delete( const std::string &filepath );

    /**
     * Moves a file from the given path to the new path. When there is already a file on the new
     * path, the overwrite parameter decides whether the old file will be overwritten or not. Also
     * the from path and the to path can't be the same.
     *
     * @note    Takes the filepath as-is
     *
     * @param   from        The source of the file.
     * @param   to          Where to move the file to.
     * @param   overwrite   (optional) Overwrite the file if it already exists.
     *
     * @return  true if it succeeds, false if it fails.
     */

    bool Move( const std::string &from, const std::string &to, const bool overwrite = false );

    /**
     * Copies a file from the given path to other path. When there is already a file on the new
     * path, the overwrite parameter decides whether the old file will be overwritten or not. Also
     * the from path and the to path can't be the same.
     *
     * @note    Takes the filepath as-is
     *
     * @param   from        The source of the file.
     * @param   to          Where to copy the file to.
     * @param   overwrite   (optional) Overwrite the file if it already exists.
     *
     * @return  true if it succeeds, false if it fails.
     */

    bool Copy( const std::string &from, const std::string &to, bool overwrite = false );

    /// @}
}

/// @}

#endif