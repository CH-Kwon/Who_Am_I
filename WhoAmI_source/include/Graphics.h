/**
\file        Graphics.h
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#include "System.h"

#include <array>
#include <glm/glm.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

#include "FontSystem.hpp"
#include <map>

#include "Shader.h"


namespace FindersEngine
{
    //Components
    class Sprite;
    class SpriteText;
    class Camera;
    class Hud;

    class CameraSystem;


    class Graphics : public System
    {
    public: //Interface
        bool BackgroundColor(float red, float blue, float green, float alpha, bool is256Bits = false);
        bool BackgroundColor(const glm::vec4& color, bool is256Bits = false);

    public:
        Graphics();
        ~Graphics();


        void Init() override;
        void Update(float deltaTime) override;


    public: //to_components
        void TurnOnSpotLight()
        {
            isSpotlight = true;
        }
        void TurnOffSpotLight()
        {
            isSpotlight = false;
        }


        enum BUFFER_ARRAY_SAVED_INFO // For VAOs
        {
            //added whole drawing info
            BASI_ONE,
            BASI_TWO, //Todo..

            BASI_COUNT
        };

        enum BUFFUR_DATA_INFO // For VBOs
        {
            BDI_POSITION = 0, // based offset index is zero
            BDI_COLOR,
            BDI_TEXTURE_COORDIATE,

            BDI_COUNT
        };

        enum BUFFER_SHAPE_INFO // For EBOs
        {
            BSI_UPPER_TRIANGLE = 0,
            BSI_LOWER_TRIANGLE,
            BSI_RECTANGLE,
            BSI_CIRCLE, //Todo

            BSI_COUNT
        };

        enum ATTRIB_ARRAY_INDEX
        {
            AAI_VERTEX = 0,
            AAI_COLOR,
            AAI_TEXTURE_COORDINATE,

            AAI_COUNT
        };

        //Imgui_Mode imgui_mode;
        static const float AREA_SIZE_MAX;
        static const float FAR_Z_AXIS;
        CameraSystem* camera_system;

        bool show_player_property_window = false;

    private:
        friend class Sprite;
        friend class SpriteText;
        friend class Camera;
        friend class Hud;


        // containers
        std::vector<Sprite*> gameSprites;
        std::vector<Camera*> gameCameras;
        std::vector<Hud*> gameHuds;
        std::vector<SpriteText*> gameSpriteTexts;

        Shader mainShader;

        // ImGui
        bool show_imgui_main_window = false;
        bool show_imgui_guide_window = false;
        bool show_another_window = false;

        glm::vec4 clear_color;
        glm::vec3 light_color;
        glm::vec3 light_pos;

        std::array<unsigned int, BASI_COUNT> VAOs = {
            0,
        };
        std::array<unsigned int, BDI_COUNT> VBOs = {
            0,
        };
        std::array<unsigned int, BSI_COUNT> EBOs = {
            0,
        };
        std::unordered_map<std::string /*variable_name*/, unsigned int /*ID*/> UniformIDs; //positionOffset, sizeOffset(priority: Area's size > Transform's scale)

        void ImguiUpdate(float);
        void CameraUpdate(float);
        void SpritesUpdate(float);
        void HudsUpdate(float);

        // isFlashlight need to be true.
        void ShootLight(float);
        void HandLight(float);

        // isSpotlight need to be true.
        void SpotLight(float);

    public:
        float max_ambient_value() const { return 1.0f; }
        float min_ambient_value() const { return 0.0f; }
        float get_ambient_value() const { return ambient_value; }
        void set_ambient_value(float value)
        {
            if (value > max_ambient_value())
                return;
            else if (value < min_ambient_value())
                return;
            ambient_value = value;
        }
        void set_light_angle(float radian) { light_angle = radian; }
        float get_light_angle() const { return light_angle; }
        void ShootLightOn() { isShootLight = true; }
        void ShootLightOff() { isShootLight = false; }
        void ShootLightSwitch() { isShootLight = !isShootLight; }
        bool IsShotLight() const { return isShootLight; }
        void HandLightOn() { isHandLight = true; }
        void HandLightOff() { isHandLight = false; }
        void HandLightSwitch() { isHandLight = !isHandLight; }
        bool IsHandLight() const { return isHandLight; }
        void set_wall_distance(float distance) { walldistance = distance; }
        float get_wall_distance() const { return walldistance; }

    private:
        FontSystem font_system;
        void Buffer_Allocator();
        bool isSpotlight = false;  // DO NOT TOUCH IT!
        bool isFlashlight = false; // DO NOT USE IT, BECAUSE IT IS SENSETIVE!!!
        bool isHandLight = false;
        bool isShootLight = false;
        float light_angle = 0.0f;
        float ambient_value = 0.1f;
        float flashLight_innerCutOff = 17.5f;
        float flashLight_outerCutOff = 35.0f;
        float shotLight_innerCutOff = 10.0f;
        float shotLight_outerCutOff = 20.0f;
        float effect_elapsedTime = 0.0f;
        float flashlight_distance = 2.125f;
        float walldistance = 2.125;
        glm::vec3 vp; // for flashlight applied normal vector on xy-plane
    };
    extern Graphics* GRAPHICS;
};


#endif // !GRAPHICS_H_
