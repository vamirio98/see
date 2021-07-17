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

#define INIT_WIN_W 640
#define INIT_WIN_H 480

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
			INIT_WIN_W, INIT_WIN_H,
			SDL_WINDOW_RESIZABLE);
	if (win == NULL)
		SDL_Log("Unable to create a window: %s", SDL_GetError());

	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		SDL_Log("Unable to create a renderer: %s", SDL_GetError());

        int win_w, win_h;
	int img_w, img_h;
        SDL_GetWindowSize(win, &win_w, &win_h);
	img = IMG_LoadTexture(renderer, argv[1]);
	SDL_QueryTexture(img, NULL, NULL, &img_w, &img_h);

	float img_ar = (float)img_w / img_h;                   // image's aspect ratio
	float win_ar = (float)INIT_WIN_W / INIT_WIN_H; // window's aspect ratio
	SDL_Rect texr;
        if (img_ar < win_ar) {
                texr.h = win_h;
                texr.w = texr.h * img_ar;
        } else {
                texr.w = win_w;
                texr.h = texr.w / img_ar;
        }
	texr.x = (win_w - texr.w) / 2;
	texr.y = (win_h - texr.h) / 2;

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
                                        win_w = e.window.data1;
                                        win_h = e.window.data2;
                                        img_ar = (float)img_w / img_h;
                                        win_ar = (float)win_w / win_h;
                                        if (img_ar < win_ar) {
                                                texr.h = win_h;
                                                texr.w = texr.h * img_ar;
                                        } else {
                                                texr.w = win_w;
                                                texr.h = texr.w / img_ar;
                                        }
                                        texr.x = (win_w - texr.w) / 2;
                                        texr.y = (win_h - texr.h) / 2;
                                }
                        default:
                                break;
                        }
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
