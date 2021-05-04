/**
\file        Sprite.cpp
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "Sprite.h"
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
    const glm::vec2 Sprite::DEFAULT_SIZE = glm::vec2(100.f, 100.f);
    const int Sprite::DEFAULT_SPRITE_LAYER = 0;
    Sprite::Sprite()
        : Component(CT_SPRITE) //, radian_theta(0.0f)
          ,
          m_isPerspective(true) // default is true
    {
        GRAPHICS->gameSprites.push_back(this);
    }
    Sprite::~Sprite()
    {
        GRAPHICS->gameSprites.erase(std::find(GRAPHICS->gameSprites.begin(), GRAPHICS->gameSprites.end(), this));
    }
    void Sprite::Init()
    {
        pm_transform = (Transform*)GetOwner()->GetComponent(CT_TRANSFORM);
        if (pm_transform == nullptr)
        {
            std::cerr << "Sprite component initializing failed" << std::endl;
        }

        elapsed_time = blend_alpha_remainded_time;
    }

    //Refer:  loading_images_file_path[] in Texture.h
    void Sprite::LoadTexture(std::string file_path)
    {
        pm_textureID = Texture::GetInstance().GetTexture(file_path);
    }
    void Sprite::render()
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

        //Todo: I will use mipmap later!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, pm_textureID);
    }
    void Sprite::Visible_Switch(bool isVisible)
    {
        m_visible = isVisible;
    }
    void Sprite::RGBA_Color(glm::vec4 color)
    {
        m_rgba_color = color;
    }
    const glm::vec3& Sprite::Size() const
    {
        //Todo: modify size returned by area
        return pm_transform->getScale();
    }

    void Sprite::RotatingMat(glm::mat4& model)
    {
        glm::vec3 rot = pm_transform->getRotation();
        model = glm::rotate(model, rot.x, glm::vec3(1.0f, 0, 0)); //x-axis
        model = glm::rotate(model, rot.y, glm::vec3(0, 1.0f, 0)); //y-axis
        model = glm::rotate(model, rot.z, glm::vec3(0, 0, 1.0f)); //z-axis
    }
};
