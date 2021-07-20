/**
 * Logger.hpp - the Logger class
 *
 * depend on SDL2
 *
 * Created by Haoyuan Li on 2021/07/20
 * Last Modified: 2021/07/20 22:15:25
 */

#include <SDL2/SDL.h>
#include <string>
#include <cstdio>

class Logger {
private:
        static FILE *log;
        static bool lock;
public:
        Logger();
        ~Logger();
        void init(const std::string &fname);
        void free();
        void msg(const std::string &message);
        void error();
        void error(const std::string &err);
        void warn(const std::string &warning);
};
