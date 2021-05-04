/**
\file        Texture.h
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <unordered_map>
#include <vector>

#include <GL/glew.h>
#include <string>

#include "Headers_Textures.h"

namespace FindersEngine
{
    enum Texture_Type
    {
        TT_SQUARE,
        TT_CIRCLE,
        TT_SUQARE_BOARERDED,
        TT_CIRCLE_BOARERDED,
    };

    //NOTICE:
    // It needs a specific file locations
    // Only work loading textures and rendering these!
    // Texture should use
    //Todo: I will make File I/O that manage Loaders, remind the flyweight pattern
    class Texture
    {
    public:
        //NOTIECE: Use only through Texture::GetInstance().~
        static Texture& GetInstance()
        {
            static Texture texture;
            return texture;
        }

        void Load();

        void opengl_init();

        ~Texture();

        TextureID GetTexture(std::string file_path);

        Image_MetaData& GetImage(std::string file_path);

    private:
        Image_MetaData* load_image(const std::string& file_path);

        Texture() {} //cannot create over...


        Texture(const Texture& texture) = delete;            //cannot copy it
        Texture& operator=(const Texture& texture) = delete; //cannot assignment it

        std::unordered_map<std::string, Image_MetaData*> gameImages;

        //using hashcode key-value
        std::unordered_map<std::string, TextureID> gameTextures; //allocated by Graphics
    };
}


#endif // !TEXTURE_H_
