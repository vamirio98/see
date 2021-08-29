/**
 * Timer.hpp - the Timer class
 *
 * Created by Haoyuan Li on 2021/07/26
 * Last Modified: 2021/08/29 10:36:22
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_

class Timer {
public:
        Timer() = default;
        ~Timer() = default;

        /**
         * @brief Start timing
         */
        void start();

        /**
         * @brief Stop timing
         */
        void stop();

        /**
         * @brief Pause timing
         */
        void pause();

        /**
         * @brief Resume timing
         */
        void resume();

        /**
         * @brief Get the timer running time
         *
         * @return The running time, ms
         */
        long long get_ticks();

        /**
         * @brief Check whether the timer is running
         */
        bool is_started();

        /**
         * @brief Check whether the timer is paused
         */
        bool is_paused();

private:
        long long start_ms_{0};   // the clock time when the timer started, ms
        long long pause_ms_{0};   // the clock time when the timer paused, ms

        // the timer status
        bool started_{false};
        bool paused_{false};

private:
        /**
         * @brief Get the real-time clock for the system
         *
         * @return The real-time in milliseconds
         */
        static long long get_sys_ticks();
};

#endif
