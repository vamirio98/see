/**
 * File.cpp - the File class
 *
 * contains basic file operations
 *
 * Created by Haoyuan Li on 2021/07/21
 * Last Modified: 2021/07/23 19:45:36
 */

#include "File.hpp"

using string = std::string;
using strvec = std::vector<std::string>;

File::File()
{
}

/**
 * \brief Open a file by a specific mode
 * \param filename The filename
 * \param mode The specific mode, same as stdandard function fopen()
 * \return 0 when succeeded and -1 when failed
 * \sa open()
 * \sa close()
 */
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

/**
 * \brief Open a directory, then get all files in it
 * \param dirname The directory name
 * \return 0 when secceeded and -1 when failed
 * \sa open()
 * \sa close()
 */
int File::open_dir(const string &dirname)
{
        if (!(dp = opendir(dirname.c_str()))) {
                fprintf(stderr, "[error] couldn't open directory %s\n",
                                dirname.c_str());
                return -1;
        }
        path = dirname;
        index = 0;
        return 0;
}

/**
 * \brief Check if the file exists
 * \param filename The filename
 * \return true when the file exists and false when not
 */
bool File::exists(const string &filename)
{
        struct stat st;
        return !(stat(filename.c_str(), &st));
}

/**
 * \brief Get the last delimiter in the path
 * \return The index of the last delimiter, std::string::npos when not found
 */
string::size_type File::find_last_delimiter(const string &filename)
{
        return filename.find_last_of("/\\");
}

/**
 * \brief Get the file type
 * \param filename The filename
 * \return IS_REG_FILE when it's a regular file, IS_DIR when it's a directory,
 * UNKNOWN when it can't be recognized
 */
int File::get_type(const string &filename)
{
        struct stat st;
        int type;
        lstat(filename.c_str(), &st);
        if (S_ISREG(st.st_mode))
                type = IS_REG_FILE;
        else if (S_ISDIR(st.st_mode))
                type = IS_DIR;
        else
                type = UNKNOWN;
        return type;
}

/**
 * \brief move to the previous file in the current directory
 */
void File::move_to_prev_file()
{
        index = (index == 0) ? index : index - 1;
        open_file(file_list[index], "r");
}

/**
 * \brief Get the current filename
 * \return The current filename
 */
string File::get_curr_file()
{
        return file_list[index];
}

/**
 * \brief move to the next file in the current directory
 */
void File::move_to_next_file()
{
        index = (index == file_list.size() - 1 ? index : index + 1);
        open_file(file_list[index], "r");
}

/**
 * \brief Open a file and the directory it locates
 * \param filename The filename
 * \return 0 when succeeded, -1 when failed
 * \sa open_file()
 * \sa open_dir()
 * \sa close()
 */
int File::open(const string &filename)
{
        int type = get_type(filename);
        if (type == IS_REG_FILE) {
                open_file(filename, "r");
                open_dir(get_path(filename));
                get_file_list();
        } else if (type == IS_DIR) {
                open_dir(filename);
                get_file_list();
                open_file(file_list[0], "r");
        } else {
                fprintf(stderr, "[error] unknown type: %s\n",
                                filename.c_str());
                return -1;
        }
        return 0;
}

/**
 * \brief Close this file and directory
 * \sa open()
 */
void File::close()
{
        fclose(fp);
        closedir(dp);
}

/**
 * \brief Open a file by a specific mode, then open the directory it locates
 * \param filename The filename
 * \param mode The specific mode, same as stdandard function fopen()
 * \return 0 when succeeded and -1 when failed
 * \sa open()
 * \sa close()
 */
int File::open(const string &filename, const string &mode)
{
        if(open_file(filename, mode) || open_dir(get_path(filename))) {
                fprintf(stderr, "[error] couldn't open %s\n",
                                filename.c_str());
                return -1;
        }
        get_file_list();
        return 0;
}

/**
 * \brief get the full filename
 */
string File::get_full_filename()
{
        return path + "/" + filename;
}

/**
 * \brief Get the file extension
 * \return the extension, "" if not found
 */
string File::get_ext()
{
        string ext{filename};
        auto pos = ext.find_last_of('.');
        if (pos != std::string::npos)
                return ext.substr(pos + 1);
        return "";
}

/**
 * \brief Get filename without path
 * \return The filename without path
 */
string File::get_filename_without_path()
{
        return filename;
}

/**
 * \brief Get filename without path
 * \param filename The filename
 * \return The filename without path
 */
string File::get_filename_without_path(const string &filename)
{
        auto pos = find_last_delimiter(filename);
        if (pos != std::string::npos)
                return filename.substr(pos + 1);
        return filename;
}

/**
 * \brief Get the current path
 * \return The path
 */
string File::get_path()
{
        return path;
}

/**
 * \brief Get the current path
 * \param filename The filename
 * \return The path
 */
string File::get_path(const string &filename)
{
        auto pos = find_last_delimiter(filename);
        if (pos != std::string::npos)
                return filename.substr(0, pos);
        return ".";
}

/**
 * \brief Get the file list in the current directory
 * \return The file list
 */
strvec File::get_file_list()
{
        DIR *tmp = dp;
        struct dirent *p;

        while ((p = readdir(tmp))) {
                if (string{"."} == p->d_name || string{".."} == p->d_name)
                        continue;
                file_list.push_back(p->d_name);
        }
        std::sort(file_list.begin(), file_list.end());
        return file_list;
}

/**
 * \brief Change the current directory
 * \param dirname The destination directory
 */
void File::cd(const std::string &dirname)
{
        if (chdir(dirname.c_str())) {
                fprintf(stderr, "[error] couldn't change current directory to %s\n", dirname.c_str());
                return;
        }
        close();
        open(dirname);
}
