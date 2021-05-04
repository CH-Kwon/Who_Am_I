/**
\file        Level1.h
\author      Changuk Lee
\par         email: leechanguk0510@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#ifndef LEVEL_1_H
#define LEVEL_1_H

namespace FindersEngine
{
    class Sprite;
    class Object;
    class Transform;

    void Level1StateLoad(void);
    void Level1StateInit(void);
    void Level1StateUpdate(float dt);
    void Level1StateExit(void);
    void Level1StateUnload(void);

    void random_light1(float dt);

    static Object* HPbar;
    static Object* Armorbar;

    static Transform* Playertransform;

    static Transform* HPbartransform;
    static Sprite* HPbarsprite;

    static Transform* Armorbartransform;
    static Sprite* Armorbarsprite;

    static Transform* Directiontransform;

    static float Hpbarposx;
    static float Armorbarposx;
    static float light_timer;
    static float Font_timer;
    static Object* Numpad;
    static Object* Num1;
    static Object* Num2;
    static Object* Num3;
    static Object* Num4;
    static Object* Num5;
    static Object* Num6;
    static Object* Num7;
    static Object* Num8;
    static Object* Num9;
    static Object* Num0;
    static Object* Num11;
    static Object* Num12;

    static Object* LoseFont;

    static Object* FirstNumber;
    static Object* SecondNumber;
    static Object* ThirdNumber;
    static Object* ForthNumber;

    static int PrintFontCondition;
}

#endif // !LEVEL_1_H
