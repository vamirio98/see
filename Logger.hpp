/**
 * Logger.hpp - a simple Logger class
 *
 * Created by Haoyuan Li on 2021/07/20
 * Last Modified: 2021/08/26 11:37:25
 */

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include "File.hpp"
#include "File_writer.hpp"

#include <string>
#include <ctime>

class Logger {
private:
        File_writer log_;

public:
        Logger();
        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;
        ~Logger();

public:
        /**
         * @brief Initialize a file as a log file, this operation will clear
         *        all contents in the file
         *
         * @param pathname The pathname of the file
         *
         * @return True if succeeded, false otherwise
         */
        bool init(const std::string &pathname);

        /**
         * @brief Add a trace severity message to the log
         *
         * @param msg The message
         */
        void trace(const std::string &msg);

        /**
         * @brief Add a debug severity message to the log
         *
         * @param msg The message
         */
        void debug(const std::string &msg);

        /**
         * @brief Add a informational severity message
         *
         * @param msg The message
         */
        void info(const std::string &msg);

        /**
         * @brief Add a warning severity message to the log
         *
         * @param msg The message
         */
        void warning(const std::string &msg);

        /**
         * @brief Add an error severity message to the log
         *
         * @param msg The message
         */
        void error(const std::string &msg);

        /**
         * @brief Add a fatal severity message to the log
         *
         * @param msg The message
         */
        void fatal(const std::string &msg);

private:
        /**
         * @brief Add a message to the log
         *
         * @param msg The message to be added
         */
        void add_message(const std::string &msg);
};

inline void Logger::add_message(const std::string &msg)
{
        time_t raw_time;
        time(&raw_time);
        std::string t = File::get_time_str(raw_time, "%Y/%m/%d %H:%M:%S");
        t += msg;
        log_.append(t);
}

#endif
