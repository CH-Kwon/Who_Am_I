/**
\file        Hud.h
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once

#ifndef Hud_H_
#define Hud_H_

#include "Component.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>

namespace FindersEngine
{
    enum Layer_Order
    {
        LO_BASE = 0,
        LO_1,
        LO_2
    };


    class Hud : public Component
    {
    public:
        Hud();
        ~Hud();
        void Init() override;

        void setLayerOrder(Layer_Order lo) { layer_order = lo; }


        void LoadTexture(std::string file_path);
        const glm::vec3& Size() const;
        void Visible_Switch(bool isVisible = true) { m_visible = isVisible; }
        void RGBA_Color(glm::vec4 color) { m_rgba_color = color; }
        const glm::vec4& get_RGBA_Color() const { return m_rgba_color; }
        void setBlendAlpha(float set_time, bool set_blend_alpha = true)
        {
            blend_alpha_remainded_time = set_time;
            is_blend_alpha = set_blend_alpha;
        }
        float getBlendAlphaElapsedTime() { return elapsed_time; }
        void setDeltaTime(float deltaTime_) { m_delta_time = deltaTime_; }
        void render();

    public:                                  // static
        static const glm::vec2 DEFAULT_SIZE; //set in Hud.cpp
        static const int DEFAULT_Hud_LAYER;

    private:
        friend class Graphics;
        bool m_visible = true;
        bool isTexture = false; // use it!!
        float m_delta_time = 1.f / 60.f;
        glm::vec4 m_rgba_color = glm::vec4(1.f, 1.f, 1.f, 1.f); //Red Green Blue Alpha
        bool is_blend_alpha = false;
        float blend_alpha = 1.0f;
        float blend_alpha_remainded_time;
        Transform* pm_transform = nullptr;
        int m_Hud_layer = DEFAULT_Hud_LAYER;
        float elapsed_time;
        GLuint pm_textureID;

        Layer_Order layer_order = LO_BASE;

        bool animation_active = true;
        float animation_speed = 1.f;
        GLuint start_frame = 0;
        GLuint current_frame = 0;

        void RotatingMat(glm::mat4& model);

        int getLayerOrder() const { return (int)layer_order; }
    };
}
#endif // !Hud_H_
