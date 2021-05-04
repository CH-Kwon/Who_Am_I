/**
\file        Transform.hpp
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once
#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Component.hpp"
#include "ComponentType.h"

#include <glm/glm.hpp>

namespace FindersEngine
{
	class Transform : public Component
	{
	public:
		Transform() : Component(CT_TRANSFORM)
		{
			position = glm::vec3(0.f); // origin
			rotation = glm::vec3(0.f); // no rotation
			scale = glm::vec3(100.f, 100.f, 1.f); // 100*100*1 = 10000(mass)
		}

		const glm::vec3& getPosition() const { return position; }
		const glm::vec3& getRotation() const { return rotation; }
		const glm::vec3& getScale() const { return scale; }
		void setPosition(const glm::vec3 & pos) { position = pos; }
		void setRotation(const glm::vec3& rot) { rotation = rot; }
		void setScale(const glm::vec3& s) { scale = s; }
	private:
            friend class RigidBody;
        glm::vec3 position; // if use public, just declare "friend class YourClass;" in here
		glm::vec3 rotation;
		glm::vec3 scale;

	};
}


#endif // !TRANSFORM_H_
