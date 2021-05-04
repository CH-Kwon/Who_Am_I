/**
 \file        SpriteText.hpp
 \author      Sehyun Kim
 \par         email: kim4969\@gmail.com
 \par         course: GAM200
 \date        11/22/2017.
 \brief
 Copyright © 2017 DigiPen All rights reserved.
 */
#ifndef SpriteText_hpp
#define SpriteText_hpp
#include "Component.hpp"
#include <string>
#include <glm/glm.hpp>

namespace FindersEngine {
    class Transform;
    
    class SpriteText : public Component
    {
    public:
        SpriteText();
        ~SpriteText();
        void Init() override; 
        void setText(const std::string& rhs) { text = rhs; }
        void setScale(float rhs) { scale = rhs; }
        void setColor(const glm::vec3& rhs) { color = rhs; }
        const std::string& getText() const { return text; }
        float getScale() { return scale; }
        const glm::vec3& getColor() const { return color; }
    private:
        friend class Graphics;
        std::string text = "";
        glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f); //BLACK
        Transform* pm_transform; // need transform(dependency)
        float scale = 1.0f;
        void Draw(float deltaTime);
    };
}

#endif /* SpriteText_hpp */
