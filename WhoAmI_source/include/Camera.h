/**
 \file        Camera.h
 \author      Sehyun Kim
 \par         email: kim4969\@gmail.com
 \par         course: GAM200
 \date        10/15/2017.
 \brief
 All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Component.hpp"
#include <glm/glm.hpp>

namespace FindersEngine
{
    class CameraSystem;
    class Camera : public Component
    {
    public:
        Camera();
        ~Camera();
        void Init() override;
        const CameraSystem& GetCameraSystem() const;
        void sync();

    private:
        friend class Graphics;
        friend class CameraSystem;
        Transform* pm_transform = nullptr; // dependency
        CameraSystem* pm_camera_system = nullptr;
    };
};

#endif // !CAMERA_H_
