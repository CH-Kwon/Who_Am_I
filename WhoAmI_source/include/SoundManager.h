/**
\file        SoundManager.h
\author      Changuk Lee
\par         email: leechanguk0510@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#ifndef SoundManager_h
#define SoundManager_h
#include "Timer.hpp"
#include <fmod.hpp>
#include <string>
#include <map>

using namespace FMOD;

namespace FindersEngine
{
	class SoundManager
	{
	public:
		SoundManager();
		~SoundManager();
                void init();
                void loading();
                void play(const std::string& type);
                void playwithtime(const std::string& type, float time);
                void stop(const std::string& ch_name);
                void ErrorCheck(FMOD_RESULT result);
                void pause(bool ispause);

        
        struct Sound_Pack
        {
            Channel* ch;
            Sound* sound;
        };
        std::map<std::string, Sound_Pack> musics;
    private:
        friend class Option;
        System* pFmod;


        FMOD_RESULT result;
        Timer timer;
    };

    extern SoundManager* SOUNDMANAGER;
}
#endif
