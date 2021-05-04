/**
\file        LTimer.cpp
\author      Changuk Lee
\par         email: leechanguk0510@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#ifndef LTIMER_HPP_
#define LTIMER_HPP_

#include "Headers_SDL.h"
namespace FindersEngine
{
	class LTimer
	{
	public:
		LTimer()
		{
			// Initialize the variables
			mStartTicks = 0;
			mPausedTicks = 0;

			mPaused = false;
			mStarted = false;
		}

		void start()
		{
			//Start the timer
			mStarted = true;

			//Unpause the timer
			mPaused = false;

			//Get the current clock time
			mStartTicks = SDL_GetTicks();
			mPausedTicks = 0;
		}

		void stop()
		{
			//Stop the timer
			mStarted = false;

			//Unpause the timer
			mPaused = false;

			//Clear tick variables
			mStartTicks = 0;
			mPausedTicks = 0;

		}
		void pause()
		{
			//If the timer is running and isn't already paused
			if (mStarted && !mPaused)
			{
				//Pause the timer
				mPaused = true;

				//Calculate the paused ticks
				mPausedTicks = SDL_GetTicks() - mStartTicks;
				mStartTicks = 0;
			}
		}


		void unpause()
		{
			//If the timer is running and paused
			if (mStarted && mPaused)
			{
				//Unpause the timer
				mPaused = false;

				//Reset the starting ticks
				mStartTicks = SDL_GetTicks() - mPausedTicks;

				//Reset the paused ticks
				mPausedTicks = 0;
			}
		}

		//Gets the timer's time
		Uint32 getTicks()
		{
			//The actual timer time
			Uint32 time = 0;

			//If the timer is running
			if (mStarted)
			{
				//If the timer is paused
				if (mPaused)
				{
					//Return the number of ticks when the timer was paused
					time = mPausedTicks;
				}
				else
				{
					//Return the current time minus the start time
					time = SDL_GetTicks() - mStartTicks;
				}
			}
			return time;
		}

		//Checks the status of the timer
		bool isStarted()
		{
			//Timers is running and paused or unpaused
			return mStarted;
		}

		bool isPaused()
		{
			//Timer is running and paused
			return mPaused && mStarted;
		}

	private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
	};
}

#endif // !LTIMER_HPP_

