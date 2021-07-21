/**
 * File.cpp - the File class
 *
 * contains basic file operations
 *
 * Created by Haoyuan Li on 2021/07/21
 * Last Modified: 2021/07/22 00:06:22
 */

#include "File.hpp"

using string = std::string;

File::File()
{
}

string::size_type File::find_last_delimiter()
{
        return fname.find_last_of("\\/");
}

int File::open(const string &filename, const string &mode)
{
        if (!(fp = fopen(filename.c_str(), mode.c_str())))
                return -1;
        fname = filename;
        return 0;
}

void File::close()
{
        fclose(fp);
        fname = "";
}

string File::get_full_filename()
{
        return fname;
}

string File::get_ext()
{
        string ext{fname};
        auto pos_delim = find_last_delimiter();
        auto pos = ext.find_last_of('.');
        if (pos != std::string::npos &&
                        (pos_delim < pos ||
                         pos_delim == std::string::npos))
                return ext.substr(pos + 1);
        return "";
}

string File::get_filename_without_path()
{
        auto pos = find_last_delimiter();
        if (pos != std::string::npos)
                return fname.substr(pos + 1);
        return fname;
}

string File::get_path()
{
        auto pos = find_last_delimiter();
        if (pos != std::string::npos)
                return fname.substr(0, pos);
        return "";
}
