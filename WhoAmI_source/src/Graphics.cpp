/**
\file        Graphics.cpp
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

//#pragma warning(disable:4700)

#include "Graphics.h"
#include "Application.h" //SwapWindows
#include "Texture.h"

//Debug Library
#include <GL/glew.h>
#include <cassert>  // assert
#include <iostream> // std::cerr, std::cout, std::clog

#include "Headers_Components.h"

#include "CameraSystem.h"
#include "Input.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include "Engine.h"
#include "DataPipeline.hpp"

//main components: Sprite, Camera
//dependency components: Transform

namespace FindersEngine
{
    namespace
    {
        //Prepared Attributes
        GLfloat buffer_position_data[] =
            {
                0.5f, 0.5f, 0.0f,   // Top Right Vertex
                0.5f, -0.5f, 0.0f,  // Bottom Right Vertex
                -0.5f, -0.5f, 0.0f, // Bottom Left Vertex
                -0.5f, 0.5f, 0.0f,  // Top Left Vertex
        };

        GLfloat buffer_color_data[] =
            {
                1.0f, 0.0f, 0.0f, 1.0f, //Red
                0.0f, 1.0f, 0.0f, 1.0f, //Green
                0.0f, 0.0f, 1.0f, 1.0f, //Blue
                1.0f, 0.0f, 0.0f, 1.0f, //Red
        };

        GLfloat buffer_coordinate_data[] = // texture's coordinate!
            {
                // x  y
                1.0f, 1.0f, // Top Right Texture Coord
                1.0f, 0.0f, // Bottom Right Textur Coord
                0.0f, 0.0f, // Bottom Left Texture Coord
                0.0f, 1.0f  // Top Left Texture Coord

        };

        //ref: buffer_position_data
        GLuint upper_right_triangle_indices[] =
            {
                0,
                1,
                3,
        };

        GLuint lower_right_triangle_indices[] =
            {
                1, 2, 3};

        // Draw using ref: buffer_position_data's indices
        GLuint rectangle_indices[] =
            {
                0, 1, 3,
                1, 2, 3};
        const glm::vec4 WHITE_COLOR(1.0f);
        const glm::vec4 DEFAULT_BACKGROUND_COLOR = glm::vec4(1.f, 1.f, 1.f, 1.f);
    }
    Graphics* GRAPHICS = nullptr;
    const float Graphics::AREA_SIZE_MAX = 800.f; // 800 * 800
    const float Graphics::FAR_Z_AXIS = 3.f;      // (800 * 3) * (800 * 3)

    Object* player_object;
    Graphics::Graphics()
    {
        assert(GRAPHICS == nullptr && "Graphics system is already existing one more!");
        GRAPHICS = this;
        clear_color = glm::vec4(1.0f);
        light_color = glm::vec3(1.0f);
    }

    Graphics::~Graphics()
    {
        ImGui_ImplSdlGL3_Shutdown();
        delete camera_system;
        glDisableVertexAttribArray(BDI_POSITION);
        glDisableVertexAttribArray(BDI_COLOR);
        glDisableVertexAttribArray(BDI_TEXTURE_COORDIATE);
        GLuint* VAOs_pointer = VAOs.data();
        GLuint* VBOs_pointer = VBOs.data();
        GLuint* EBOs_pointer = EBOs.data();
        glDeleteVertexArrays(static_cast<int>(VAOs.size()), VAOs_pointer);
        glDeleteBuffers(static_cast<int>(VBOs.size()), VBOs_pointer);
        glDeleteBuffers(static_cast<int>(EBOs.size()), EBOs_pointer);
    }

    void Graphics::Init()
    {
        GLenum is_glew_init = glewInit();
        if (is_glew_init != GLEW_OK)
        {
            std::cerr << "Initialzing GLEW is failed! " << glewGetErrorString(is_glew_init) << '\n';
            return;
        }



        BackgroundColor(DEFAULT_BACKGROUND_COLOR);
        mainShader.init("Shaders/vertex.glsl", "Shaders/fragment.glsl");

        mainShader.draw_begin();
        Buffer_Allocator();
        mainShader.setInt("outTexture", 0);
        Texture::GetInstance().opengl_init(); // lodepng
        mainShader.draw_end();

        glBindVertexArray(NULL);
        glBindBuffer(GL_ARRAY_BUFFER, NULL);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

        camera_system = new CameraSystem(glm::vec3(0, 0, FAR_Z_AXIS));
        font_system.Init();
        ImGui_ImplSdlGL3_Init(APPLICATION->getWindow());
    }

    void Graphics::ImguiUpdate(float)
    {
        ImGui_ImplSdlGL3_NewFrame(APPLICATION->getWindow());
        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_F10))
        {
            show_imgui_main_window = !show_imgui_main_window;
        }

        if (show_imgui_main_window)
        {
            // 1. Show a simple window
            // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
            ImGui::Text("ImGui Test Helper!");
            ImGui::SliderFloat("float", &(camera_system->m_zoom), 0.01f, 45.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
            if (ImGui::Button("ImGui Guide Window"))
                show_imgui_guide_window ^= 1;
            if (ImGui::Button("Another Window"))
                show_another_window ^= 1;


            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            int mouse_x;
            int mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            ImGui::Text("Mouse Screen Position (%d, %d)", mouse_x, mouse_y);
            glm::vec2 world_mouse(mouse_x, mouse_y);
            world_mouse = APPLICATION->screen_to_world(world_mouse);
            ImGui::Text("Mouse World Position (%2.2f, %2.2f)", world_mouse.x, world_mouse.y);
        }

        // 2. Show another simple window, this time using an explicit Begin/End pair
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello from another window!");

            ImGui::End();
        }

        // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
        if (show_imgui_guide_window)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
            ImGui::ShowTestWindow(&show_imgui_guide_window);
        }
    }

    void Graphics::CameraUpdate(float)
    {
        mainShader.draw_begin();

        for (auto iter : gameCameras)
        {
            iter->sync();
        }

        light_pos = camera_system->m_position;
        light_pos.z = 10.0f;
        mainShader.setVec3f("lightPos", light_pos);
    }

    void Graphics::SpritesUpdate(float deltaTime)
    {
        mainShader.draw_begin();

        for (std::vector<Sprite*>::iterator iter = gameSprites.begin();
             iter != gameSprites.end(); ++iter)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[BSI_RECTANGLE]);
            mainShader.setFloat("blendAlpha", (*iter)->blend_alpha);

            (*iter)->setDeltaTime(deltaTime);
            glm::vec3 size = (*iter)->Size();

            camera_system->update(deltaTime);

            // Todo : perspiective is default, but I should add orthogonal and all of two become abstract form;
            glm::mat4 projection(1.0f);
            glm::mat4 view(1.0f);
            glm::mat4 model(1.0f);
            glm::vec2 texOffset(0.f);
            glm::vec2 texRatio(1.f);

            int v_screen_width;
            int v_screen_height;
            APPLICATION->get_virtual_screen_size(&v_screen_width, &v_screen_height);


            glm::vec3 transform = (*iter)->pm_transform->getPosition();

            mainShader.setVec2f("texOffset", texOffset);
            mainShader.setVec2f("texRatio", texRatio);
            mainShader.setBool("isPerspective", (*iter)->m_isPerspective);

            view = camera_system->GetLookAtMatrix();

            if ((*iter)->m_isPerspective)
            {
                projection = camera_system->GetProjectionPerspective();

                mainShader.setVec3f("aSize", size / AREA_SIZE_MAX);
            }
            else // orthogonal
            {
                projection = camera_system->GetProjectionOrthogonal();

                mainShader.setVec3f("aSize", size);
            }

            model = glm::translate(model, transform);
            (*iter)->RotatingMat(model);


            mainShader.setMat4f("projection", projection);
            mainShader.setMat4f("view", view);
            mainShader.setMat4f("model", model);
            mainShader.setVec4f("objectColor", (*iter)->get_RGBA_Color());

            (*iter)->render();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //drawing...

            //Todo: glViewport to set in APPLICATION(width, height)
        }
        mainShader.draw_end();
    }

    void Graphics::HudsUpdate(float deltaTime)
    {
        mainShader.draw_begin();

        std::sort(std::begin(gameHuds), std::end(gameHuds), [](const auto& hud1, const auto& hud2) { return hud1->getLayerOrder() < hud2->getLayerOrder(); });

        for (std::vector<Hud*>::iterator iter = gameHuds.begin();
             iter != gameHuds.end(); ++iter)
        {

            glm::vec2 texOffset(0.0f);
            glm::vec2 texRatio(1.0f);
            mainShader.setVec2f("texOffset", texOffset);
            mainShader.setVec2f("texRatio", texRatio);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[BSI_RECTANGLE]);
            mainShader.setFloat("blendAlpha", (*iter)->blend_alpha);

            (*iter)->setDeltaTime(deltaTime);
            glm::vec3 size = (*iter)->Size();

            camera_system->update(deltaTime);

            // Todo : perspiective is default, but I should add orthogonal and all of two become abstract form;
            glm::mat4 projection(1.0f);
            glm::mat4 view(1.0f);
            glm::mat4 model(1.0f);

            glm::vec3 transform = (*iter)->pm_transform->getPosition();
            view = camera_system->GetLookAtMatrix();


            mainShader.setBool("isPerspective", false);

            projection = camera_system->GetProjectionOrthogonal();

            mainShader.setVec3f("aSize", size);


            model = glm::translate(model, transform);
            (*iter)->RotatingMat(model);


            mainShader.setMat4f("projection", projection);
            mainShader.setMat4f("view", view);
            mainShader.setMat4f("model", model);
            mainShader.setVec4f("objectColor", (*iter)->get_RGBA_Color());

            (*iter)->render();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //drawing...
        }
        mainShader.draw_end();
    }

    void Graphics::ShootLight(float)
    {
        mainShader.draw_begin();
        {
            mainShader.setBool("isFlashLight", true);
            vp = camera_system->m_position;
            vp.z = 0.f;
            glm::vec3 vLight_angle(glm::cos(light_angle), glm::sin(light_angle), 0.0f);
            vp += vLight_angle * glm::vec3(2.0f);
            mainShader.setVec3f("flashLight.normal", vLight_angle);
            mainShader.setVec3f("flashLight.position", vp);
            mainShader.setVec3f("flashLight.direction", -vLight_angle);

            mainShader.setFloat("flashLight.innerCutOff", glm::cos(glm::radians(flashLight_innerCutOff * 1.5f)));
            mainShader.setFloat("flashLight.outerCutOff", glm::cos(glm::radians(flashLight_outerCutOff * 1.5f)));

            // light properties
            glm::vec3 lightAmbient(ambient_value); // ambient_value;
            glm::vec3 lightDiffuse(0.8f);
            glm::vec3 lightSpecular(0.9f);

            mainShader.setVec3f("flashLight.ambient", lightAmbient);
            mainShader.setVec3f("flashLight.diffuse", lightDiffuse);
            mainShader.setVec3f("flashLight.specular", lightSpecular);
            mainShader.setFloat("flashLight.constant", 1.0f);
            mainShader.setFloat("flashLight.linear", 0.0009f);
            mainShader.setFloat("flashLight.quadratic", 0.0000032f);

            mainShader.setFloat("shininess", 32.0f);
        }
        mainShader.draw_end();
    }
    void Graphics::HandLight(float)
    {

        mainShader.draw_begin();
        {
            float flashLight_innerCutOff = 15.0f;
            float flashLight_outerCutOff = 30.0f;

            mainShader.setBool("isFlashLight", true);
            vp = camera_system->m_position;

            vp.z = 0.f;
            glm::vec3 vLight_angle(glm::cos(light_angle), glm::sin(light_angle), 0.0f);

            mainShader.setVec3f("flashLight.normal", -vLight_angle);
            mainShader.setVec3f("flashLight.position", vp);
            mainShader.setVec3f("flashLight.direction", vLight_angle);

            mainShader.setFloat("flashLight.innerCutOff", glm::cos(glm::radians(flashLight_innerCutOff)));
            mainShader.setFloat("flashLight.outerCutOff", glm::cos(glm::radians(flashLight_outerCutOff)));

            // light properties
            glm::vec3 lightAmbient(ambient_value); // ambient_value;
            glm::vec3 lightDiffuse(0.7f);
            glm::vec3 lightSpecular(0.8f);

            mainShader.setVec3f("flashLight.ambient", lightAmbient);
            mainShader.setVec3f("flashLight.diffuse", lightDiffuse);
            mainShader.setVec3f("flashLight.specular", lightSpecular);
            mainShader.setFloat("flashLight.constant", 1.0f);
            mainShader.setFloat("flashLight.linear", 0.0009f);
            mainShader.setFloat("flashLight.quadratic", 0.00032f);

            mainShader.setFloat("shininess", 32.0f);
        }
        mainShader.draw_end();
    }

    void Graphics::SpotLight(float)
    {
        mainShader.draw_begin();
        {
            glm::vec3 normal(0.0f, 0.0f, 1.0f);
            mainShader.setVec3f("light.normal", normal);
            mainShader.setVec3f("light.position", camera_system->m_position);
            mainShader.setVec3f("light.direction", camera_system->m_front);


            mainShader.setFloat("light.innerCutOff", glm::cos(glm::radians(shotLight_innerCutOff)));
            mainShader.setFloat("light.outerCutOff", glm::cos(glm::radians(shotLight_outerCutOff)));


            // light properties
            glm::vec3 lightAmbient(ambient_value); // ambient_value;
            glm::vec3 lightDiffuse(0.8f);
            glm::vec3 lightSpecular(0.8f);

            mainShader.setVec3f("light.ambient", lightAmbient);
            mainShader.setVec3f("light.diffuse", lightDiffuse);
            mainShader.setVec3f("light.specular", lightSpecular);
            mainShader.setFloat("light.constant", 1.0f);
            mainShader.setFloat("light.linear", 0.1f);
            mainShader.setFloat("light.quadratic", 0.128f);

            mainShader.setFloat("shininess", 32.0f);
        }
        mainShader.draw_end();
    }


    void Graphics::Update(float deltaTime)
    {
        player_object = OBJECT_FACTORY->GetObjectID(100);
        // configuration
        glEnable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // clear and update
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);


        // Start::
        {
            int screen_width;
            int screen_height;
            APPLICATION->get_real_screen_size(&screen_width, &screen_height);
        }

        ImguiUpdate(deltaTime);
        CameraUpdate(deltaTime);
        vp = camera_system->m_position;

        glBindVertexArray(VAOs[BASI_ONE]);

        mainShader.draw_begin();
        {
            mainShader.setFloat("flashLightDistance", flashlight_distance);
            mainShader.setBool("isFlashLight", false);
            mainShader.setBool("isSpotlight", isSpotlight);
            mainShader.setFloat("walldistance", walldistance);
        }
        mainShader.draw_end();

        if (isSpotlight)
        {
            SpotLight(deltaTime);
        }

        if (isHandLight)
        {
            HandLight(deltaTime);
        }


        if (isShootLight)
        {
            ShootLight(deltaTime);
        }


        SpritesUpdate(deltaTime);
        HudsUpdate(deltaTime);
        std::for_each(gameSpriteTexts.begin(), gameSpriteTexts.end(), [deltaTime](const auto& elem) { elem->Draw(deltaTime); });

        glBindVertexArray(NULL);

        // Font staffs...

        ImGui::Render();

        APPLICATION->SwapWindow(); //double buffer..
    }

    void Graphics::Buffer_Allocator()
    {
        GLuint* VAOs_pointer = VAOs.data();
        GLuint* VBOs_pointer = VBOs.data();
        GLuint* EBOs_pointer = EBOs.data();

        glGenVertexArrays(static_cast<int>(VAOs.size()), VAOs_pointer);
        glBindVertexArray(VAOs[BASI_ONE]);

        // using VAOs[BASIC_ONE]
        {
            //VBOs jobs...
            glGenBuffers(static_cast<int>(VBOs.size()), VBOs_pointer);

            glBindBuffer(GL_ARRAY_BUFFER, VBOs[BDI_POSITION]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_position_data), buffer_position_data, GL_STATIC_DRAW);
            glEnableVertexAttribArray(AAI_VERTEX);
            glVertexAttribPointer(AAI_VERTEX, 3 /*x, y, z*/, GL_FLOAT, GL_FALSE, sizeof(GLfloat[3]), (void*)0);

            glBindBuffer(GL_ARRAY_BUFFER, VBOs[BDI_COLOR]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_color_data), buffer_color_data, GL_STATIC_DRAW);
            glEnableVertexAttribArray(AAI_COLOR);
            glVertexAttribPointer(AAI_COLOR, 4 /*r, g, b, a*/, GL_FLOAT, GL_FALSE, sizeof(GLfloat[4]), (void*)0);

            glBindBuffer(GL_ARRAY_BUFFER, VBOs[BDI_TEXTURE_COORDIATE]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_coordinate_data), buffer_coordinate_data, GL_STATIC_DRAW);
            glEnableVertexAttribArray(AAI_TEXTURE_COORDINATE);
            glVertexAttribPointer(AAI_TEXTURE_COORDINATE, 2 /*s, t*/, GL_FLOAT, GL_FALSE, sizeof(GLfloat[2]), (void*)0);
        }

        //EBOs jobs...
        {
            glGenBuffers(static_cast<int>(EBOs.size()), EBOs_pointer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[BSI_RECTANGLE]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangle_indices), rectangle_indices, GL_STATIC_DRAW);


            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[BSI_LOWER_TRIANGLE]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lower_right_triangle_indices), lower_right_triangle_indices, GL_STATIC_DRAW);


            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[BSI_UPPER_TRIANGLE]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(upper_right_triangle_indices), upper_right_triangle_indices, GL_STATIC_DRAW);
        }
    }

    // Reporting over index/argument's bound...
    bool Bounding_Error_Report(const std::string& function_name, float value, float start, float end, const std::string& type_name, const std::string& argument_name)
    {
        bool fail = false;

        if (value < start || value > end) // over bounding!
        {
            std::cerr << function_name << " ERROR: "
                      << "Set between " << start << " to " << end << " in " << type_name
                      << " in a " << argument_name << " argument." << std::endl;
            fail = true;
        }

        return fail;
    }

    bool Graphics::BackgroundColor(float red, float blue, float green, float alpha, bool is256Bits)
    {
        bool success = true;

        if (!is256Bits)
        {
            success = !Bounding_Error_Report("BackgroundColor", red, 0.f, 1.f, "float", "red");
            success = !Bounding_Error_Report("BackgroundColor", blue, 0.f, 1.f, "float", "blue");
            success = !Bounding_Error_Report("BackgroundColor", green, 0.f, 1.f, "float", "green");
            success = !Bounding_Error_Report("BackgroundColor", alpha, 0.f, 1.f, "float", "alpha");
        }
        else
        {
            success = !Bounding_Error_Report("BackgroundColor", red, 0.f, 255.f, "int", "red");
            success = !Bounding_Error_Report("BackgroundColor", blue, 0.f, 255.f, "int", "blue");
            success = !Bounding_Error_Report("BackgroundColor", green, 0.f, 255.f, "int", "green");
            success = !Bounding_Error_Report("BackgroundColor", alpha, 0.f, 255.f, "int", "alpha");

            red /= 255.f;
            blue /= 255.f;
            green /= 255.f;
            alpha /= 255.f; //converting to 256bits to float[0.f,1.f]
        }

        clear_color = glm::vec4(red, blue, green, alpha);

        return success;
    }
    bool Graphics::BackgroundColor(const glm::vec4& color, bool is256Bits)
    {
        float red = color.x;
        float blue = color.y;
        float green = color.z;
        float alpha = color.w;

        return BackgroundColor(red, blue, green, alpha, is256Bits);
    }
};
