/**
 * Logger.cpp - the Logger class
 *
 * Created by Haoyuan Li on 2021/07/20
 * Last Modified: 2021/07/20 22:22:14
 */

#include "Logger.hpp"

Logger::Logger()
{
}

Logger::~Logger()
{
        this->quit();
}

void Logger::init(const string &fname)
{
        if (lock)
                return;
        log = fopen(fname.c_str(), "w");
        lock = true;
}

void Logger::quit()
{
        fclose(log);
        lock = false;
}

void Logger::error()
{
        fprintf(log, "Error: %s\n", SDL_GetError());
}

void Logger::warn(const string &warning)
{
        fprintf(log, "Warn: %s", warning.c_str());
}
