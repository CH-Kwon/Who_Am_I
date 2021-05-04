/**
 \file
 \author
 \par         email:
 \par         course: GAM200
 \date        ?/?/2017
 \brief
 
 */

#pragma once

#ifndef HEADERS_SYSTEMS_H_
#define HEADERS_SYSTEMS_H_

//An instance
#include "Input.h"
#include "LTimer.hpp"
#include "Texture.h"
#include "Timer.hpp"

//SYSTEM
#include "Application.h"
#include "Graphics.h"
#include "ObjectFactory.h"
#include "Physics.h"

#ifdef _WIN32
#include "../../WhoAmI/Include/GameLogic.h"
#include "../../WhoAmI/Include/GameStateManager.h"
#else
#include "GameLogic.h"
#include "GameStateManager.h"
#endif

#endif // !HEADERS_SYSTEMS_H_
