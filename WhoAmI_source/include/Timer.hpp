/**
\file        LTimer.hpp
\author      Changuk Lee
\par         email: leechanguk0510@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once

//Singleton Pattern
#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>

namespace FindersEngine
{

	class Timer
	{
	public:
		Timer() {}; //cannot create over...
		// Only interface is getInstace()
		// How to use? Timer::getInstance().~
		static Timer& GetInstance()
		{
			static Timer timer; //itself!
			return timer;
		}

		void Init()
		{
			startTime = prevTime = std::chrono::high_resolution_clock::now();
			currTime = prevTime;
		}

		float GetDeltaTime(void)
		{
			using namespace std::chrono;

			currTime = high_resolution_clock::now();

			duration<float> delta_time(currTime - prevTime);

			prevTime = high_resolution_clock::now();

			return delta_time.count();
		}

		float GetTime(void)
		{
			using namespace std::chrono;

			currTime = high_resolution_clock::now();

			duration<float> delta_time(currTime - startTime);

			//prevTime = high_resolution_clock::now();

			return delta_time.count();
		}

	private:
		
		Timer(const Timer& timer) = delete; //cannot copy it
		Timer& operator=(const Timer& timer) = delete; //cannot assignment it		

		std::chrono::time_point<std::chrono::high_resolution_clock> prevTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> currTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	};
};



#endif // !TIMER_H_
