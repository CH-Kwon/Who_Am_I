/**
\file        Hud.cpp
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
#include "Hud.h"
#include "Graphics.h"
#include "Headers_Components.h"
#include "Object.h"
#include "Texture.h"
#include <algorithm>
#include <iostream>

#include "lodepng.h" // loading for png files
#include <glm/gtc/matrix_transform.hpp>

namespace FindersEngine
{
    const glm::vec2 Hud::DEFAULT_SIZE = glm::vec2(100.f, 100.f);
    const int Hud::DEFAULT_Hud_LAYER = 0;

    Hud::Hud() : Component(CT_HUD) { GRAPHICS->gameHuds.push_back(this); }

    Hud::~Hud() { GRAPHICS->gameHuds.erase(std::find(GRAPHICS->gameHuds.begin(), GRAPHICS->gameHuds.end(), this)); }

    void Hud::Init()
    {
        pm_transform = (Transform*)GetOwner()->GetComponent(CT_TRANSFORM);
        if (pm_transform == nullptr)
            std::cerr << "Hud component initializing failed" << std::endl;
        elapsed_time = blend_alpha_remainded_time;
    }

    const glm::vec3& Hud::Size() const { return pm_transform->getScale(); }

    void Hud::LoadTexture(std::string file_path) { pm_textureID = Texture::GetInstance().GetTexture(file_path); }

    void Hud::render()
    {
        if (is_blend_alpha)
        {
            elapsed_time -= m_delta_time;
            if (elapsed_time <= 0)
                elapsed_time = 0;
            float alpha_blend_ratio = ((blend_alpha_remainded_time - elapsed_time) / blend_alpha_remainded_time);
            blend_alpha = (1.f - alpha_blend_ratio);
        }
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, pm_textureID);
    }

    void Hud::RotatingMat(glm::mat4& model)
    {
        glm::vec3 rot = pm_transform->getRotation();
        model = glm::rotate(model, rot.x, glm::vec3(1.0f, 0, 0)); //x-axis
        model = glm::rotate(model, rot.y, glm::vec3(0, 1.0f, 0)); //y-axis
        model = glm::rotate(model, rot.z, glm::vec3(0, 0, 1.0f)); //z-axis
    }
};
