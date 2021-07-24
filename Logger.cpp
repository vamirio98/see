/**
 * Logger.cpp - the Logger class
 *
 * Created by Haoyuan Li on 2021/07/20
 * Last Modified: 2021/07/24 23:03:26
 */

#include "Logger.hpp"

using std::string;

FILE *Logger::log = nullptr;
bool Logger::lock = false;
time_t Logger::t = 0;
struct tm *Logger::tp = nullptr;
string Logger::tstr = "";

Logger::Logger()
{
}

Logger::~Logger()
{
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

void Logger::get_current_time()
{
        time(&t);
        tp = localtime(&t);
        char str[30];
        sprintf(str, "%04d-%02d-%02d %02d:%02d:%02d",
                        tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday,
                        tp->tm_hour, tp->tm_min, tp->tm_sec);
        tstr = str;
}

void Logger::msg(const string &message)
{
        get_current_time();
        fprintf(log, "[%s] [N] %s", tstr.c_str(), message.c_str());
}

void Logger::error(const string &msg)
{
        fprintf(log, "[%s] [E] %s: %s", msg.c_str(),
                        tstr.c_str(), SDL_GetError());
}

void Logger::warn(const string &warning)
{
        fprintf(log, "[%s] [W] %s", tstr.c_str(), warning.c_str());
}
