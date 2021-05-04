/**
\file        SoundManager.cpp
\author      Changuk Lee
\par         email: leechanguk0510@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "SoundManager.h"
#include "Option.hpp"
#include <fmod_errors.h>
#include <iostream>

#include "Engine.h"
#include "DataPipeline.hpp"

namespace FindersEngine
{
    SoundManager* SOUNDMANAGER = new SoundManager;

    SoundManager::SoundManager()
    {
        SOUNDMANAGER = this;
    }
    SoundManager::~SoundManager()
    {
        pFmod->close();
        delete SOUNDMANAGER;
    }
    void SoundManager::init()
    {
        
        result = System_Create(&pFmod);
        ErrorCheck(result);
        result = pFmod->init(100, FMOD_INIT_NORMAL, NULL);
        ErrorCheck(result);
        timer.Init();
    }

	void SoundManager::loading()
	{
        const std::vector<std::string>& sound_names = ENGINE->getSounds();
        
        for (const std::string& name : sound_names)
        {
            std::string path = SOUND_DIR + name;
            
            int mode = FMOD_DEFAULT;
            
            if (name == "THUNDER_SOUND.mp3" || name == "MENU_SOUND.mp3" || name == "BACKGROUND_SOUND.mp3" || name == "HEART_BEAT.wav")
                mode = FMOD_LOOP_NORMAL;
            musics[name] = Sound_Pack(); // create one
            result = pFmod->createSound(path.c_str(), mode, NULL, &musics[name].sound);
            ErrorCheck(result);
        }
	}

    void SoundManager::play(const std::string& type  /*int type*/)
    {
        
        pFmod->update();

#ifdef _WIN32
        pFmod->playSound(FMOD_CHANNEL_FREE, musics[type].sound, false, &musics[type].ch);
#else   // mac os
        pFmod->playSound(musics[type].sound, NULL, false, &musics[type].ch);
#endif
        musics[type].ch->setVolume(Option::getInstance().volume);
    }

    void SoundManager::playwithtime(const std::string& type, float time)
    {
        if (timer.GetTime() > time)
        {
            pFmod->update();
            
#ifdef _WIN32
            pFmod->playSound(FMOD_CHANNEL_FREE, musics[type].sound, false, &musics[type].ch);
#else   // mac os
            pFmod->playSound(musics[type].sound, NULL, false, &musics[type].ch);
#endif
            musics[type].ch->setVolume(Option::getInstance().volume);
            timer.Init();
            
        }
    }
    
    void SoundManager::stop(const std::string& ch_name)
    {
        musics[ch_name].ch->stop();
    }

    void SoundManager::ErrorCheck(FMOD_RESULT result)
    {
        if (result != FMOD_OK)
        {
            printf("SOUND ERROR");
        }
    }

    void SoundManager::pause(bool ispause)
    {
        for (auto m : musics)
        {
            m.second.ch->setPaused(ispause);
        }
    }
}
