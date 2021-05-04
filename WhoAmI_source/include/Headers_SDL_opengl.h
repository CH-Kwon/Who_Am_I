/**
\file        Headers_SDL_opengl.h
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef LIBRARY_SDL2_OPENGL_H_
#define LIBRARY_SDL2_OPENGL_H_


#ifdef _WIN32
//define for window 32/64-bit(common)

//#include <SDL_opengl.h>

#ifdef _WIN64
//define for window 64bit(only)
#endif // WIN32 \
       // define for window 32bit(only)

#elif __APPLE__
#if TARGET_OS_MAC
//#include <SDL2/SDL_opengl.h>
// Other kinds of Mac OS
#elif TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_IPHONE
// iOS device
#else
#error "Unknown Apple Platform!"
#endif

#elif __linux__
// Ubuntu, Debian,
// centos, Fedora, RedHat,
#elif __unix__
// Solaris, HP...
#else
#error "Unknown Platform!"
#endif // End Platform Settings...

#endif // !LIBRARY_SDL2_IMAGE_H_
