/**
\file        MessageController.cpp
\author      Chiho Kwon
\par         email: erpo0811@gmail.com
\par         course: GAM200
\date        12/15/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "MessageController.h"
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
    const auto width = GRAPHICS -> AREA_SIZE_MAX;
    const auto height = GRAPHICS -> AREA_SIZE_MAX;

    namespace
    {
        glm::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec4 red(1.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 blue(0.0f, 0.0f, 1.0f, 1.0f);
    };

    MessageController::MessageController()
    {
    }

    MessageController::~MessageController()
    {
    }

    void MessageController::ControllAlpha(Object* object, float distance)
    {
        Object* player = OBJECT_FACTORY->GetObjectID(100);

        Transform* player_transform = new Transform();
        player->AddComponent(player_transform);
        Transform* obj_transform = new Transform();
        object->AddComponent(obj_transform);

        glm::vec3 distance_ = glm::vec3(0.f, 0.f, 0.f);
        distance_.x = (player_transform->getPosition().x * width - obj_transform->getPosition().x * width);
        distance_.y = (player_transform->getPosition().y * height - obj_transform->getPosition().x * height);

        float dist_length = glm::length(distance_);
    }

    void MessageController::Init()
    {
        transform = dynamic_cast<Transform*>(GetOwner()->GetComponent(CT_TRANSFORM));
        hud = dynamic_cast<Hud*>(GetOwner()->GetComponent(CT_HUD));
        hud->RGBA_Color(white);
        collision = dynamic_cast<Collision*>(GetOwner()->GetComponent(CT_COLLISION));
    }

    void MessageController::Update(float deltaTime)
    {
    }
}
