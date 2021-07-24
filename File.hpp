/**
 * File.hpp - the File class
 *
 * contains basic file operations
 *
 * Created by Haoyuan Li on 2021/07/21
 * Last Modified: 2021/07/24 23:36:35
 */

#ifndef FILE_HPP
#define FILE_HPP

#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define IS_REG_FILE 0
#define IS_DIR 1
#define UNKNOWN 2

class File {
private:
        // use for file
        std::string filename;   // the current filename
        FILE *fp;       // point to the current file

        // use for directory
        std::string dir;       // the current directory
        std::vector<std::string> file_list;
        size_t index;   // the current file index

private:
        int open_file(const std::string &filename, const std::string &mode);

public:
        File();
        ~File() = default;
        File(const File &) = delete;
        File &operator=(const File &) = delete;

public:
        // common
        bool exists(const std::string &filename);
        std::string::size_type find_last_delimiter(const std::string &filename);
        int get_type(const std::string &filename);
        void move_to_prev_file();
        std::string get_curr_filename();
        void move_to_next_file();
        int open(const std::string &filename);
        void close();

        // use for file
        int open(const std::string &filename, const std::string &mode);
        std::string get_full_filename();
        std::string get_ext();
        std::string get_filename_without_path();
        std::string get_filename_without_path(const std::string &filename);
        std::string get_path();
        std::string get_path(const std::string &filename);

        // use for directory
        std::vector<std::string> get_file_list();
        void cd(const std::string &dirname);
};

#endif
