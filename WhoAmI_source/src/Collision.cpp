/**
\file        Collision.cpp
\author      jungdae.chur
\par         email: wmdhwmdh@gmail.com
\par         course: GAM200
\date        12/13/2017
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "Collision.h"
#include "Application.h"
#include "Engine.h"
#include "Object.h"
#include "Physics.h"
#include "RigidBody.h"
#include "Sprite.h"
#include "Transform.hpp"
#include <glm/glm.hpp>

#include "CameraSystem.h"
#include "Graphics.h"

#include "jsonReader.h" // getWallPos();
#define PI 3.14159

using namespace FindersEngine;

namespace FindersEngine
{
    const float width = 800.f;
    const float height = 800.f;
    glm::vec2 padtarget_direction = glm::vec2(0, 0);
    glm::vec2 pad = glm::vec2(0, 0);

    Collision::Collision()
        : Component(CT_COLLISION)
    {
    }
    Collision::~Collision()
    {
    }

    void Collision::Init()
    {
        pm_transform = (Transform*)GetOwner()->GetComponent(CT_TRANSFORM);
        if (pm_transform == nullptr)
        {
            std::cerr << "Collision Component need Transform Component!" << std::endl;
            std::cerr << "Collision cannot initialize." << std::endl;
        }
    }

    //Chekc two AABB objects' collision
    //return true if collided, and false otherwise
    bool Collision::AABBAABBCollisionCheck(Object* pA, Object* pB)
    {
        Transform* a_pTransform = static_cast<Transform*>(pA->GetComponent(CT_TRANSFORM));
        Transform* b_pTransform = static_cast<Transform*>(pB->GetComponent(CT_TRANSFORM));

        if (a_pTransform == nullptr || b_pTransform == nullptr)
            return false;

        glm::vec2 asize = a_pTransform->getScale();
        glm::vec2 bsize = b_pTransform->getScale();

        glm::vec3 apos = glm::vec3(a_pTransform->getPosition().x * width / 2.f, a_pTransform->getPosition().y * height / 2.f, 0.f);
        glm::vec3 bpos = glm::vec3(b_pTransform->getPosition().x * width / 2.f, b_pTransform->getPosition().y * height / 2.f, 0.f);

        glm::vec3 atl, abr, btl, bbr;
        atl = glm::vec3(apos.x - asize.x / 2.f, apos.y + asize.y / 2.f, 0.f);
        abr = glm::vec3(apos.x + asize.x / 2.f, apos.y - asize.y / 2.f, 0.f);
        btl = glm::vec3(bpos.x - bsize.x / 2.f, bpos.y + bsize.y / 2.f, 0.f);
        bbr = glm::vec3(bpos.x + bsize.x / 2.f, bpos.y - bsize.y / 2.f, 0.f);

        // Check if the point is out of the rect
        if (atl.x > bbr.x)
            return false;

        if (abr.x < btl.x)
            return false;

        if (abr.y > btl.y)
            return false;

        if (atl.y < bbr.y)
            return false;

        return true;
    }

    //Check two circle collision
    //return true if collieded, and false otherwise
    bool Collision::CircleCircleCollisionCheck(Object* pA, Object* pB)
    {
        if ((pA == nullptr) || (pB == nullptr))
        {
            return false;
        }
        Transform* a_pTransform = static_cast<Transform*>(pA->GetComponent(CT_TRANSFORM));
        Transform* b_pTransform = static_cast<Transform*>(pB->GetComponent(CT_TRANSFORM));

        if (a_pTransform == nullptr || b_pTransform == nullptr)
        {
            b_pTransform = 0;
            return false;
        }

        glm::vec2 asize = a_pTransform->getScale();
        glm::vec2 bsize = b_pTransform->getScale();

        glm::vec3 apos = glm::vec3(a_pTransform->getPosition().x * width, a_pTransform->getPosition().y * height, 0.f);
        glm::vec3 bpos = glm::vec3(b_pTransform->getPosition().x * width, b_pTransform->getPosition().y * height, 0.f);

        glm::vec2 minimumVec = ((asize / 2.f) + (bsize / 2.f)); // Collide position
        float minimumLength = glm::length(minimumVec);

        glm::vec3 to_distance = apos - bpos;

        float distLength = glm::length(to_distance);
        glm::vec3 normalVec = glm::normalize(to_distance);


        float dist = glm::length(to_distance);

        if (dist <= minimumLength) // Calculate distance between two
        {
            return true;
        }
        return false;
    }

    //Check collision among circle and rectangle object
    //return true if collided, and false otherwise
    bool Collision::CircleRectCollisionCheck(Object* pA, Object* pB)
    {
        Transform* a_pTransform = static_cast<Transform*>(pA->GetComponent(CT_TRANSFORM));
        Transform* b_pTransform = static_cast<Transform*>(pB->GetComponent(CT_TRANSFORM));

        if (a_pTransform == nullptr || b_pTransform == nullptr)
            return false;

        // A is Rect
        glm::vec3 a_rect_size = a_pTransform->getScale();
        glm::vec3 b_radius = b_pTransform->getScale();

        glm::vec3 a_rect_pos = glm::vec3(a_pTransform->getPosition().x * width, a_pTransform->getPosition().y * height, 0.f);
        glm::vec3 b_circle_pos = glm::vec3(b_pTransform->getPosition().x * width, b_pTransform->getPosition().y * height, 0.f);

        glm::vec3 a_distance = glm::vec3(0.f, 0.f, 0.f);
        a_distance.x = (glm::abs(b_circle_pos.x - a_rect_pos.x));
        a_distance.y = (glm::abs(b_circle_pos.y - a_rect_pos.y));

        glm::vec3 normalVec = glm::normalize(a_distance);
        if (a_distance.x > (a_rect_size.x / 2.f) + (b_radius.x / 2.f))
            return false;
        if (a_distance.y > (a_rect_size.y / 2.f) + (b_radius.y / 2.f))
            return false;

        if (a_distance.x <= (a_rect_size.x / 2.f) + (b_radius.x / 2.f))
        {
            return true;
        }
        if (a_distance.y <= (a_rect_size.y / 2.f) + (b_radius.y / 2.f))
        {
            return true;
        }

        glm::vec2 a_length(a_distance.x - a_rect_size.x / 2.f, a_distance.y - a_rect_size.y / 2.f);

        const float lengthSq = glm::dot(a_length, a_length);

        return lengthSq <= b_radius.x * b_radius.y;
    }
    //Check among circle and line collision
    //return true if collided, and false otherwise
    bool Collision::RayCastCollisionCheck(Object* pA, float bullet_range)
    {
        Transform* a_pTransform = static_cast<Transform*>(pA->GetComponent(CT_TRANSFORM));
        Transform* b_pTransform;

        glm::vec3 player_pos = glm::vec3(a_pTransform->getPosition().x * width, a_pTransform->getPosition().y * height, 0.f);

        int mouse_x;
        int mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        glm::vec2 world_mouse_two(mouse_x, mouse_y);
        world_mouse_two = APPLICATION->screen_to_world(world_mouse_two);

        // I'm gonna be a ray.
        glm::vec3 world_mouse_three_normalized = glm::normalize(glm::vec3(world_mouse_two.x, world_mouse_two.y, 0.f));

        bool collisionSomething = false;
        ObjectType whoamI_type = OT_NONE;
        ObjectID whoamI_ID = 0;

        while (!collisionSomething)
        {
            // check for only zombies and walls
            for (std::vector<RigidBody*>::iterator it = PHYSICS->walls_and_zombies.begin();
                 it != PHYSICS->walls_and_zombies.end(); it++)
            {
                b_pTransform = static_cast<Transform*>((*it)->GetOwner()->GetComponent(CT_TRANSFORM));

                glm::vec3 b_rect_pos = glm::vec3(b_pTransform->getPosition().x * width, b_pTransform->getPosition().y * height, 0.f);
                glm::vec2 b_rect_size = b_pTransform->getScale();

                glm::vec3 btl, bbr; // Wall
                btl = glm::vec3(b_rect_pos.x - b_rect_size.x / 2.f, b_rect_pos.y + b_rect_size.y / 2.f, 0.f);
                bbr = glm::vec3(b_rect_pos.x + b_rect_size.x / 2.f, b_rect_pos.y - b_rect_size.y / 2.f, 0.f);

                if (player_pos.x < btl.x) // left
                    collisionSomething = false;
                else if (player_pos.x > bbr.x)
                    collisionSomething = false;
                else if (player_pos.y > btl.y)
                    collisionSomething = false;
                else if (player_pos.y < bbr.y)
                    collisionSomething = false;
                else
                {
                    collisionSomething = true;
                    whoamI_type = (*it)->GetOwner()->GetObjType();
                    whoamI_ID = (*it)->GetOwner()->GetObjectID();
                    (*it)->GetOwner()->is_collide = true;
                    break;
                }
            }
            // Not too slow, let's go ray, more faster!
            player_pos += (world_mouse_three_normalized * 10.f);
            if (player_pos.x < JSONREADER->getWall8Pos().x * width)
                break;
            else if (player_pos.x > JSONREADER->getWall7Pos().x * width)
                break;
            else if (player_pos.y < JSONREADER->getWall4Pos().y * height)
                break;
            else if (player_pos.y > JSONREADER->getWall3Pos().y * height)
                break;
        }
        if (whoamI_type == OT_ZOMBIE)
        {
            return true;
        }
        if (whoamI_type == OT_WALL)
        {
            return false;
        }
        return false;
    }
    //Check raycasting bullet for gamepad
    //return true if collided, and false otherwise
    bool Collision::RayCastCollisionCheckForPad(Object* pA, float bullet_range)
    {
        Transform* a_pTransform = static_cast<Transform*>(pA->GetComponent(CT_TRANSFORM));
        Transform* b_pTransform;

        glm::vec3 player_pos = glm::vec3(a_pTransform->getPosition().x * width, a_pTransform->getPosition().y * height, 0.f);

        pad = APPLICATION->get_right_pad();
        pad = APPLICATION->screen_to_world(pad);

        // I'm gonna be a ray
        glm::vec3 pad_normal_vec = glm::normalize(glm::vec3(pad.x, pad.y, 0.f));

        bool collisionSomething = false;
        ObjectType whoamI_type = OT_NONE;

        while (!collisionSomething)
        {
            for (std::vector<RigidBody*>::iterator it = PHYSICS->walls_and_zombies.begin();
                 it != PHYSICS->walls_and_zombies.end(); it++)
            {
                b_pTransform = static_cast<Transform*>((*it)->GetOwner()->GetComponent(CT_TRANSFORM));

                glm::vec3 b_rect_pos = glm::vec3(b_pTransform->getPosition().x * width, b_pTransform->getPosition().y * height, 0.f);
                glm::vec2 b_rect_size = b_pTransform->getScale();

                glm::vec3 btl, bbr; // Wall
                btl = glm::vec3(b_rect_pos.x - b_rect_size.x / 2.f, b_rect_pos.y + b_rect_size.y / 2.f, 0.f);
                bbr = glm::vec3(b_rect_pos.x + b_rect_size.x / 2.f, b_rect_pos.y - b_rect_size.y / 2.f, 0.f);

                if (player_pos.x < btl.x) // left
                    collisionSomething = false;
                else if (player_pos.x > bbr.x)
                    collisionSomething = false;
                else if (player_pos.y > btl.y)
                    collisionSomething = false;
                else if (player_pos.y < bbr.y)
                    collisionSomething = false;
                else
                {
                    collisionSomething = true;
                    whoamI_type = (*it)->GetOwner()->GetObjType();
                    (*it)->GetOwner()->is_collide = true;
                    break;
                }
            }
            // Not too slow, let's go ray, more faster!
            player_pos += (pad_normal_vec * 10.f);
            if (player_pos.x < JSONREADER->getWall8Pos().x * width)
                break;
            else if (player_pos.x > JSONREADER->getWall7Pos().x * width)
                break;
            else if (player_pos.y < JSONREADER->getWall4Pos().y * height)
                break;
            else if (player_pos.y > JSONREADER->getWall3Pos().y * height)
                break;
        }
        if (whoamI_type == OT_ZOMBIE)
        {
            return true;
        }
        if (whoamI_type == OT_WALL)
        {
            return false;
        }
        return false;
    }
    // Assign the distance between player and wall
    // To use for light logic
    void Collision::SaveWallDistance(Object* pA)
    {
        Transform* a_pTransform = static_cast<Transform*>(pA->GetComponent(CT_TRANSFORM));
        Transform* b_pTransform;
        RigidBody* a_rigidbody = static_cast<RigidBody*>(pA->GetComponent(CT_RIGID_BODY));

        glm::vec3 player_pos = glm::vec3(a_pTransform->getPosition().x * width, a_pTransform->getPosition().y * height, 0.f);
        glm::vec3 player_pos2 = player_pos;
        glm::vec3 save_player_pos = player_pos;

        int mouse_x;
        int mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        glm::vec2 world_mouse_two(mouse_x, mouse_y);
        world_mouse_two = APPLICATION->screen_to_world(world_mouse_two);

        // I'm gonna be a ray
        glm::vec3 world_mouse_three_normalized = glm::normalize(glm::vec3(world_mouse_two.x, world_mouse_two.y, 0.f));
        float degree = 15.f;
        glm::vec3 positive_direct_direction = world_mouse_three_normalized * cos(glm::radians(degree));
        glm::vec3 negative_direct_direction = world_mouse_three_normalized * cos(glm::radians(-degree));

        bool collisionSomething = false;
        ObjectType whoamI_type = OT_NONE;

        if (!ENGINE->isPause)
        {
            while (!collisionSomething)
            {
                // check for only walls
                for (std::vector<RigidBody*>::iterator it = PHYSICS->walls.begin();
                     it != PHYSICS->walls.end(); it++)
                {
                    b_pTransform = static_cast<Transform*>((*it)->GetOwner()->GetComponent(CT_TRANSFORM));

                    glm::vec3 b_rect_pos = glm::vec3(b_pTransform->getPosition().x * width, b_pTransform->getPosition().y * height, 0.f);
                    glm::vec2 b_rect_size = b_pTransform->getScale();

                    glm::vec3 btl, bbr; // Wall
                    btl = glm::vec3(b_rect_pos.x - b_rect_size.x / 2.f, b_rect_pos.y + b_rect_size.y / 2.f, 0.f);
                    bbr = glm::vec3(b_rect_pos.x + b_rect_size.x / 2.f, b_rect_pos.y - b_rect_size.y / 2.f, 0.f);

                    if ((player_pos.x < btl.x) && (player_pos2.x < btl.x)) // left
                        collisionSomething = false;
                    else if ((player_pos.x > bbr.x) && (player_pos2.x > bbr.x))
                        collisionSomething = false;
                    else if ((player_pos.y > btl.y) && (player_pos2.y > btl.y))
                        collisionSomething = false;
                    else if ((player_pos.y < bbr.y) && (player_pos2.y < bbr.y))
                        collisionSomething = false;
                    else
                    {
                        collisionSomething = true;
                        (*it)->GetOwner()->is_collide = true;
                        a_rigidbody->wall_distance = Min(glm::length(player_pos - save_player_pos), glm::length(player_pos2 - save_player_pos)) / 840.f;
                        break;
                    }
                }
                // Not too slow, let's go ray, more faster!
                player_pos += positive_direct_direction * 10.f;
                player_pos2 += negative_direct_direction * 10.f;

                // Prevent to go out of the map
                if (player_pos.x < JSONREADER->getWall8Pos().x * width)
                    break;
                else if (player_pos.x > JSONREADER->getWall7Pos().x * width)
                    break;
                else if (player_pos.y < JSONREADER->getWall4Pos().y * height)
                    break;
                else if (player_pos.y > JSONREADER->getWall3Pos().y * height)
                    break;

                if (player_pos2.x < JSONREADER->getWall8Pos().x * width)
                    break;
                else if (player_pos2.x > JSONREADER->getWall7Pos().x * width)
                    break;
                else if (player_pos2.y < JSONREADER->getWall4Pos().y * height)
                    break;
                else if (player_pos2.y > JSONREADER->getWall3Pos().y * height)
                    break;
            }
        }
    }
    // Assign the distance between player and wall
    // To use for light logic only for game pad
    void Collision::SaveWallDistanceForPad(Object* pA)
    {
        Transform* a_pTransform = static_cast<Transform*>(pA->GetComponent(CT_TRANSFORM));
        Transform* b_pTransform;
        RigidBody* a_rigidbody = dynamic_cast<RigidBody*>(pA->GetComponent(CT_RIGID_BODY));

        glm::vec3 player_pos = glm::vec3(a_pTransform->getPosition().x * width, a_pTransform->getPosition().y * height, 0.f);
        glm::vec3 player_pos2 = player_pos;
        glm::vec3 save_player_pos = player_pos;

        pad = APPLICATION->get_right_pad();
        pad = APPLICATION->screen_to_world(pad);

        // I'm gonna be a ray
        glm::vec3 pad_normalized = glm::normalize(glm::vec3(pad.x, pad.y, 0.f));
        float degree = 15.f;
        glm::vec3 positive_direct_direction = pad_normalized * cos(glm::radians(degree));
        glm::vec3 negative_direct_direction = pad_normalized * cos(glm::radians(-degree));

        bool collisionSomething = false;
        ObjectType whoamI_type = OT_NONE;

        if (!ENGINE->isPause)
        {
            while (!collisionSomething)
            {
                // check for only walls
                for (std::vector<RigidBody*>::iterator it = PHYSICS->walls.begin();
                     it != PHYSICS->walls.end(); it++)
                {
                    b_pTransform = static_cast<Transform*>((*it)->GetOwner()->GetComponent(CT_TRANSFORM));

                    glm::vec3 b_rect_pos = glm::vec3(b_pTransform->getPosition().x * width, b_pTransform->getPosition().y * height, 0.f);
                    glm::vec2 b_rect_size = b_pTransform->getScale();

                    glm::vec3 btl, bbr; // Wall
                    btl = glm::vec3(b_rect_pos.x - b_rect_size.x / 2.f, b_rect_pos.y + b_rect_size.y / 2.f, 0.f);
                    bbr = glm::vec3(b_rect_pos.x + b_rect_size.x / 2.f, b_rect_pos.y - b_rect_size.y / 2.f, 0.f);

                    if ((player_pos.x < btl.x) && (player_pos2.x < btl.x)) // left
                        collisionSomething = false;
                    else if ((player_pos.x > bbr.x) && (player_pos2.x > bbr.x))
                        collisionSomething = false;
                    else if ((player_pos.y > btl.y) && (player_pos2.y > btl.y))
                        collisionSomething = false;
                    else if ((player_pos.y < bbr.y) && (player_pos2.y < bbr.y))
                        collisionSomething = false;
                    else
                    {
                        collisionSomething = true;
                        (*it)->GetOwner()->is_collide = true;
                        a_rigidbody->wall_distance = Min(glm::length(player_pos - save_player_pos), glm::length(player_pos2 - save_player_pos)) / 840.f;
                        break;
                    }
                }
                // Not too slow, let's go ray, more faster!
                player_pos += positive_direct_direction * 10.f;
                player_pos2 += negative_direct_direction * 10.f;

                // Prevent to go out of the map
                if (player_pos.x < JSONREADER->getWall8Pos().x * width)
                    break;
                else if (player_pos.x > JSONREADER->getWall7Pos().x * width)
                    break;
                else if (player_pos.y < JSONREADER->getWall4Pos().y * height)
                    break;
                else if (player_pos.y > JSONREADER->getWall3Pos().y * height)
                    break;

                if (player_pos2.x < JSONREADER->getWall8Pos().x * width)
                    break;
                else if (player_pos2.x > JSONREADER->getWall7Pos().x * width)
                    break;
                else if (player_pos2.y < JSONREADER->getWall4Pos().y * height)
                    break;
                else if (player_pos2.y > JSONREADER->getWall3Pos().y * height)
                    break;
            }
        }
    }
    //Check among circle and arc object's collision
    //It will be used the enemy's viewpoint
    //return true if collided, and false otherwise
    // It can collide with circle, ONLY
    bool Collision::FieldViewCollisionCheck(Object* pA, Object* pB, float view_range)
    {
        // A = Player = Circle, B = ZombieView = Arc_View
        Transform* a_pTransform = static_cast<Transform*>(pA->GetComponent(CT_TRANSFORM));
        Transform* b_pTransform = static_cast<Transform*>(pB->GetComponent(CT_TRANSFORM));

        if ((pA->GetObjType() == OT_PLAYER) && (pB->GetObjType() == OT_ZOMBIE))
        {
            if (a_pTransform == nullptr || b_pTransform == nullptr)
                return false;

            glm::vec2 a_size = a_pTransform->getScale();
            glm::vec2 b_size = b_pTransform->getScale();

            glm::vec3 apos = glm::vec3(a_pTransform->getPosition().x * width, a_pTransform->getPosition().y * height, 0.f);
            glm::vec3 bpos = glm::vec3(b_pTransform->getPosition().x * width, b_pTransform->getPosition().y * height, 0.f);

            glm::vec2 minimumVec = ((a_size / 2.f) + (b_size / 2.f)); // Collide position

            glm::vec3 to_distance = apos - bpos;

            // Circle-Circle collision check
            auto minimumLength = (glm::length(minimumVec) * view_range);
            float dist = glm::length(to_distance);

            if (dist <= minimumLength) // Calculate distance between two
            {
                // 0. CircleCircleCollisionCheck(pA, pB)
                // 1. Rotation of Zombie vector
                // 2. player pos - zombie pos vector
                // 3. float angle = glm::angle(player pos, zombie pos);
                // 4. Rotation +- theta/2 < theta
                // return true;
                float rot_b = b_pTransform->getRotation().z;
                float rot_b_degree = glm::degrees(rot_b);
                glm::vec2 direction = b_pTransform->getPosition() - a_pTransform->getPosition();
                float angle_radian = glm::acos(glm::dot(glm::vec2(1.f, 0.f), direction) / (glm::length(direction)));
                float angle_degree = glm::degrees(angle_radian);

                float theta = 30.f;

                float real_theta_plus = rot_b_degree + theta;
                float real_theta_minus = rot_b_degree - theta;

                if (a_pTransform->getPosition().y > b_pTransform->getPosition().y)
                {
                    float offset = 180 - angle_degree;
                    angle_degree = 180 + offset;
                }
                if (rot_b_degree + theta >= 360)
                {
                    float offset = rot_b_degree + theta - 360;
                    rot_b_degree = 360 - offset;
                }

                if (rot_b_degree < theta) // if rot_b_degree - theta < 0
                {
                    float offset = rot_b_degree - theta;
                    real_theta_minus = 360 + offset;
                    if ((angle_degree > real_theta_minus))
                    {
                        return true;
                    }
                }
                if (rot_b_degree + theta > 360)
                {
                    float offset = rot_b_degree + theta - 360;
                    real_theta_plus = offset;
                    if ((angle_degree > (360 - real_theta_plus)))
                    {
                        return true;
                    }
                }
                else if (((rot_b_degree + theta) > angle_degree) && ((rot_b_degree - theta) < angle_degree))
                {
                    return true;
                }
            }
        }
        return false;
    }
    //check among mouse position and rectangle
    //return false if it doesn't collide, and true otherwise
    bool Collision::MouseRectCollisionCheck(Object* pA)
    {
        // Object has HUD component
        Transform* a_pTransform = static_cast<Transform*>(pA->GetComponent(CT_TRANSFORM));

        glm::vec2 a_pos = a_pTransform->getPosition();
        glm::vec2 a_size = a_pTransform->getScale();
        //Mouse
        int mouse_x;
        int mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        glm::vec2 world_mouse(mouse_x, mouse_y);

        glm::vec3 atl, abr;
        atl = glm::vec3(a_pos.x - a_size.x / 2.f, a_pos.y - a_size.y / 2.f, 0.f);
        abr = glm::vec3(a_pos.x + a_size.x / 2.f, a_pos.y + a_size.y / 2.f, 0.f);

        if (atl.x > mouse_x)
            return false;

        if (abr.x < mouse_x)
            return false;

        if (atl.y > mouse_y)
            return false;

        if (abr.y < mouse_y)
            return false;

        return true;
    }
    //check among mouse position and rectangle
    //return false if it doesn't collide, and true otherwise
    //It will be used only in EDIT MODE.
    //It can click and drop the object.
    bool Collision::MouseRectCollisionCheck_edit(Object* pA, glm::vec3 pos)
    {
        float Camera_Z = GRAPHICS->camera_system->m_position.z;
        // Object
        Transform* a_pTransform = static_cast<Transform*>(pA->GetComponent(CT_TRANSFORM));

        glm::vec2 a_pos = a_pTransform->getPosition();

        glm::vec2 a_size = a_pTransform->getScale();
        //Mouse
        int mouse_x;
        int mouse_y;
        float world_x, world_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        world_x = Camera_Z * (((float)mouse_x - 640.f) / 840.f) + pos.x;
        world_y = Camera_Z * (-(float)mouse_y + 360.f) / 840.f + pos.y;


        glm::vec3 atl, abr;

        atl = glm::vec3(a_pos.x - (a_size.x / 640.f) / 2.f, a_pos.y - (a_size.y / 640.f) / 2.f, 0.f);
        abr = glm::vec3(a_pos.x + (a_size.x / 640.f) / 2.f, a_pos.y + (a_size.y / 640.f) / 2.f, 0.f);

        if (atl.x > world_x)
            return false;

        if (abr.x < world_x)
            return false;

        if (atl.y > world_y)
            return false;

        if (abr.y < world_y)
            return false;

        return true;
    }
}
