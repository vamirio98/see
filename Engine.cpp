/**
 * Engine.cpp - the Engine class
 *
 * encapsulate part of the SDL2 function
 *
 * Created by Haoyuan Li on 2021/07/17
 * Last Modified: 2021/08/28 10:26:51
 */

#include "Engine.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

using std::string;

Engine::Engine()
{
}

Engine::~Engine()
{
}

Engine *Engine::get_instance()
{
        static Engine e;
        return &e;
}

bool Engine::init()
{
        bool state{false};
        do {
                if (!log_.init(logfile_)) {
                        fprintf(stderr, "[Error] couldn't open log file %s\n",
                                        logfile_.c_str());
                        break;
                }
                if (SDL_Init(SDL_INIT_VIDEO)) {
                        log_.fatal("initialize failed\n");
                        break;
                }
                if (!create_window("",
                                SEE_WINDOWPOS_CENTERED,
                                SEE_WINDOWPOS_CENTERED,
                                init_w_, init_h_,
                                SEE_WINDOW_SHOWN | SEE_WINDOW_RESIZABLE)) {
                        log_.fatal("couldn't create window\n");
                        break;
                }
                set_window_title(init_title_);
                create_renderer();
                if (!renderer_) {
                        log_.fatal("couldn't create renderer\n");
                        break;
                }
                SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
                log_.info("initialize seccessfully\n");
                state = true;
        } while (0);
        return state;
}

void Engine::free_instance()
{
        SDL_DestroyTexture(tex_);
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(win_);
        SDL_Quit();
        log_.info("exit seccessfully\n");
}

void Engine::fit_window_size()
{
        get_window_size(&win_w_, &win_h_);
        int tex_w, tex_h;
        query_texture(tex_, &tex_w, &tex_h);
        float tex_ar = static_cast<float>(tex_w) / tex_h;
        float win_ar = static_cast<float>(win_w_) / win_h_;

        if (tex_ar < win_ar) { // texture is taller
                rect_.h = (win_h_ < tex_h) ? win_h_ : tex_h;
                rect_.w = rect_.h * tex_ar;
        } else {               // texture is wider
                rect_.w = (win_w_ < tex_w) ? win_w_ : tex_w;
                rect_.h = rect_.w / tex_ar;
        }
        rect_.x = (win_w_ - rect_.w) / 2;
        rect_.y = (win_h_ - rect_.h) / 2;
}
