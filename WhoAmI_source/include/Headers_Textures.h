/**
 \file
 \author
 \par         email:
 \par         course: GAM200
 \date        ?/?/2017
 \brief
 
 */

#ifndef HEADERS_TEXTURES_H_
#define HEADERS_TEXTURES_H_

namespace FindersEngine
{
    struct Image_MetaData
    {
        std::vector<unsigned char> image;
        unsigned width, height;
    };

    using TextureID = unsigned int;
};

#endif // !HEADERS_TEXTURES_H_
