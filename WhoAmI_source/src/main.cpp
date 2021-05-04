/**
\file        main.cpp
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
//Library input list

#ifdef _WIN32
#pragma comment(lib, "FindersEngine.lib")
#ifdef WIN32

#endif // WIN32

#ifdef _WIN64
//#pragma comment(lib, "opengl32.lib")
#else
#pragma comment(lib, "opengl32.lib")
#endif // WIN64

#elif __APPLE__
//#pragma comment(lib, "libFindersEngine.a")
#pragma comment(lib, "opengl32.lib")
#endif

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "SDL2.lib")

#include "DebugUtil.h"
#include <iostream>

#ifdef _WIN32
#include <FindersEngine.h> // This is our engine:)

#ifdef _DEBUG

#else //release
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#endif

#else
#include "FindersEngine.h"
#endif

int main(int argc, char* argv[])
{

    argc, argv;

    //Make namespace's shortcut, do not use using namespace ~ due to conflictions...
    namespace FE = FindersEngine;

    //Create Engine
    FE::Engine* ENGINE = new FE::Engine();

    //Initialize the Engine and
    ENGINE->Init();
    //Todo: Create initial game state, main menu

    //Main Loop
    ENGINE->GameLoop();

    //Todo: Shutdown the Engine
    //Also means shutdown and clean all systems
    ENGINE->DestroyAllSystems();
    
    //Todo: Delete the Engine
    delete ENGINE;
    return 0;
}
