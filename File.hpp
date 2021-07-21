/**
 * File.hpp - the File class
 *
 * contains basic file operations
 *
 * Created by Haoyuan Li on 2021/07/21
 * Last Modified: 2021/07/22 00:05:56
 */

#include <cstdio>
#include <string>

class File {
private:
        std::string fname;
        FILE *fp;

private:
        std::string::size_type find_last_delimiter();

public:
        File();
        ~File() = default;
        File(const File &) = delete;
        File &operator=(const File &) = delete;

public:
        int open(const std::string &filename, const std::string &mode);
        void close();
        std::string get_full_filename();
        std::string get_ext();
        std::string get_filename_without_path();
        std::string get_path();
};
