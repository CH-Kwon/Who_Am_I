/**
\file        Controller.hpp
\author      SeongHyun Hong
\par         email: tjdgus3174@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Component.hpp"
#ifdef _WIN32
    #include "../../WhoAmI/Include/GameLogic.h"
#else //apple
    #include "GameLogic.h"
#endif

#include <list>

namespace FindersEngine
{
	class Controller : public Component
	{
	public:
		Controller() : Component(CT_CONTROLLER)
		{
			iterpController = GAMELOGIC->Insert(this);
		}
		~Controller()
		{
			GAMELOGIC->Erase(iterpController);
		}

		virtual void Init() = 0;

		virtual void Update(float deltaTime) = 0;

	private:
		std::list <Controller*>::iterator iterpController;
	};
};


#endif // !CONTROLLER_H_
