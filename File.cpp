/**
 * File.cpp - the File class
 *
 * contains basic file operations
 *
 * Created by Haoyuan Li on 2021/07/21
 * Last Modified: 2021/07/26 15:23:58
 */

#include "File.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <sys/stat.h>

#ifdef unix     // unix
        #include <unistd.h>
        #include <dirent.h>
#else           // WINDOWS
        #include <Windows.h>
        #include <direct.h>
#endif

using string = std::string;
using strvec = std::vector<std::string>;

#ifdef unix
        const string delim = "/";
#else
        const string delim = "\\";
#endif


File::File()
{
}

int File::open_file(const string &filename, const string &mode)
{
        if (!(fp = fopen(filename.c_str(), mode.c_str()))) {
                fprintf(stderr, "[error] couldn't open file %s\n",
                                filename.c_str());
                return -1;
        }
        this->filename = get_filename_without_path(filename);
        return 0;
}

bool File::exists(const string &filename)
{
        if (filename.empty())
                return false;
        struct stat st;
        return !(stat(filename.c_str(), &st));
}

string::size_type File::find_last_delimiter(const string &filename)
{
        if (filename.empty())
                return std::string::npos;
        return filename.find_last_of("/\\");
}

int File::get_type(const string &filename)
{
        if (filename.empty())
                return UNKNOWN;
        int type;

#ifdef unix
        struct stat st;
        lstat(filename.c_str(), &st);
        if (S_ISREG(st.st_mode))
                type = IS_REG_FILE;
        else if (S_ISDIR(st.st_mode))
                type = IS_DIR;
        else
                type = UNKNOWN;
#endif // unix

#ifdef _WIN32
        DWORD attr = GetFileAttributes(filename.c_str());
        if (attr == FILE_ATTRIBUTE_DIRECTORY)
                type = IS_DIR;
        else if (attr == FILE_ATTRIBUTE_COMPRESSED || FILE_ATTRIBUTE_NORMAL ||
                        attr == FILE_ATTRIBUTE_READONLY)
                type = IS_REG_FILE;
        else
                type = UNKNOWN;
#endif // _WIN32

        return type;
}

void File::move_to_prev_file()
{
        if (file_list.empty())
                return;
        auto current = index;
        index = (index == 0) ? index : index - 1;
        // skip files that are not regular files
        while (index != 0 && get_type(dir + delim + file_list[index])
                        != IS_REG_FILE)
                ++index;
        if (get_type(dir + delim + file_list[index]) == IS_REG_FILE) {
                fclose(fp);
                open_file(dir + delim + file_list[index], "r");
        }
        else {
                index = current;
        }
}

string File::get_curr_filename()
{
        if (file_list.empty())
                return "";
        return file_list[index];
}

void File::move_to_next_file()
{
        if (file_list.empty())
                return;
        auto current = index;
        index = (index == file_list.size() - 1) ? index : index + 1;
        // skip files that are not regular files
        while (index != file_list.size() -1 && get_type(
                                dir + delim + file_list[index]) != IS_REG_FILE)
                ++index;
        if (get_type(dir + delim + file_list[index]) == IS_REG_FILE) {
                fclose(fp);
                open_file(dir + delim + file_list[index], "r");
        }
        else {
                index = current;
        }
}

int File::open(const string &filename)
{
        if (filename.empty() || !exists(filename))
                return -1;
        int type = get_type(filename);
        if (type == IS_REG_FILE) {
                open_file(filename, "r");
                dir = get_path(filename);
                get_file_list();
                index = std::find(file_list.begin(), file_list.end(),
                                this->filename) - file_list.begin();
        } else if (type == IS_DIR) {
                dir = filename;
                index = 0;
                get_file_list();
                do {
                        if (file_list.empty()) {
                                this->filename = "";
                                fp = nullptr;
                                break;
                        }
                        // skip files that are not regular files
                        while (index != file_list.size() &&
                                        get_type(dir + delim + file_list[index])
                                        != IS_REG_FILE)
                                ++index;
                        if (index == file_list.size()) {
                                this->filename = "";
                                fp = nullptr;
                                index = 0;
                        } else {
                                open_file(dir + delim + file_list[index], "r");
                        }
                } while (0);
        } else {
                fprintf(stderr, "[error] unknown type: %s\n",
                                filename.c_str());
                return -1;
        }
        return 0;
}

void File::close()
{
        filename.clear();
        if (fp)
                fclose(fp);
        dir.clear();
        file_list.clear();
        index = 0;
}

int File::open(const string &filename, const string &mode)
{
        if (filename.empty() || !exists(filename))
                return -1;
        if(open_file(filename, mode))
                return -1;
        dir = get_path(filename);
        get_file_list();
        index = std::find(file_list.begin(), file_list.end(),
                        this->filename) - file_list.begin();
        return 0;
}

string File::get_full_filename()
{
        if (filename.empty())
                return "";
        return dir + delim + filename;
}

string File::get_ext()
{
        if (filename.empty())
                return "";
        string ext{filename};
        auto pos = ext.find_last_of('.');
        if (pos != std::string::npos)
                return ext.substr(pos + 1);
        return "";
}

string File::get_filename_without_path()
{
        return filename;
}

string File::get_filename_without_path(const string &filename)
{
        if (filename.empty())
                return "";
        auto pos = find_last_delimiter(filename);
        if (pos != std::string::npos)
                return filename.substr(pos + 1);
        return filename;
}

string File::get_path()
{
        return dir;
}

string File::get_path(const string &filename)
{
        if (filename.empty())
                return ".";
        auto pos = find_last_delimiter(filename);
        if (pos != std::string::npos)
                return filename.substr(0, pos);
        return ".";
}

strvec File::get_file_list()
{
#ifdef unix
        DIR *dp;
        struct dirent *p;

        if (!(dp = opendir(dir.c_str()))) {
                fprintf(stderr, "[error] couldn't get file list in %s\n",
                                dir.c_str());
                return file_list;
        }

        while ((p = readdir(dp))) {
                // ignore the hidden files
                if ('.' == p->d_name[0])
                        continue;
                file_list.push_back(p->d_name);
        }

        closedir(dp);
#else
        WIN32_FIND_DATA ffd;
        HANDLE h_find = INVALID_HANDLE_VALUE;
        DWORD error = 0;

        h_find = FindFirstFile((dir + delim + "*").c_str(), &ffd);
        if (h_find == INVALID_HANDLE_VALUE) {
                fprintf(stderr, "[error] couldn't get file list in %s\n",
                                dir.c_str());
                return file_list;
        }

        do {
                // ignore the hidden files
                if (ffd.cFileName[0] == '.')
                        continue;
                file_list.push_back(ffd.cFileName);
        } while (FindNextFile(h_find, &ffd));

        error = GetLastError();
        if (error != ERROR_NO_MORE_FILES)
                fprintf(stderr, "[error] find first file error in %s\n",
                                dir.c_str());

        FindClose(h_find);
#endif

        std::sort(file_list.begin(), file_list.end());
        return file_list;
}

void File::cd(const std::string &dirname)
{
        if (chdir(dirname.c_str())) {
                fprintf(stderr, "[error] couldn't change current directory to %s\n", dirname.c_str());
                return;
        }
        close();
        open(".");
}
