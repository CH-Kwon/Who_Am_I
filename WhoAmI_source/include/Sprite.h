/**
\file        SpriteText.h
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once

#ifndef SPRITE_H_
#define SPRITE_H_

#include "Component.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>

namespace FindersEngine
{
    enum VIEWPORT_METHOD
    {
        VM_ORTHOGONAL = 0,
        VM_PERSPECTIVE
    }; // render's view method...

    class Sprite : public Component
    {
    public:
        Sprite();
        ~Sprite();
        void Init() override;
        void LoadTexture(std::string file);
        void setDeltaTime(float deltaTime_) { m_delta_time = deltaTime_; }
        const glm::vec3& Size() const;
        void Visible_Switch(bool isVisible = true);
        void RGBA_Color(glm::vec4 color);
        void setBlendAlpha(float set_time, bool set_blend_alpha = true)
        {
            blend_alpha_remainded_time = set_time;
            is_blend_alpha = set_blend_alpha;
        }
        void setOrthogonal() { m_isPerspective = false; }
        void setPerspective() { m_isPerspective = true; }
        float getBlendAlphaElapsedTime() { return elapsed_time; }
        const glm::vec4& get_RGBA_Color() const { return m_rgba_color; }

    public:                                  // static
        static const glm::vec2 DEFAULT_SIZE; //set in Sprite.cpp
        static const int DEFAULT_SPRITE_LAYER;

    private:
        friend class Graphics;
        bool m_visible = true;
        bool m_isPerspective;
        glm::vec4 m_rgba_color = glm::vec4(1.f, 1.f, 1.f, 1.f); //Red Green Blue Alpha
        bool is_blend_alpha = false;
        float blend_alpha = 1.0f;
        float blend_alpha_remainded_time;
        Transform* pm_transform = nullptr;
        int m_sprite_layer = DEFAULT_SPRITE_LAYER;
        float elapsed_time;
        bool m_flip_x = false;
        bool m_flip_y = false;
        GLuint pm_textureID;
        float m_delta_time = 1.f / 60.f;
        bool animation_active = true;
        float animation_speed = 1.f;
        GLuint start_frame = 0;
        GLuint current_frame = 0;

        void RotatingMat(glm::mat4& model);
        void render();
    };
}
#endif // !SPRITE_H_
