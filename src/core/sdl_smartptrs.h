//
// Created by bzl on 19.05.2024.
//

#ifndef SDL_BZGAME_SDL_SMARTPTRS_H
#define SDL_BZGAME_SDL_SMARTPTRS_H

#include "global.h"

struct bzDeleter{
    void operator()(Window *p)    const { SDL_DestroyWindow(p);    }
    void operator()(Renderer *p)  const { SDL_DestroyRenderer(p);  }
    void operator()(Texture *p)   const { SDL_DestroyTexture(p);    }

};

std::shared_ptr<Texture>
CreateSharedTexture(SDL_Renderer *renderer, const char * const file)
{
    Texture *texture = IMG_LoadTexture(renderer, file);
    if (!texture) throw std::runtime_error("ERROR: on call LoadTexture() \n");// handle error or return nullptr
    return {texture, bzDeleter()};
}

std::shared_ptr<Renderer>
CreateSharedRenderer(Window* window, int index, Uint32 flags)
{
    Renderer* renderer = SDL_CreateRenderer(window, index, flags);
    if(renderer == nullptr) throw std::runtime_error("ERROR: Could not create renderer.\n");
    return {renderer, bzDeleter()};
}

std::shared_ptr<Window>
CreateSharedWindow(const char* title, int x, int y, int w, int h, Uint32 flags)
{
    Window* window = SDL_CreateWindow(title, x, y, w, h, flags);
    if(!window) throw std::runtime_error("ERROR: Could not create window.\n");
    return {window, bzDeleter()};
}

#endif //SDL_BZGAME_SDL_SMARTPTRS_H
