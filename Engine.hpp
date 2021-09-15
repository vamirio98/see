/**
 * Engine.hpp - the Engine class
 *
 * encapsulate part of the SDL2 function
 *
 * Created by Haoyuan Li on 2021/07/17
 * Last Modified: 2021/09/15 10:40:10
 */

#ifndef ENGINE_HPP
#define ENGINE_HPP


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Logger.hpp"
#include "File.hpp"

using See_window = SDL_Window;
using See_renderer = SDL_Renderer;
using See_texture = SDL_Texture;
using See_rect = SDL_Rect;

/**
 * @define see_window_pos
 */
#define SEE_WINDOWPOS_CENTERED SDL_WINDOWPOS_CENTERED
#define SEE_WINDOWPOS_UNDEFINED SDL_WINDOWPOS_UNDEFINED

/**
 * @define see_window_flags
 */
#define SEE_WINDOW_SHOWN SDL_WINDOW_SHOWN
#define SEE_WINDOW_RESIZABLE SDL_WINDOW_RESIZABLE


class Engine {
private:
        See_window *win_;
        See_renderer *renderer_;
        See_texture *tex_;
        See_rect rect_;

        const std::string init_title_{"See"};

        const int init_w_{1024};
        const int init_h_{640};
        int win_w_, win_h_;

        Logger log_;
        const std::string logfile_{"./see.log"};

private:
        Engine();
        ~Engine();

public:
        /**
         * @brief Get the Engine instance
         *
         * @return The pointer to the Engine instance
         */
        static Engine *get_instance();

        Engine(const Engine &) = delete;
        Engine &operator=(const Engine &) = delete;

        /**
         * @brief Initialize the Engine
         *
         * @return True if initialize successfully, false otherwise
         */
        bool init();

        /**
         * @brief Free the Engine instance
         */
        void free_instance();

        /**
         * @brief Create a window with the specified position, dimensions
         *        and flags
         *
         * @param title The title of the window
         * @param x The x position of the window, it can be one of follows:
         *          SEE_WINDOWPOS_CENTERED, SEE_WINDOWPOS_UNDEFINED
         * @param y The y position of the window, it can be one of follows:
         *          SEE_WINDOWPOS_CENTERED, SEE_WINDOWPOS_UNDEFINED
         * @param w The width of the window in pixels
         * @param h The height of the window in pixels
         * @param flags 0, or one or more @define see_window_flags OR'd
         *              together
         *
         * @return The point to a See_window object or nullptr on failure
         */
        See_window *create_window(const std::string &title, const int &x,
                        const int &y, const int &w,
                        const int &h, const uint32_t &flags);
        void create_renderer();

        /**
         * @brief Set the title of the window
         *
         * @param title The title
         */
        void set_window_title(const std::string &title);

        /**
         * @brief Get the size of the window
         *
         * @param w A pointer to the width of the window in pixels
         * @param h A pointer to the height of the window in pixels
         */
        void get_window_size(int *w, int *h);

        /**
         * @brief Set the size of the window
         *
         * @param w The width of the window in pixels
         * @param h The height of the window in pixels
         */
        void set_window_size(const unsigned &w, const unsigned &h);

        /**
         * @brief Load an image diectly into a render texture
         *
         * @param pathname The file pathname
         *
         * @return A pointer to a See_texture object or nullptr on failure
         */
        See_texture *load_texture(const std::string &pathname);

        /**
         * @brief Query the attributes of a texture
         *
         * @param tex The pointer to the texture to be queried
         * @param w A pointer to the width of the texture in pixels
         * @param h A pointer to the height of the texture in pixels
         *
         * @return True on success, false otherwise
         */
        bool query_texture(See_texture *tex, int *w, int *h);

        /**
         * @brief Clear the current redering target
         *
         * @return True on success, false otherwise
         */
        bool render_clear();

        /**
         * @brief Copy the texture to the current rendering target
         *
         * @return True on success, false otherwise
         */
        bool render_copy();

        /**
         * @brief Copy a portion of the texture to the current redering target
         *
         * @param tex The pointer to the redering context
         * @param src The source See_rect structure or nullptr for the entire
         *            texture
         * @param dest The destinaion See_rect structure or nullptr for the
         *             entire redering target, the texture will be stretched
         *             to fill the given rectangle
         *
         * @return True on success, false otherwise
         */
        bool render_copy(See_texture *tex, See_rect *src, See_rect *dest);

        /**
         * @brief Update the screen
         */
        void render_present();

        /**
         * @brief Fit the texture with the window size
         */
        void fit_window_size();
};

inline See_window *Engine::create_window(const std::string &title,
                const int &x, const int &y, const int &w,
                const int &h, const uint32_t &flags)
{
        win_ = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
        return win_;
}

inline void Engine::create_renderer()
{
        renderer_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED);
}

inline void Engine::set_window_title(const std::string &title)
{
        SDL_SetWindowTitle(win_, title.c_str());
}

inline void Engine::get_window_size(int *w, int *h)
{
        SDL_GetWindowSize(win_, w, h);
}

inline void Engine::set_window_size(const unsigned &w, const unsigned &h)
{
        SDL_SetWindowSize(win_, static_cast<int>(w), static_cast<int>(h));
}

inline See_texture *Engine::load_texture(const std::string &pathname)
{
        tex_ = IMG_LoadTexture(renderer_, pathname.c_str());
        return tex_;
}

inline bool Engine::query_texture(See_texture *tex, int *w, int *h)
{
        return SDL_QueryTexture(tex, nullptr, nullptr, w, h) == 0;
}

inline bool Engine::render_clear()
{
        return SDL_RenderClear(renderer_) == 0;
}

inline bool Engine::render_copy()
{
        return SDL_RenderCopy(renderer_, tex_, nullptr, &rect_) == 0;
}

inline bool Engine::render_copy(See_texture *tex, See_rect *src, See_rect *dest)
{
        return SDL_RenderCopy(renderer_, tex, src, dest) == 0;
}

inline void Engine::render_present()
{
        SDL_RenderPresent(renderer_);
}

#endif
