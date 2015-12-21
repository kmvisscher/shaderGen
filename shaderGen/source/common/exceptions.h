#pragma once
#ifndef __APIEXCEPTIONS_H__
#define __APIEXCEPTIONS_H__

#include <exception>
#include <string>

#include <Poco/Exception.h>

namespace LibStruct
{

    typedef Poco::RuntimeException ApiInputException;

}

#endif