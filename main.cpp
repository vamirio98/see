/*
 * main.cpp -
 *
 * Created by Haoyuan Li on 2021/07/14
 * Last Modified: 2021/07/22 00:08:53
 */

#include <string>
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include "Engine.hpp"
#include "File.hpp"

using std::string;

int init();
void quit();

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "%s\n", "Usage: see <filename>");
		return 1;
	}

        auto engnie = Engine::get_instance();
        engnie->init();

        File file;
        file.open(argv[1], "r");
        engnie->set_window_title(file.get_filename_without_path());
        engnie->load_texture(file.get_full_filename());
        engnie->fit_window();
        file.close();

        bool run = true;
	while (run) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
                        switch (e.type) {
                        case SDL_QUIT:
                                run = false;
                                break;
                        case SDL_KEYUP:
                                if (e.key.keysym.sym == SDLK_ESCAPE)
                                        run = false;
                                break;
                        case SDL_WINDOWEVENT:
                                switch (e.window.event) {
                                case SDL_WINDOWEVENT_RESIZED:
                                        engnie->fit_window();
                                }
                        default:
                                break;
                        }
		}
                engnie->render_clear();
                engnie->render_copy();
                engnie->render_present();
	}
        engnie->free();
}
