/**
 * Logger.cpp - a simple Logger class
 *
 * Created by Haoyuan Li on 2021/07/20
 * Last Modified: 2021/08/26 12:35:51
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
        string message = msg;
        add_message(message.insert(0, " [T] "));
}

void Logger::debug(const string &msg)
{
        string message = msg;
        add_message(message.insert(0, " [D] "));
}

void Logger::info(const string &msg)
{
        string message = msg;
        add_message(message.insert(0, " [I] "));
}

void Logger::warning(const string &msg)
{
        string message = msg;
        add_message(message.insert(0, " [W] "));
}

void Logger::error(const string &msg)
{
        string message = msg;
        add_message(message.insert(0, " [E] "));
}

void Logger::fatal(const string &msg)
{
        string message = msg;
        add_message(message.insert(0, " [F] "));
}
