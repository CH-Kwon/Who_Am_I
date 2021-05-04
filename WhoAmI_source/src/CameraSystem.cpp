/**
\file        CameraSystem.cpp
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/


#include "CameraSystem.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Input.h"
#include <GL/glew.h>
#include <cassert>

#include "Application.h"

namespace FindersEngine
{
    CameraSystem::CameraSystem(glm::vec3 position, glm::vec3 up,
                               float yaw, float pitch, float roll,
                               float near_plane, float far_plane)
        : m_front(glm::vec3(0, 0, -1)),
          m_movementSpeed(SPEED),
          m_mouseSensitivity(SENSITIVITY),
          m_zoom(ZOOM)
    {
        m_position = position;
        m_worldUp = up;
        m_yaw = yaw;
        m_pitch = pitch;
        m_roll = roll;

        m_near_plane = near_plane;
        m_far_plane = far_plane;

        //Todo

        update_camera_system();
    }

    glm::mat4 CameraSystem::GetLookAtMatrix()
    {
        return m_view;
    }

    glm::mat4 CameraSystem::GetProjectionOrthogonal()
    {
        return m_ortho;
    }

    glm::mat4 CameraSystem::GetProjectionPerspective()
    {

        return m_perspective;
    }

    void CameraSystem::update(float deltaTime)
    {
        int screen_width;
        int screen_height;

        APPLICATION->get_real_screen_size(&screen_width, &screen_height);

        m_scale.x = (float)screen_width;
        m_scale.y = (float)screen_height;

        m_ortho_left = 0.0f;
        m_ortho_right = m_scale.x;
        m_ortho_bottom = m_scale.y;
        m_ortho_top = 0.0f;

        m_perspective = glm::perspective(glm::radians(m_zoom), (GLfloat)screen_width / (GLfloat)screen_height, m_near_plane, m_far_plane);

        m_ortho = glm::ortho(m_ortho_left, m_ortho_right, m_ortho_bottom, m_ortho_top, m_near_plane, m_far_plane); // m_near_plane, m_far_plane);
        m_view = glm::lookAt(m_position, m_position + m_front, m_up);
    }


    void CameraSystem::process_keyboard(Camera_Movement direction, float deltaTime)
    {
        float movement_velocity = m_movementSpeed * deltaTime;
        switch (direction)
        {
            case CM_FORWARD:
                m_position += m_front * movement_velocity;
                break;
            case CM_BACKWARD:
                m_position -= m_front * movement_velocity;
                break;
            case CM_RIGHT:
                m_position += m_right * movement_velocity;
                break;
            case CM_LEFT:
                m_position -= m_right * movement_velocity;
                break;
            case CM_UP:
                m_position += m_up * movement_velocity;
                break;
            case CM_DOWN:
                m_position -= m_up * movement_velocity;
                break;
            default:
                assert(!"Unknown test_process_keyboard, value");
                break;
        }
    }

    void CameraSystem::process_move_movement(float xoffset, float yoffset, bool constrainPitch)
    {
        xoffset *= m_mouseSensitivity;
        yoffset *= m_mouseSensitivity;

        m_yaw += xoffset;
        m_pitch += yoffset;

        if (constrainPitch)
        {
            if (m_pitch > 89.0f)
                m_pitch = 89.0f;
            if (m_pitch < -89.0f)
                m_pitch = -89.0f;
        }

        update_camera_system();
    }

    void CameraSystem::process_mouse_Scroll(float yoffset)
    {
        if (m_zoom >= 1.0f && m_zoom <= 45.0f)
            m_zoom -= yoffset;
        if (m_zoom <= 1.0f)
            m_zoom = 1.0f;
        if (m_zoom >= 45.0f)
            m_zoom = 45.0f;
    }


    void CameraSystem::update_camera_system()
    {
        glm::vec3 front;
        front.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch)) * glm::cos(glm::radians(m_roll));
        front.y = glm::sin(glm::radians(m_pitch)) * glm::cos(glm::radians(m_roll));
        front.z = glm::sin(glm::radians(m_yaw));
        m_front = glm::normalize(front);

        m_right = glm::normalize(glm::cross(m_front, m_worldUp));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }
};
