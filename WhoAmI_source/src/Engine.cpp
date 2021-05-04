/**
\file
\author
\par         email:
\par         course: GAM200
\date        ?/?/2017
\brief

*/

#include "DataPipeline.hpp"

#include "Engine.h"
#include "Object.h"
#include "SoundManager.h"

//DEBUG_TOOL
#include "DebugUtil.h"
#include "Headers_Controllers.h"
#include "Headers_Systems.h"
#include "ObjectFactory.h"
#include <cassert>
#include <iostream>

#include "imgui.h"
#include "jsonReader.h"
#include <fstream>



namespace FindersEngine
{
    const int SCREEN_FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

    Engine* ENGINE = nullptr;

    Engine::Engine() : isGameRunning(true), deltaTime(0.f), counted_frames(0.f)
    {
        assert(ENGINE == nullptr && "More than onc instance of the Engine cannot be created!");
        ENGINE = this;
        isPause = false;
        isResume = false;
    }

    void Engine::GameLoop()
    {
        using namespace glm;

        //Timer::GetInstance().Init();
        LTimer timer;
        LTimer cptimer;

        timer.start();

        while (isGameRunning)
        {
            //Calculate the amount of time took for one iteration in previous time
            //deltaTime = Timer::GetInstance().GetDeltaTime();
            cptimer.start();

            counted_frames++;

            float avgFPS = counted_frames / (timer.getTicks() / 1000.f);
            if (isPause)
            {
                deltaTime = 0.0f;
            }
            else
            {
                deltaTime = 1 / avgFPS;
            }

            for (auto sys : gameSystems)
            {
                sys->Update(deltaTime);
            }
            int frameTicks = cptimer.getTicks();

            if (frameTicks < SCREEN_TICKS_PER_FRAME)
            {
                //Wait remaining time
                SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
            }
        }

        OBJECT_FACTORY->DestroyAllObjects();
    }

    void Engine::DestroyAllSystems()
    {
        //Delete all systems (in reverse) that they were added in
        //to minimize dependency problems between systems
        for (auto sys = gameSystems.rbegin(); sys < gameSystems.rend(); ++sys)
            delete *sys;

        //std::cout << "Cheking Memory Leak(It will end after 5 seconds...)" << std::endl;

        //	  DEBUG_MEMORY_LEAK_CHECKS();
        //SDL_Delay(5000); //5 seconds...
    }

    void Engine::AddSystem(System* system)
    {
        //Add a system to the Engine to be updated every frame
        gameSystems.push_back(system);
    }

    void Engine::Init() // Load!
    {
        

        
        JSONREADER->jsonReaderMain();

        Input::GetInstance().Init();

                                       //Todo: Add systems...
        
        

        AddSystem(new Application());
        //AddSystem(new jsonReader());

        SOUNDMANAGER->init();
        SOUNDMANAGER->loading();
        Texture::GetInstance().Load(); //Todo: should move in Load
       
        //Add Systems before graphics
        AddSystem(new ObjectFactory());
        AddSystem(new GameLogic());
        AddSystem(new GameState());
        AddSystem(new Physics());
        AddSystem(new Graphics());



        for (auto sys : gameSystems)
            sys->Init();
    }

    void Engine::Quit()
    {
        isGameRunning = false;
    }
    
    void Engine::LoadAssetLog()
    {
        const auto image_log_path = "./Log/image_log.txt";
        std::fstream image_fileout(image_log_path, std::ios_base::out);
        
        if (!image_fileout)
        {
            std::cerr << "Failed to opend " << image_log_path << ".\n";
        }
        
        for (auto image : IMAGES)
        {
            image_fileout << image << '\n';
        }
        
        const auto sound_log_path = "./Log/sound_log.txt";
        std::fstream sound_fileout(sound_log_path, std::ios_base::out);
        
        if (!sound_fileout)
        {
            std::cerr << "Failed to opend " << sound_log_path << ".\n";
        }
        
        for (auto sound : SOUNDS)
        {
            sound_fileout << sound << '\n';
        }
    }
}
