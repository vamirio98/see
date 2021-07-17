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

	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *img = NULL;

	string fname{argv[1]};
	// remove directory if present
	const auto last_slash_idx = fname.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
		fname.erase(0, last_slash_idx + 1);

	win = SDL_CreateWindow(fname.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			640, 480,
			0);
	if (win == NULL)
		SDL_Log("Unable to create a window: %s", SDL_GetError());

	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		SDL_Log("Unable to create a renderer: %s", SDL_GetError());

	img = IMG_LoadTexture(renderer, argv[1]);
	int w, h;
	SDL_QueryTexture(img, NULL, NULL, &w, &h);
	SDL_SetWindowSize(win, w, h);
	SDL_SetWindowPosition(win,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_Rect texr;
	texr.x = 0;
	texr.y = 0;
	texr.w = w;
	texr.h = h;

	while (1) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if ((e.type == SDL_QUIT) || (e.type == SDL_KEYUP &&
					e.key.keysym.sym == SDLK_ESCAPE))
				break;
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, img, NULL, &texr);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(img);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);

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
