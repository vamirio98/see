/*
 * main.cpp -
 *
 * Created by Haoyuan Li on 2021/07/14
 * Last Modified: 2021/07/23 22:56:23
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

        bool run = true;
	while (run) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
                        switch (e.type) {
                        case SDL_QUIT:
                                run = false;
                                break;
                        case SDL_KEYUP:
                                if (e.key.keysym.sym == SDLK_ESCAPE) {
                                        run = false;
                                        break;
                                }
                                if (e.key.keysym.sym == SDLK_LEFT)
                                        file.move_to_prev_file();
                                if (e.key.keysym.sym == SDLK_RIGHT)
                                        file.move_to_next_file();
                                engnie->load_texture(file.get_full_filename());
                                engnie->fit_window();
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
        file.close();
        engnie->free();
}
