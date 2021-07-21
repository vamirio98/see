/**
 * Logger.cpp - the Logger class
 *
 * Created by Haoyuan Li on 2021/07/20
 * Last Modified: 2021/07/20 22:22:14
 */

#include "Logger.hpp"

using std::string;

FILE *Logger::log = nullptr;
bool Logger::lock = false;

Logger::Logger()
{
}

Logger::~Logger()
{
        free();
}

FILE *Logger::init(const string &fname)
{
        if (lock)
                return nullptr;
        log = fopen(fname.c_str(), "w");
        lock = true;
        return log;
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

void Logger::error(const string &msg)
{
        fprintf(log, "[Error] %s: %s\n", msg.c_str(), SDL_GetError());
}

void Logger::warn(const string &warning)
{
        fprintf(log, "[Warn] %s", warning.c_str());
}
