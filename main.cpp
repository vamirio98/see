/*
 * main.cpp -
 *
 * Created by Haoyuan Li on 2021/07/14
 * Last Modified: 2021/07/14 23:41:54
 */

#include <string>
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include "Engine.hpp"


using std::string;

int init();
void quit();

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "%s\n", "Usage: see <filename>");
		return 1;
	}
	if (init() != 0)
		return 1;


	string fname{argv[1]};
	// remove directory if present
	const auto last_slash_idx = fname.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
		fname.erase(0, last_slash_idx + 1);

        Engine win(fname.c_str(), argv[1]);

        win.fit_window();

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
                                        win.fit_window();
                                }
                        default:
                                break;
                        }
		}
                win.display();
	}

	quit();
}


/*
 * init - inintialize
 * returns 0 on success or the error code on failure
 */
int init()
{
	int err = 0;
	if ((errno = SDL_Init(SDL_INIT_AUDIO)) != 0)
		SDL_Log("Unable to inintialize SDL: %s", SDL_GetError());
	return err;
}


/*
 * quit
 */
void quit()
{
	SDL_Quit();
}
