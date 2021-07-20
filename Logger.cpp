/**
 * Logger.cpp - the Logger class
 *
 * Created by Haoyuan Li on 2021/07/20
 * Last Modified: 2021/07/20 22:22:14
 */

#include "Logger.hpp"

using std::string;

Logger::Logger()
{
}

Logger::~Logger()
{
        this->free();
}

void Logger::init(const string &fname)
{
        if (lock)
                return;
        log = fopen(fname.c_str(), "w");
        lock = true;
}

void Logger::free()
{
        fclose(log);
        lock = false;
}

void Logger::msg(const string &message)
{
        fprintf(log, "%s\n", message.c_str());
}

void Logger::error()
{
        fprintf(log, "Error: %s\n", SDL_GetError());
}

void Logger::warn(const string &warning)
{
        fprintf(log, "Warn: %s", warning.c_str());
}
