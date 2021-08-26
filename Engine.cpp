/**
 * Engine.cpp - the Engine class
 *
 * Created by Haoyuan Li on 2021/07/17
 * Last Modified: 2021/08/26 11:38:31
 */

#include "Engine.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

using std::string;

const string init_title{"See"};
const string logfile{"./see.log"};

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::init()
{
        if (!log_.init(logfile)) {
                fprintf(stderr, "[Error] couldn't open log file %s\n",
                                logfile.c_str());
                exit(-1);
        }
        if (SDL_Init(SDL_INIT_VIDEO)) {
                log_.fatal("initialize failed\n");
                exit(-1);
        }
        create_window();
        if (!win) {
                log_.fatal("couldn't create window\n");
                exit(-1);
        }
        set_window_title(init_title);
        create_renderer();
        if (!renderer) {
                log_.fatal("couldn't create renderer\n");
                exit(-1);
        }
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        log_.info("initialize seccessfully\n");
}

void Engine::free()
{
        SDL_DestroyTexture(tex);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        log_.info("exit seccessfully\n");
}

void Engine::create_window()
{
        win = SDL_CreateWindow("",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        init_w, init_h,
                        SDL_WINDOW_RESIZABLE);
}

void Engine::create_renderer()
{
        renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}

void Engine::set_window_title(const string &name)
{
        SDL_SetWindowTitle(win, name.c_str());
}

void Engine::get_window_size(int *w, int *h)
{
        SDL_GetWindowSize(win, w, h);
}

void Engine::set_window_size(const int &w, const int &h)
{
        SDL_SetWindowSize(win, w, h);
}

void Engine::load_texture(const string &fname)
{
        tex = IMG_LoadTexture(renderer, fname.c_str());
}

void Engine::query_texture(See_texture *tex, int *w, int *h)
{
        SDL_QueryTexture(tex, nullptr, nullptr, w, h);
}

void Engine::render_clear()
{
        SDL_RenderClear(renderer);
}

void Engine::render_copy()
{
        SDL_RenderCopy(renderer, tex, nullptr, &rect);
}

void Engine::render_copy(See_texture *tex, See_rect *src, See_rect *dest)
{
        SDL_RenderCopy(renderer, tex, src, dest);
}

void Engine::render_present()
{
        SDL_RenderPresent(renderer);
}

void Engine::fit_window()
{
        get_window_size(&win_w, &win_h);
        int tex_w, tex_h;
        query_texture(tex, &tex_w, &tex_h);
        float tex_ar = static_cast<float>(tex_w) / tex_h;
        float win_ar = static_cast<float>(win_w) / win_h;

        if (tex_ar < win_ar) { // texture is taller
                rect.h = (win_h < tex_h) ? win_h : tex_h;
                rect.w = rect.h * tex_ar;
        } else {               // texture is wider
                rect.w = (win_w < tex_w) ? win_w : tex_w;
                rect.h = rect.w / tex_ar;
        }
        rect.x = (win_w - rect.w) / 2;
        rect.y = (win_h - rect.h) / 2;
}
