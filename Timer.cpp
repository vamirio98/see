/**
 * Timer.cpp - the Timer class
 *
 * Created by Haoyuan Li on 2021/07/26
 * Last Modified: 2021/08/29 10:39:16
 */

#include "Timer.hpp"

#include <ctime>

void Timer::start()
{
        started_ = true;
        paused_ = false;
        start_ms_ = get_sys_ticks();
        pause_ms_ = 0;
}

void Timer::stop()
{
        started_ = false;
        paused_ = false;
        start_ms_ = 0;
        pause_ms_ = 0;
}

void Timer::pause()
{
        if (started_ && !paused_) {
                paused_ = true;
                pause_ms_ = get_sys_ticks() - start_ms_;
                start_ms_ = 0;
        }
}

void Timer::resume()
{
        if (started_ && paused_) {
                paused_ = false;
                start_ms_ = get_sys_ticks() - pause_ms_;
                pause_ms_ = 0;
        }
}

long long Timer::get_ticks()
{
        long long t = 0;
        if (started_)
                t = paused_ ? pause_ms_ : get_sys_ticks() - start_ms_;
        return t;
}

bool Timer::is_started()
{
        return started_;
}

bool Timer::is_paused()
{
        return started_ && paused_;
}

long long Timer::get_sys_ticks()
{
        struct timespec spec;
        clock_gettime(CLOCK_REALTIME, &spec);
        return (spec.tv_sec * 1000LL + spec.tv_nsec / 1000000LL);
}
