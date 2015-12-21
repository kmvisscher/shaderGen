#pragma once

#ifndef __DEFINES_H__
#define __DEFINES_H__

#if _PLATFORM_WIN 

#define FORCE_INLINE __forceinline

#elif _PLATFORM_UNIX

#define FORCE_INLINE __attribute__((always_inline))

#endif


#endif