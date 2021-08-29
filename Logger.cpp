/**
 * Logger.cpp - a simple Logger class
 *
 * Created by Haoyuan Li on 2021/07/20
 * Last Modified: 2021/08/29 10:02:08
 */

#include "Logger.hpp"
#include <cstdio>

using std::string;

Logger::Logger()
{
}

Logger::~Logger()
{
}

bool Logger::init(const string &pathname)
{
        bool state = false;
        if (log_.open(pathname) && log_.clear())
                state = true;
        return state;
}

void Logger::trace(const string &msg)
{
        string message{" [T] "};
        add_message(message + msg);
}

void Logger::debug(const string &msg)
{
        string message{" [D] "};
        add_message(message + msg);
}

void Logger::info(const string &msg)
{
        string message{" [I] "};
        add_message(message + msg);
}

void Logger::warning(const string &msg)
{
        string message{" [W] "};
        add_message(message + msg);
}

void Logger::error(const string &msg)
{
        string message{" [E] "};
        add_message(message + msg);
}

void Logger::fatal(const string &msg)
{
        string message{" [F] "};
        add_message(message + msg);
}
