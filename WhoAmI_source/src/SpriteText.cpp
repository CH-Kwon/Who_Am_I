/**
 \file        SpriteText.cpp
 \author      Sehyun Kim
 \par         email: kim4969\@gmail.com
 \par         course: GAM200
 \date        11/22/2017.
 \brief
 All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
 */
#include "SpriteText.hpp"
#include "Graphics.h"
#include "Headers_Components.h"
#include "Object.h"

namespace FindersEngine
{
    SpriteText::SpriteText()
        : Component(CT_SPRITE_TEXT) { GRAPHICS->gameSpriteTexts.push_back(this); }

    SpriteText::~SpriteText() { GRAPHICS->gameSpriteTexts.erase(std::find(GRAPHICS->gameSpriteTexts.begin(), GRAPHICS->gameSpriteTexts.end(), this)); }

    void SpriteText::Init()
    {
        pm_transform = (Transform*)GetOwner()->GetComponent(CT_TRANSFORM);
        if (!pm_transform)
            std::cerr << "SpriteText component initializing failed" << std::endl;
    }

    void SpriteText::Draw(float deltaTime)
    {
        glm::vec3 pos = pm_transform->getPosition();
        glm::vec3 rot = pm_transform->getRotation();
        GRAPHICS->font_system.RenderText(text, pos.x, pos.y, scale, color, rot.z);
    }
}
