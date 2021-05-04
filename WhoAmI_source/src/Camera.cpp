/**
 \file        Camera.cpp
 \author      Sehyun Kim
 \par         email: kim4969\@gmail.com
 \par         course: GAM200
 \date        10/15/2017.
 \brief
 All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
 */
#include "Camera.h"
#include "CameraSystem.h"
#include "Graphics.h"
#include "Object.h"
#include "Transform.hpp"
#include <algorithm>
#include <iostream> // debugging

namespace FindersEngine
{
    Camera::Camera() : Component(CT_CAMERA) { GRAPHICS->gameCameras.push_back(this); }

    Camera::~Camera() { GRAPHICS->gameCameras.erase(std::find(GRAPHICS->gameCameras.begin(), GRAPHICS->gameCameras.end(), this)); }

    void Camera::Init()
    {
        pm_transform = (Transform*)GetOwner()->GetComponent(CT_TRANSFORM);
        if (!pm_transform)
            std::cerr << "Camera need transform component in object!" << std::endl;
        pm_camera_system = GRAPHICS->camera_system;
        if (!pm_camera_system)
            std::cerr << "There is no camera system!" << std::endl;
    }
    void Camera::sync()
    {
        glm::vec3 cameraPosition = pm_transform->getPosition();
        pm_camera_system->m_position.x = cameraPosition.x;
        pm_camera_system->m_position.y = cameraPosition.y;
    }

    const CameraSystem& Camera::GetCameraSystem() const { return *pm_camera_system; }
};
