/**
 * Timer.cpp - the Timer class
 *
 * depend on SDL2, a timer instance can run not more than ~49 days, see
 * SDL_timer.h for more information
 *
 * Created by Haoyuan Li on 2021/07/26
 * Last Modified: 2021/07/26 15:34:03
 */

#include "Timer.hpp"
#include <SDL2/SDL_timer.h>

Timer::Timer()
{
        start_ms = 0;
        pause_ms = 0;
        started = false;
        paused = false;
}

void Timer::start()
{
        started = true;
        paused = false;
        start_ms = SDL_GetTicks();
        pause_ms = 0;
}

void Timer::stop()
{
        started = false;
        paused = false;
        start_ms = 0;
        pause_ms = 0;
}

void Timer::pause()
{
        if (started && !paused) {
                paused = true;
                pause_ms = SDL_GetTicks() - start_ms;
                start_ms = 0;
        }
}

void Timer::resume()
{
        if (started && paused) {
                paused = false;
                start_ms = SDL_GetTicks() - pause_ms;
                pause_ms = 0;
        }
}

Uint32 Timer::get_ticks()
{
        Uint32 time = 0;
        if (started) {
                if (paused)
                        time = pause_ms;
                else
                        time = SDL_GetTicks() - start_ms;
        }
        return time;
}

bool Timer::is_started()
{
        return started;
}

bool Timer::is_paused()
{
        return started && paused;
}