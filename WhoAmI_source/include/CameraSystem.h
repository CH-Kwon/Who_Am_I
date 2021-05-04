/**
\file        CameraSystem.h
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#ifndef CAMERA_SYSTEM_H_
#define CAMERA_SYSTEM_H_

#include <glm/glm.hpp>

namespace FindersEngine
{
    const float YAW = -90.f;  // x-axis rotation
    const float PITCH = 0.0f; // y-axis rotation
    const float ROLL = 0.0f;  // z-axis rotation
    const float SPEED = 2.5f;
    const float SENSITIVITY = 0.1f;
    const float ZOOM = 45.0f;

    const float NEAR_PLANE = 0.1f;
    const float FAR_PLANE = 100.f;

    enum Camera_Movement
    {
        CM_FORWARD, // z-axis
        CM_BACKWARD,
        CM_RIGHT, // x-axis
        CM_LEFT,
        CM_UP, // y-axis
        CM_DOWN
    };

    class CameraSystem
    {
    public:
        // Camera Attributes
        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;
        glm::vec3 m_scale;

        glm::mat4 m_perspective;
        glm::mat4 m_ortho;
        glm::mat4 m_view;

        float m_near_plane;
        float m_far_plane;

        // Euler Angles
        float m_yaw;
        float m_pitch;
        float m_roll;

        // Camera option
        float m_movementSpeed;
        float m_mouseSensitivity;
        float m_zoom;

        CameraSystem(glm::vec3 position = glm::vec3(0), glm::vec3 up = glm::vec3(0, 1, 0),
                     float yaw = YAW, float pitch = PITCH, float roll = ROLL,
                     float near_pane = NEAR_PLANE, float far_plane = FAR_PLANE);

        glm::mat4 GetLookAtMatrix();
        glm::mat4 GetProjectionOrthogonal();
        glm::mat4 GetProjectionPerspective();

        void update(float deltaTime);


        void process_keyboard(Camera_Movement direction, float deltaTime);
        void process_move_movement(float xoffset, float yoffset, bool constrainPitch = true);
        void process_mouse_Scroll(float yoffset);

    private:
        void update_camera_system();

        float m_ortho_left;
        float m_ortho_right;
        float m_ortho_top;
        float m_ortho_bottom;
    };
};

#endif // !CAMERA_SYSTEM_H_
