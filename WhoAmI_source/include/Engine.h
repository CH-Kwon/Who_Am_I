/**
 \file
 \author
 \par         email:
 \par         course: GAM200
 \date        ?/?/2017
 \brief
 
 */

#pragma once

#ifndef ENGINE_H_
#define ENGINE_H_

#include <vector>
#include <string>

namespace FindersEngine
{
    class System;
    class Engine
    {
        //The Engine manage all systems in the game, updating them, routing msgs,
        //and destory the systems when the game ends
    public:
        Engine();
        ~Engine()
        {
            //nothing...
        }

        //Update all systems
        void GameLoop();

        //Destroy all systems in the engine in reverse to avoid dependency issues
        void DestroyAllSystems();

        //Add systems to the engine
        void AddSystem(System* system);

        //Initialize Engine which means initialize all systems
        void Init();

        void Quit();

        bool isPause;
        bool isResume;
        
        void LoadAssetLog();
        
        const std::vector<std::string>& getImages() const { return IMAGES; }
        const std::vector<std::string>& getSounds() const { return SOUNDS; }

    private:
        //Track all systems the engine uses
        friend class Application;
        friend class Graphics;
        friend  class Texture;
        std::vector<System*> gameSystems;
        //Main Loop
        bool isGameRunning;
        //delta for each frame
        float deltaTime;
        std::vector<std::string> IMAGES;
        std::vector<std::string> SOUNDS;
        float fps;
        float counted_frames;
    };                     //class Engine
    extern Engine* ENGINE; //A global pointer ot the instance of Engine
};                         //namespace FindersEngine
#endif                     // !ENGINE_H_
