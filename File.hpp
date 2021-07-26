/**
 * File.hpp - the File class
 *
 * contains basic file operations
 *
 * Created by Haoyuan Li on 2021/07/21
 * Last Modified: 2021/07/26 15:27:35
 */

#ifndef FILE_HPP
#define FILE_HPP

#include <cstdio>
#include <string>
#include <vector>

#define IS_REG_FILE 0
#define IS_DIR 1
#define UNKNOWN 2

class File {
public:
        File();
        ~File() = default;
        File(const File &) = delete;
        File &operator=(const File &) = delete;

public:
        /**
         * \brief Check if the file or directory exists
         *
         * \param filename The filename
         *
         * \return true when the file exists and false when not
         */
        bool exists(const std::string &filename);

        /**
         * \brief Get the last delimiter in the path
         *
         * \return The index of the last delimiter, std::string::npos when not
         * found
         */
        std::string::size_type find_last_delimiter(const std::string &filename);

        /**
         * \brief Get the file type
         *
         * \param filename The filename
         *
         * \return IS_REG_FILE when it's a regular file, IS_DIR when it's a
         * directory, UNKNOWN when it can't be recognized
         */
        int get_type(const std::string &filename);

        /**
         * \brief move to the previous file in the current directory
         */
        void move_to_prev_file();

        /**
         * \brief Get the current filename
         *
         * \return The current filename
         */
        std::string get_curr_filename();

        /**
         * \brief move to the next file in the current directory
         */
        void move_to_next_file();

        /**
         * \brief Open a file and the directory it locates
         *
         * \param filename The filename
         *
         * \return 0 when succeeded, -1 when failed
         * \sa open_file()
         * \sa open_dir()
         * \sa close()
         */
        int open(const std::string &filename);

        /**
         * \brief Close this file and directory
         *
         * \sa open()
         */
        void close();

        /**
         * \brief Open a file by a specific mode, then open the directory it locates
         *
         * \param filename The filename
         * \param mode The specific mode, same as stdandard function fopen()
         *
         * \return 0 when succeeded and -1 when failed
         *
         * \sa open()
         * \sa close()
         */
        int open(const std::string &filename, const std::string &mode);

        /**
         * \brief get the full filename
         */
        std::string get_full_filename();

        /**
         * \brief Get the file extension
         *
         * \return the extension, "" if not found
         */
        std::string get_ext();

        /**
         * \brief Get filename without path
         *
         * \return The filename without path
         */
        std::string get_filename_without_path();

        /**
         * \brief Get filename without path
         *
         * \param filename The filename
         *
         * \return The filename without path
         */
        std::string get_filename_without_path(const std::string &filename);

        /**
         * \brief Get the current path
         *
         * \return The path
         */
        std::string get_path();

        /**
         * \brief Get the current path
         *
         * \param filename The filename
         *
         * \return The path
         */
        std::string get_path(const std::string &filename);

        /**
         * \brief Get the file list in the current directory
         *
         * \return The file list
         */
        std::vector<std::string> get_file_list();

        /**
         * \brief Change the current directory
         *
         * \param dirname The destination directory
         */
        void cd(const std::string &dirname);

private:
        std::string filename;   // the current filename
        FILE *fp;               // point to the current file

        std::string dir;        // the current directory
        // list of all unhidden files in the current directory
        std::vector<std::string> file_list;
        size_t index;           // the current file index in the file_list

private:
        /**
         * \brief Open a file by a specific mode
         *
         * \param filename The filename
         * \param mode The specific mode, same as stdandard function fopen()
         *
         * \return 0 when succeeded and -1 when failed
         *
         * \sa open()
         * \sa close()
         */
        int open_file(const std::string &filename, const std::string &mode);
};

#endif
