/*
 * main.cpp -
 *
 * Created by Haoyuan Li on 2021/07/14
 * Last Modified: 2021/09/15 10:43:09
 */

#include "Engine.hpp"
#include "File.hpp"
#include "Timer.hpp"

#include "see_config.h"

#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

using std::string;

constexpr uint32_t fps = 25;
constexpr uint32_t ticks_per_frame = 1000 / fps;
const std::vector<string> support_format{"jpg", "jpeg", "png"};

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "%s\n", "Usage: see <filename>");
		return 1;
	}
        printf("See Version %d.%d\n", SEE_VERSION_MAJOR, SEE_VERSION_MINOR);

        auto engnie = Engine::get_instance();
        engnie->init();

        File file;
        File dir;
        file.bind(argv[1]);
        if (file.is_directory())
                dir.bind(argv[1]);
        else
                dir.bind(file.get_parent() == "" ? "." : file.get_parent());
        std::vector<string> filelist = dir.list();
        auto iter = filelist.begin();
        while (iter != filelist.end()) {
                if (std::find(support_format.begin(), support_format.end(),
                                        File::get_extension(*iter)) ==
                                        support_format.end())
                        iter = filelist.erase(iter);
                else
                        ++iter;
        }
        std::sort(filelist.begin(), filelist.end());
        if (file.is_directory()) {
                file.unbind();
                file.bind(filelist[0]);
        }
        decltype(filelist.size()) index = std::find(filelist.begin(),
                        filelist.end(), file.get_name()) - filelist.begin();

        engnie->set_window_title(file.get_name());
        engnie->load_texture(dir.get_path() + dir.separator + file.get_name());
        engnie->fit_window_size();

        bool run = true;
	bool change = true;
        SDL_Event e;
        Timer cap_fps;
	while (run) {
                cap_fps.start();
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
                                if (e.key.keysym.sym == SDLK_LEFT) {
                                        if (index != 0) {
                                                file.unbind();
                                                file.bind(dir.get_absolute_path() + file.separator + filelist[--index]);
                                        }
                                }
                                if (e.key.keysym.sym == SDLK_RIGHT)
                                        if (index != filelist.size() - 1) {
                                                file.unbind();
                                                file.bind(dir.get_absolute_path() + file.separator + filelist[++index]);
                                        }
                                engnie->load_texture(file.get_absolute_path());
                                engnie->set_window_title(file.get_name());
                                engnie->fit_window_size();
				change = true;
                                break;
                        case SDL_WINDOWEVENT:
                                switch (e.window.event) {
                                case SDL_WINDOWEVENT_RESIZED:
                                        engnie->fit_window_size();
					change = true;
					break;
				default:
					break;
                                }
				break;
                        default:
                                break;
                        }
			if (change) {
				engnie->render_clear();
				engnie->render_copy();
				engnie->render_present();
				change = false;
			}
		}
                auto ticks = cap_fps.get_ticks();
                if (ticks < ticks_per_frame)
                        SDL_Delay(ticks_per_frame - ticks);
	}
        engnie->free_instance();
        return 0;
}
