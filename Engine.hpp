/**
 * Engine.hpp - the Engine class
 *
 * depend on SDL2
 *
 * Created by Haoyuan Li on 2021/07/17
 * Last Modified: 2021/07/26 15:31:19
 */

#ifndef ENGINE_HPP
#define ENGINE_HPP


#include <SDL2/SDL.h>
#include <string>

#include "Logger.hpp"

using See_window = SDL_Window;
using See_renderer = SDL_Renderer;
using See_texture = SDL_Texture;
using See_rect = SDL_Rect;

class Engine {
public:
        static Engine *get_instance()
        {
                static Engine e;
                return &e;
        }
        Engine(const Engine &) = delete;
        Engine &operator=(const Engine &) = delete;

private:
        std::string title;
        See_window *win;
        See_renderer *renderer;
        See_texture *tex;
        See_rect rect;

        const int init_w = 1024;
        const int init_h = 640;
        int win_w, win_h;

        Logger *log;

private:
        Engine();
        ~Engine();

public:
        void init();
        void free();
        void create_window();
        void create_renderer();
        void set_window_title(const std::string &name);
        void get_window_size(int *w, int *h);
        void set_window_size(const int &w, const int &h);
        void load_texture(const std::string &fname);
        void query_texture(See_texture *tex, int *w, int *h);
        void render_clear();
        void render_copy();
        void render_copy(See_texture *tex, See_rect *src, See_rect *dest);
        void render_present();
        void fit_window();
};

#endif
