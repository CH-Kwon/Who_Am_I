/**
 \file
 \author
 \par         email:
 \par         course: GAM200
 \date        ?/?/2017
 \brief
 
 */

#pragma once

#ifdef _WIN32
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "SDL2.lib")
#endif

#ifndef SYSTEM_H_
#define SYSTEM_H_

namespace FindersEngine
{
    class System
    {
    public:
        //Initialize the System

        virtual void Init() = 0;

        //All Systems are updated every frame
        virtual void Update(float deltaTime) = 0;

        //All Systems need a virtual destructor to their destructors called
        virtual ~System()
        {
            // nothing...
        }
    }; //class System

};     //namespace FindersEngine
#endif // !SYSTEM_H_
