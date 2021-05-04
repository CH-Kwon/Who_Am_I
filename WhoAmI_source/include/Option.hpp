/**
 \file        Option.cpp
 \author      Sehyun Kim
 \par         email: kim4969\@gmail.com
 \par         course: GAM200
 \date        10/11/2017.
 \brief
 Copyright © 2017 DigiPen All rights reserved.
 */

#ifndef Option_hpp
#define Option_hpp
#include <vector>

namespace FindersEngine {
    
    struct Resolution { int width; int height; };
    
    enum RESOL : short { RESOL_640_360, RESOL_800_450, RESOL_960_540, RESOL_1024_576, RESOL_1280_720, RESOL_1600_900, RESOL_1920_1080 };
    
class Option
{
public:
    static Option& getInstance()
    {
        static Option option;
        return option;
    }
    
    void ResolutionDown();
    void ResolutionUp();

    void FullScreenOn();
    void FullScreenOff();   //Window Mode
    
    void VolumnUp();
    void VolumnDown();
    
    void LightGammaUp();
    void LightGammaDown();
    
    void OnlyUsingKeyboard();
    void OnlyUsingGamepad();
    
    // player's control mode
    
private:
	friend class SoundManager;
    void SetResolution(RESOL index);
    Option()
    {
        Resolution r;
        r.width = 640;
        r.height = 360;
        resolutions.push_back(r);
        r.width = 800;
        r.height = 450;
        resolutions.push_back(r);
        r.width = 960;
        r.height = 540;
        resolutions.push_back(r);
        r.width = 1024;
        r.height = 576;
        resolutions.push_back(r);
        r.width = 1280;
        r.height = 720;
        resolutions.push_back(r);
        r.width = 1600;
        r.height = 900;
        resolutions.push_back(r);
        r.width = 1920;
        r.height = 1080;
        resolutions.push_back(r);
    }
    Option(const Option&) = delete;
    Option& operator=(const Option&) = delete;
    
    std::vector<Resolution> resolutions;
    short current_index = RESOL_1280_720;
    const float VOLUME_STEP = 0.2f;
	float volume = 1.f;
    const float GAMMA_STEP = 0.1f;
    
    float gamma = 0.5f;
};
}

#endif /* Option_hpp */
