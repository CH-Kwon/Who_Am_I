/**
\file        HudController.cpp
\author      jungdae.chur
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/13/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
#include "HudController.h"
#include "../../WhoAmI/Include/GameStateManager.h"
#include "CameraSystem.h"
#include "Collision.h"
#include "Graphics.h"
#include "Hud.h"
#include "Input.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "RigidBody.h"
#include "Texture.h"
#include "Transform.hpp"
#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"
#include <iostream>

#include <algorithm>


#include <iostream>
#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#define WIDTH 1280
#define HEIGHT 640

namespace FindersEngine
{
    using namespace glm;

    namespace
    {
        glm::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec4 red(1.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 blue(0.0f, 0.0f, 1.0f, 1.0f);
    };

    HudController::HudController()
    {
    }

    HudController::~HudController()
    {
    }

    void HudController::Init()
    {
        transform = dynamic_cast<Transform*>(GetOwner()->GetComponent(CT_TRANSFORM));
        hud = dynamic_cast<Hud*>(GetOwner()->GetComponent(CT_HUD));
        hud->RGBA_Color(white);
        collision = dynamic_cast<Collision*>(GetOwner()->GetComponent(CT_COLLISION));
        timer.Init();
    }

    void HudController::Update(float deltaTime)
    {
        suicide(deltaTime);
    }

    void HudController::suicide(float dt)
    {
        lifeTime -= dt;
        if (lifeTime <= 0.0f)
        {
            OBJECT_FACTORY->Destroy(GetOwner());
        }
    }
}
