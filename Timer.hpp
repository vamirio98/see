/**
 * Timer.hpp - the Timer class
 *
 * depend on SDL2, a timer instance can run not more than ~49 days, see
 * SDL_timer.h for more information
 *
 * Created by Haoyuan Li on 2021/07/26
 * Last Modified: 2021/07/26 10:39:46
 */

#ifndef TIMER_HPP
#define TIMER_HPP

#include <SDL2/SDL_timer.h>

class Timer {
public:
        Timer();
        ~Timer() = default;

        void start();
        void stop();
        void pause();
        void resume();

        Uint32 get_ticks();

        // check the status of the timer
        bool is_started();
        bool is_paused();

private:
        Uint32 start_ms;        // the clock time when the timer started, ms
        Uint32 pause_ms;        // the clock time when the timer paused, ms
        // the timer status
        bool started;
        bool paused;
};

#endif
