/**
 * Engine.hpp - the Engine class
 *
 * Created by Haoyuan Li on 2021/07/17
 * Last Modified: 2021/07/17 23:52:08
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP


#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <string>

using std::string;
using See_window = SDL_Window;
using See_renderer = SDL_Renderer;
using See_texture = SDL_Texture;
using See_rect = SDL_Rect;

struct See_content {
        See_texture *texture;
        See_rect area;
};

class Engine {
private:
        string title{""};
        int w{640};
        int h{480};
        See_window *win;
        See_renderer *renderer;
        See_content content;

public:
        Engine(string title, string fname);
        ~Engine();
        void display();
        void fit_window();
};

#endif
