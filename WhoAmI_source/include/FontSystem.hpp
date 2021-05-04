/**
\file        FontSystem.hpp
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

// helped by LearnOpenGL

#ifndef FontSystem_hpp
#define FontSystem_hpp

#include "Shader.h"
#include <glm/glm.hpp>
#include <map>

namespace FindersEngine
{

    struct Charcter
    {
        unsigned int TextureID; // ID handle of the glyph texture
        glm::ivec2 Size;        // Size of glyph
        glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
        long Advance;           // Offset to advance to next glyph
    };

    class FontSystem
    {
    public:
        void RenderText(std::string text, float x, float y, float scale, const glm::vec3& color, float rotation);
        void Init();


    private:
        std::map<char, Charcter> pm_charcters;
        unsigned int VAO;
        unsigned int VBO;
        Shader fontShader;
    };
}

#endif /* FontSystem_hpp */
