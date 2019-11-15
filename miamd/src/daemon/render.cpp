#include <cstring>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <thread>
#include "global.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpv/client.h>
#include <mpv/render_gl.h>
#include <unistd.h>
#include <GL/glx.h>
#include <math.h> 
#include <iostream>
#include <vector>
#include <chrono>
std::vector<std::string> musics[2];
static void *get_proc_address_mpv(void *fn_ctx, const char *name)
{
    return reinterpret_cast<void*>(glXGetProcAddressARB(reinterpret_cast<const unsigned char*>(name)));
}

int handler(Display * d, XErrorEvent * e)
{
    printf("Error code: %d\n",e->error_code);
    return 0;
}
void Render(sf::Window &window, _GAME &GAME){
	if(GAME.backend=="mysql"){
        mysql_thread_init();
    }
	mpv_handle *mpv = GAME.mpv;
	mpv_render_context *mpv_gl;
	mpv_opengl_init_params iparams{.get_proc_address = get_proc_address_mpv,};
        mpv_render_param params[]{
               {MPV_RENDER_PARAM_API_TYPE, const_cast<char *>(MPV_RENDER_API_TYPE_OPENGL)},
               {MPV_RENDER_PARAM_OPENGL_INIT_PARAMS, &iparams},
               {MPV_RENDER_PARAM_INVALID}
        };
	mpv_render_context_create(&mpv_gl,mpv,params);
	
	mpv_opengl_fbo mpfbo{.fbo = 0, .w = GAME.width, .h = GAME.height, .internal_format = 0};
	int flip_y{1};
	 mpv_render_param params2[] = {
            {MPV_RENDER_PARAM_OPENGL_FBO, &mpfbo},
            {MPV_RENDER_PARAM_FLIP_Y, &flip_y},
            {MPV_RENDER_PARAM_INVALID, nullptr}
	};
	//unsigned int W=window.getSize().x;
	//unsigned int H=window.getSize().y;
	unsigned int start;
	unsigned int end;
	sf::Event event;
	GAME.video_ready=true;
	while(GAME.Active){
        while (GAME.window->pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                GAME.window->close();
                GAME.Active = false;
            }
        }
		start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	//	W=window.getSize().x;
	//	H=window.getSize().y;
	//	if(mpfbo.w!=(int)W || mpfbo.h!=(int)H){
	//	mpfbo.w=W;
	//	mpfbo.h=H;
	//	}
		mpv_render_context_render(mpv_gl, params2);
		window.display();
		end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		end=end-start;
		if(end<16){
		std::this_thread::sleep_for(std::chrono::milliseconds(16-end));
		}
	}
}
