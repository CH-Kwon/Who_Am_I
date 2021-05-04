/**
 \file
 \author
 \par         email:
 \par         course: GAM200
 \date        ?/?/2017
 \brief
 
 */

#include "Texture.h"

#include <unordered_map>
#include <vector>
//#include <array>

#include "lodepng.h"
#include <GL/glew.h>

#include <iostream>
#include <string>

#include "Engine.h"
#include "DataPipeline.hpp"

#include "Headers_Textures.h"

namespace FindersEngine
{

    
    void Texture::Load()
    {
        //loading all image files
        
        const std::vector<std::string>& loading_image_file_path = ENGINE->IMAGES;
        
        for (const std::string& file_path : loading_image_file_path)
        {
            std::string&& path = IMAGE_DIR + file_path;
            Image_MetaData* image = load_image(path);
            gameImages.insert({path, image});
        }
        
//        for (const auto file_path : loading_images_file_path)
//        {
//            Image_MetaData* image = load_image(file_path);
//            gameImages.insert({file_path, image});
//            //std::cout << "Load image file: " << file_path << std::endl;
//        }
        //std::cout << loading_images_file_path_size << std::endl;
    }
    
    void Texture::opengl_init()
    {
        const std::vector<std::string>& loading_image_file = ENGINE->getImages();
        
        for (const std::string& file : loading_image_file)
        {
            gameTextures.insert({file, NULL});
        }
        
        
        std::vector<GLuint> texture_indices(gameTextures.size());
        
        // This is the Graphic staff
        glActiveTexture(GL_TEXTURE0); //Default Setting..(one)
        glEnable(GL_TEXTURE_2D);
        
        glGenTextures((int)texture_indices.size(), &texture_indices[0]);
        
        //for loop allocating...images! start 0
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        //glGenerateMipmap(GL_TEXTURE_2D);
        //Todo: I will use mipmap later!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        // after allocating GLuint(s)
        int i = 0;
        
        for (const std::string& file : loading_image_file)
        {
            std::string&& file_path = IMAGE_DIR + file;
            
            glBindTexture(GL_TEXTURE_2D, texture_indices[i]);
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (gameImages[file_path])->width, (gameImages[file_path])->height,
                         0, GL_RGBA, GL_UNSIGNED_BYTE, gameImages[file_path]->image.data());
            glBindTexture(GL_TEXTURE_2D, NULL); // safe binding
            gameTextures[file_path] = texture_indices[i];
            i++;
        }
        
        
//        for (auto file_path : loading_images_file_path)
//        {
//            glBindTexture(GL_TEXTURE_2D, texture_indices[i]);
//
//            //Todo : Double Check: GL_RGB, GL_RGBA
//            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (gameImages[file_path])->width, (gameImages[file_path])->height,
//                         0, GL_RGBA, GL_UNSIGNED_BYTE, gameImages[file_path]->image.data());
//
//            glBindTexture(GL_TEXTURE_2D, NULL);
//
//            gameTextures[file_path] = texture_indices[i];
//            i++;
//        }
        
        std::cout << "Done" << std::endl;
    }
    
    Texture::~Texture()
    {
        const auto & loading_image_file = ENGINE->getImages();
        
        //Todo: Clear GLTexture2D...
        for (const std::string& file : loading_image_file)
        {
            std::string&& file_path = IMAGE_DIR + file;
            delete gameImages[file_path];
        
        }
        
        gameImages.clear();
        gameTextures.clear();
    }
    
    TextureID Texture::GetTexture(std::string file)
    {
        std::string&& file_path = IMAGE_DIR + file;
        return gameTextures[file_path];
    }
    
    Image_MetaData& Texture::GetImage(std::string file_path)
    {
        return *gameImages[file_path];
    }
    
    
    Image_MetaData* Texture::load_image(const std::string& file_path)
    {
        Image_MetaData* saving_image = new Image_MetaData();
        //Load PNG from specified file_location
        unsigned is_error = lodepng::decode(saving_image->image,
                                            saving_image->width, saving_image->height,
                                            file_path);
        
        if (is_error != 0)
        {
            std::cerr << "ERROR: " << is_error << ": "
            << lodepng_error_text(is_error) << std::endl;
            return nullptr;
        }
        
        return saving_image;
    }
}

