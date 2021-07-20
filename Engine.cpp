/**
 * Engine.cpp - the Engine class
 *
 * Created by Haoyuan Li on 2021/07/17
 * Last Modified: 2021/07/17 23:36:53
 */

#include "Engine.hpp"

Engine::Engine(string title, string fname)
{
        this->title = title;
        win = SDL_CreateWindow(title.c_str(),
                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        w, h,
                        SDL_WINDOW_RESIZABLE);
        renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        content.texture = IMG_LoadTexture(renderer, fname.c_str());
        SDL_QueryTexture(content.texture, nullptr, nullptr,
                        &content.area.w, &content.area.h);
        content.area.x = 0;
        content.area.y = 0;
}

Engine::~Engine()
{
        SDL_DestroyTexture(content.texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
}

void Engine::display()
{
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, content.texture, NULL, &(content.area));
        SDL_RenderPresent(renderer);
}

void Engine::fit_window()
{
        SDL_GetWindowSize(win, &w, &h);
        int texr_w, texr_h;
        SDL_QueryTexture(content.texture, NULL, NULL, &texr_w, &texr_h);
        float texr_ar = (float)texr_w / texr_h;
        float win_ar = (float)w / h;
        if (texr_ar < win_ar) { // texture is taller
                content.area.h = (h < texr_h) ? h : texr_h;
                content.area.w = content.area.h * texr_ar;
        } else {                // texture is wider
                content.area.w = (w < texr_w) ? w : texr_w;
                content.area.h = content.area.w / texr_ar;
        }
        content.area.x = (w - content.area.w) / 2;
        content.area.y = (h - content.area.h) / 2;
}
