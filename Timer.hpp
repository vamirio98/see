/**
 * Timer.hpp - the Timer class
 *
 * depend on SDL2, a timer instance can run not more than ~49 days, see
 * SDL_timer.h for more information
 *
 * Created by Haoyuan Li on 2021/07/26
 * Last Modified: 2021/07/26 15:38:09
 */

#ifndef TIMER_HPP
#define TIMER_HPP

#include <SDL2/SDL_timer.h>

class Timer {
public:
        Timer();
        ~Timer() = default;

        /**
         * \brief Start timing
         */
        void start();

        /**
         * \brief Stop timing
         */
        void stop();

        /**
         * \brief Pause timing
         */
        void pause();

        /**
         * \brief Resume timing
         */
        void resume();

        /**
         * \brief Get the timer running time
         *
         * \return The running time, ms
         */
        Uint32 get_ticks();


        /**
         * \brief Check whether the timer is running
         */
        bool is_started();

        /**
         * \brief Check whether the timer is paused
         */
        bool is_paused();

private:
        Uint32 start_ms;        // the clock time when the timer started, ms
        Uint32 pause_ms;        // the clock time when the timer paused, ms

        // the timer status
        bool started;
        bool paused;
};

#endif
