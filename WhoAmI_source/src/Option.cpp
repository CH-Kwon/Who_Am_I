/**
 \file        Option.cpp
 \author      Sehyun Kim
 \par         email: kim4969\@gmail.com
 \par         course: GAM200
 \date        10/11/2017.
 \brief
 Copyright © 2017 DigiPen All rights reserved.
 */
#include "Option.hpp"
#include "Application.h"
#include "Graphics.h"
#include "SoundManager.h"
#include <iostream>
using namespace FindersEngine;

void Option::ResolutionUp()
{
    if (current_index + 1 > RESOL_1920_1080)
        return;
    current_index++;
    SetResolution(static_cast<RESOL>(current_index));
}
void Option::ResolutionDown()
{
    if (current_index - 1 < RESOL_640_360)
        return;
    current_index--;
    SetResolution(static_cast<RESOL>(current_index));
}

void Option::SetResolution(RESOL index)
{
    short i = index;

    SDL_SetWindowSize(APPLICATION->getWindow(), resolutions[i].width, resolutions[i].height);
    SDL_SetWindowPosition(APPLICATION->getWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}


void Option::FullScreenOn()
{
    if (!SDL_SetWindowFullscreen(APPLICATION->getWindow(), SDL_WINDOW_FULLSCREEN))
    {
        std::cerr << "FullScreen On Failed!\n";
        std::cerr << "Error: " << SDL_GetError() << '\n';
    }
}

void Option::FullScreenOff()
{
    if (!SDL_SetWindowFullscreen(APPLICATION->getWindow(), NULL))
    {
        std::cerr << "FullScreen Off Failed!\n";
        std::cerr << "Error: " << SDL_GetError() << '\n';
    }
}

void Option::VolumnUp()
{
    if (volume + VOLUME_STEP > 1.0f)
    {
        volume = 1.0f;
        return;
    }
    volume += VOLUME_STEP;
}

void Option::VolumnDown()
{

    if (volume - VOLUME_STEP < 0.f)
    {
        volume = 0.0f;
        return;
    }
    volume -= VOLUME_STEP;
}

void Option::LightGammaUp()
{
    GRAPHICS->set_ambient_value(GRAPHICS->get_ambient_value() + GAMMA_STEP);
}

void Option::LightGammaDown()
{
    GRAPHICS->set_ambient_value(GRAPHICS->get_ambient_value() - GAMMA_STEP);
}

void Option::OnlyUsingKeyboard()
{
    APPLICATION->TurnOffGamePad();
}

void Option::OnlyUsingGamepad()
{
    APPLICATION->TurnOnGamePad();
}
