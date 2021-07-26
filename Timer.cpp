/**
 * Timer.cpp - the Timer class
 *
 * depend on SDL2, a timer instance can run not more than ~49 days, see
 * SDL_timer.h for more information
 *
 * Created by Haoyuan Li on 2021/07/26
 * Last Modified: 2021/07/26 10:40:03
 */

#include "Timer.hpp"

Timer::Timer()
{
        start_ms = 0;
        pause_ms = 0;
        started = false;
        paused = false;
}

/**
 * \brief Start timing
 */
void Timer::start()
{
        started = true;
        paused = false;
        start_ms = SDL_GetTicks();
        pause_ms = 0;
}

/**
 * \brief Stop timing
 */
void Timer::stop()
{
        started = false;
        paused = false;
        start_ms = 0;
        pause_ms = 0;
}

/**
 * \brief Pause timing
 */
void Timer::pause()
{
        if (started && !paused) {
                paused = true;
                pause_ms = SDL_GetTicks() - start_ms;
                start_ms = 0;
        }
}

/**
 * \brief Resume timing
 */
void Timer::resume()
{
        if (started && paused) {
                paused = false;
                start_ms = SDL_GetTicks() - pause_ms;
                pause_ms = 0;
        }
}

/**
 * \brief Get the timer running time
 */
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

/**
 * \brief Check whether the timer is running
 */
bool Timer::is_started()
{
        return started;
}

/**
 * \brief Check whether the timer is paused
 */
bool Timer::is_paused()
{
        return started && paused;
}
