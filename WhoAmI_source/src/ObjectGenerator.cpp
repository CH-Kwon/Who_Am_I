/**
\file        ObjectGenerator.cpp
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "ObjectGenerator.h"
#include "EyeController.h"
#include "Headers_Components.h"
#include "Headers_Controllers.h"
#include "Hud.h"
#include "ObjectFactory.h"
#include "Physics.h"
#include "Object.h"
#define WIDTH 1280
#define HEIGHT 640

namespace FindersEngine
{
    ObjectGenerator* OBJECT_GEN = nullptr;

    ObjectGenerator::ObjectGenerator()
    {
    }
    ObjectGenerator::~ObjectGenerator()
    {
    }

    Object* ObjectGenerator::CreateObject(const std::string& pim, const glm::vec3& pos, const glm::vec3& scale, ObjectType ot, ShapeType st, unsigned id)
    {
        Object* obj = OBJECT_FACTORY->CreateEmptyObject(id);
        obj->SetShapeType(st);
        obj->SetObjType(ot);

        Transform* transform = new Transform();
        transform->setPosition(pos);
        transform->setScale(scale);
        obj->AddComponent(transform);

        Sprite* sprite = new Sprite();
        sprite->LoadTexture(pim);
        obj->AddComponent(sprite);
        obj->AddComponent(new RigidBody(glm::vec3(0, 0, 0), 1.f));
        obj->Init();

        return obj;
    }

    Object* ObjectGenerator::CreateHint(const std::string& pim, const glm::vec3& pos, const glm::vec3& scale, ObjectType ot, ShapeType st, unsigned id)
    {
        Object* obj = OBJECT_FACTORY->CreateEmptyObject(id);
        obj->SetShapeType(st);
        obj->SetObjType(ot);

        Transform* transform = new Transform();
        transform->setPosition(pos);
        transform->setScale(scale);
        obj->AddComponent(transform);

        Sprite* sprite = new Sprite();
        sprite->LoadTexture(pim);
        obj->AddComponent(sprite);
        obj->Init();

        return obj;
    }

    Object* ObjectGenerator::CreateSprite(const std::string& pim, const glm::vec3& pos, const glm::vec3& scale, unsigned id)
    {
        Object* obj = OBJECT_FACTORY->CreateEmptyObject(id);

        Transform* transform = new Transform();
        transform->setPosition(pos);
        transform->setScale(scale);
        obj->AddComponent(transform);

        Sprite* sprite = new Sprite();
        sprite->LoadTexture(pim);
        obj->AddComponent(sprite);
        obj->Init();
        return obj;
    }

    Object* ObjectGenerator::CreateBullet(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& bullet_size, unsigned id)
    {
        Object* bullet = OBJECT_FACTORY->CreateEmptyObject(id);
        bullet->SetShapeType(ST_LINE);
        bullet->SetObjType(OT_BULLET);

        Transform* transform = new Transform();
        transform->setPosition(pos);
        transform->setScale(bullet_size);
        transform->setRotation(rot);
        bullet->AddComponent(transform);
        bullet->AddComponent(new BulletController());

        Sprite* sprite = new Sprite();
        //Todo: Load texture and get texture id
        sprite->LoadTexture("PIN_BULLET.png");
        bullet->AddComponent(sprite);
        bullet->AddComponent(new RigidBody(glm::vec3(0, 0, 0), 1.f));
        bullet->Init();

        return bullet;
    }

    Object* ObjectGenerator::CreatePlayer(const glm::vec3& pos, unsigned id)
    {
        Object* player = OBJECT_FACTORY->CreateEmptyObject(id);
        player->SetShapeType(ST_CIRCLE);
        player->SetObjType(OT_PLAYER);

        Transform* transform = new Transform();
        transform->setPosition(pos);
        transform->setScale(glm::vec3(140.f, 140.f, 1.f));
        player->AddComponent(transform);

        Sprite* sprite = new Sprite();
        //Todo: Load texture and get texture id
        sprite->LoadTexture("PIN_PLAYER2.png");
        player->AddComponent(sprite);

        Camera* camera = new Camera();
        player->AddComponent(camera); // only use one!

        RigidBody* rigidbody = new RigidBody(glm::vec3(0, 0, 0), 1.f);
        player->AddComponent(rigidbody);

        player->AddComponent(new PlayerController());
        player->Init();

        return player;
    }
    Object* ObjectGenerator::CreateWall(const glm::vec3& pos, const glm::vec3& scale, unsigned id)
    {
        Object* wall = OBJECT_FACTORY->CreateEmptyObject(id);
        wall->SetShapeType(ST_RECTANGLE);
        wall->SetObjType(OT_WALL);

        Transform* transform = new Transform();
        transform->setPosition(pos);
        transform->setScale(scale);
        wall->AddComponent(transform);

        Sprite* sprite = new Sprite();
        sprite->LoadTexture("PIN_WALL.png");
        wall->AddComponent(sprite);

        RigidBody* rigidbody = new RigidBody(glm::vec3(0, 0, 0), 1.f);
        wall->AddComponent(rigidbody);

        PHYSICS->walls_and_zombies.push_back(rigidbody);
        PHYSICS->walls.push_back(rigidbody);

        wall->Init();

        return wall;
    }
    Object* ObjectGenerator::CreateZombie(const glm::vec3& pos, unsigned id)
    {
        Object* zombie = OBJECT_FACTORY->CreateEmptyObject(id);
        zombie->SetShapeType(ST_CIRCLE);
        zombie->SetObjType(OT_ZOMBIE);

        Transform* transform = new Transform();
        transform->setPosition(pos);
        transform->setScale(glm::vec3(120, 120, 1));
        zombie->AddComponent(transform);

        Sprite* sprite = new Sprite();
        sprite->LoadTexture("PIN_ZOMBIE.png");
        zombie->AddComponent(sprite);

        RigidBody* rigidbody = new RigidBody(glm::vec3(0, 0, 0), 1.f);
        zombie->AddComponent(rigidbody);
        PHYSICS->walls_and_zombies.push_back(rigidbody);

        zombie->AddComponent(new ZombieController());
        zombie->Init();

        return zombie;
    }

    Object* ObjectGenerator::CreateSpeechBox(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& pim, float lifeTime)
    {
        Object* speech_box1 = OBJECT_FACTORY->CreateEmptyObject(id);
        speech_box1->SetObjType(OT_MESSAGE);
        speech_box1->SetShapeType(ST_HUD);

        Transform* speech_box1_transform = new Transform();
        speech_box1_transform->setPosition(position);
        speech_box1_transform->setScale(scale);
        speech_box1->AddComponent(speech_box1_transform);

        Hud* speech_box1_hud = new Hud();
        speech_box1_hud->LoadTexture(pim);
        speech_box1_hud->RGBA_Color(glm::vec4(1, 0, 0, 0));
        speech_box1_hud->setBlendAlpha(10.f);
        speech_box1->AddComponent(speech_box1_hud);

        HudController* hudController = new HudController();
        hudController->Set_LifeTime(lifeTime);
        speech_box1->AddComponent(hudController);

        speech_box1->Init();
        return speech_box1;
    }

    Object* ObjectGenerator::CreateHud(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& pim, Layer_Order lo)
    {
        Object* hud_object = OBJECT_FACTORY->CreateEmptyObject(id);
        hud_object->SetShapeType(ST_RECTANGLE);

        Transform* transform = new Transform();
        transform->setPosition(position);
        transform->setScale(scale);
        hud_object->AddComponent(transform);

        Hud* hud = new Hud();
        hud->LoadTexture(pim);
		hud->setLayerOrder(lo);        
        hud_object->AddComponent(hud);

        hud->Init();
        return hud_object;
    }

    Object* ObjectGenerator::CreateCollisionHud(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& pim)
    {
        Object* ammohud = OBJECT_FACTORY->CreateEmptyObject(id);
        ammohud->SetShapeType(ST_RECTANGLE);

        Transform* ammohud_transform = new Transform();
        ammohud_transform->setPosition(position);
        ammohud_transform->setScale(scale);
        ammohud->AddComponent(ammohud_transform);

        Hud* ammohud_hud = new Hud();
        ammohud_hud->LoadTexture(pim);
        ammohud->AddComponent(ammohud_hud);

        ammohud->AddComponent(new Collision());
        ammohud->Init();
        return ammohud;
    }
    Object* ObjectGenerator::CreateEye(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& pim)
    {
        Object* eye = OBJECT_FACTORY->CreateEmptyObject(id);
        eye->SetShapeType(ST_RECTANGLE);

        Transform* transform = new Transform();
        transform->setPosition(position);
        transform->setScale(scale);
        eye->AddComponent(transform);

        Hud* hud = new Hud();
        hud->LoadTexture(pim);
        eye->AddComponent(hud);

        eye->AddComponent(new EyeController());
        eye->Init();
        return eye;
    }
    Object* ObjectGenerator::CreateButton(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& pim, std::string str, Layer_Order lo)
    {
        Object* button = OBJECT_FACTORY->CreateEmptyObject(id);
        button->SetShapeType(ST_RECTANGLE);
        button->SetObjType(OT_BUTTON);

        Transform* transform = new Transform();
        transform->setPosition(position);
        transform->setScale(scale);
        button->AddComponent(transform);

        Hud* hud = new Hud();
        hud->LoadTexture(pim);
		hud->setLayerOrder(lo);        
        button->AddComponent(hud);

        Collision* col = new Collision();
        button->AddComponent(col);

        ButtonController* button_controller = new ButtonController();
        button_controller->setName(str);
        button->AddComponent(button_controller);

        button->Init();
        return button;
    }
    Object* ObjectGenerator::CreateAFont(const glm::vec3& pos_offset_bottom_left, float scale, std::string text, const glm::vec3& color, unsigned id, float rotation)
    {
        using namespace glm;

        Object* obj = OBJECT_FACTORY->CreateEmptyObject(id);

        Transform* transform = new Transform();
        transform->setPosition(pos_offset_bottom_left);
        transform->setRotation(vec3(0.0f, 0.0f, rotation)); // ONLY Z-AXIS
        obj->AddComponent(transform);

        SpriteText* sprite_text = new SpriteText();
        sprite_text->setText(text);
        sprite_text->setScale(scale);
        sprite_text->setColor(color);

        obj->AddComponent(sprite_text);

        obj->Init();
        return obj;
    }
    Object* ObjectGenerator::CreatePausebox(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& pim)
    {
        Object* pausebox = OBJECT_FACTORY->CreateEmptyObject(id);
        pausebox->SetShapeType(ST_RECTANGLE);

        Transform* pausebox_transform = new Transform();
        pausebox_transform->setPosition(position);
        pausebox_transform->setScale(scale);
        pausebox->AddComponent(pausebox_transform);

        Hud* pausebox_hud = new Hud();
        pausebox_hud->LoadTexture(pim);
        pausebox->AddComponent(pausebox_hud);

        pausebox->AddComponent(new Collision());
        pausebox->Init();
        return pausebox;
    }
    Object* ObjectGenerator::CreateTextbox(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& pim)
    {
        Object* textbox1 = OBJECT_FACTORY->CreateEmptyObject(id);
        textbox1->SetShapeType(ST_RECTANGLE);

        Transform* textbox1_transform = new Transform();
        textbox1_transform->setPosition(position);
        textbox1_transform->setScale(scale);
        textbox1->AddComponent(textbox1_transform);

        Hud* textbox1_hud = new Hud();
        //textbox1_hud->setBlendAlpha(5.f);
        textbox1_hud->LoadTexture(pim);
        // textbox1_hud->setBlendAlpha(12.f);
        textbox1->AddComponent(textbox1_hud);
        textbox1->Init();

        return textbox1;
    }
    Object* ObjectGenerator::CreateKeyinfo(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& pim, Layer_Order lo)
    {
        Object* ammohud = OBJECT_FACTORY->CreateEmptyObject(id);
        ammohud->SetShapeType(ST_RECTANGLE);

        Transform* ammohud_transform = new Transform();
        ammohud_transform->setPosition(position);
        ammohud_transform->setScale(scale);
        ammohud->AddComponent(ammohud_transform);

        Hud* ammohud_hud = new Hud();
        ammohud_hud->LoadTexture(pim);
        ammohud->AddComponent(ammohud_hud);
		ammohud_hud->setLayerOrder(lo);
		ammohud->AddComponent(ammohud_hud);
        ammohud->AddComponent(new Collision());
        ammohud->Init();
        return ammohud;
    }
    Object* ObjectGenerator::CreateKeyboardMouse(const glm::vec3& position, const glm::vec3& scale, unsigned id, const std::string& pim, Layer_Order lo)
    {
        Object* keyboardmouse = OBJECT_FACTORY->CreateEmptyObject(id);
        keyboardmouse->SetShapeType(ST_RECTANGLE);

        Transform* keyboardmouse_transform = new Transform();
        keyboardmouse_transform->setPosition(position);
        keyboardmouse_transform->setScale(scale);
        keyboardmouse->AddComponent(keyboardmouse_transform);

        Hud* keyboardmouse_hud = new Hud();
        keyboardmouse_hud->LoadTexture(pim);
        keyboardmouse->AddComponent(keyboardmouse_hud);
		keyboardmouse_hud->setLayerOrder(lo);
        keyboardmouse->AddComponent(new Collision());
        keyboardmouse->Init();
        return keyboardmouse;
    }
    Object* ObjectGenerator::CreateBase(const glm::vec3& pos, const glm::vec3& scale, unsigned id)
    {
        Object* base_tile = OBJECT_FACTORY->CreateEmptyObject(id);
        Transform* transform = new Transform();
        transform->setPosition(pos);
        transform->setScale(scale);
        base_tile->AddComponent(transform);

        Sprite* sprite = new Sprite();
        sprite->LoadTexture("PIN_BASE.png");
        base_tile->AddComponent(sprite);
        base_tile->Init();

        return base_tile;
    }
}