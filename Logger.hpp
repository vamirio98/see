/**
 * Logger.hpp - the Logger class
 *
 * depend on SDL2
 *
 * Created by Haoyuan Li on 2021/07/20
 * Last Modified: 2021/07/20 22:15:25
 */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <SDL2/SDL.h>
#include <string>
#include <cstdio>
#include <ctime>

class Logger {
private:
        static FILE *log;
        static bool lock;
        static time_t t;
        static struct tm *tp;
        static std::string tstr;

public:
        static Logger *get_instance()
        {
                static Logger l;
                return &l;
        }
        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;

private:
        Logger();
        ~Logger();

public:
        FILE *init(const std::string &fname);
        void free();
        void get_current_time();
        void msg(const std::string &message);
        void error(const std::string &msg);
        void warn(const std::string &warning);
};

#endif
