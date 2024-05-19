//
// Created by bzl on 19.05.2024.
//
#ifndef SDL_BZGAME_GLOBAL_H
#define SDL_BZGAME_GLOBAL_H

#include <cmath>
#include <cstdarg>
#include <cstddef>
#include <cassert>
#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include <core/sdl_smartptrs.h>

#include <fmt/core.h>   // https://fmt.dev/latest/index.html
#include <nfd.h>        // https://github.com/mlabbe/nativefiledialog/blob/master/README.md

// Usually ImGui is only included during development, but defining IMGUI_ALSO_IN_RELEASE can make it available everywhere
#if defined( _DEBUG ) || (defined( IMGUI_ALSO_IN_RELEASE ) && defined( RELEASE ))
#include <imgui.h>      // https://github.com/ocornut/imgui/blob/bb224c8aa1de1992c6ea3483df56fb04d6d1b5b6/examples/example_sdl2_sdlrenderer/main.cpp
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#endif

#include <SDL_stdinc.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif


using i8    = std::int8_t;
using i16   = std::int16_t;
using i32   = std::int32_t;
using i64   = std::int64_t;
using u8    = std::uint8_t;
using u16   = std::uint16_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using uint  = unsigned int;

using isize = std::ptrdiff_t;
using usize = std::size_t;

using string      = std::string;
using string_view = std::string_view;
using String      = std::string;
using StringView  = std::string_view;

using Color       = SDL_Color;
using Event       = SDL_Event;
using Point       = SDL_Point;
using FPoint      = SDL_FPoint;
using Keysym      = SDL_Keysym;
using Keymod      = SDL_Keymod;
using Rect        = SDL_Rect;
using FRect       = SDL_FRect;
using Surface     = SDL_Surface;
using Texture     = SDL_Texture;
using Renderer    = SDL_Renderer;
using Window      = SDL_Window;
using Palette     = SDL_Palette;
using PixelFormat = SDL_PixelFormat;
using Font        = TTF_Font;
using Chunk       = Mix_Chunk;
//using Sound       = Mix_Chunk;
using Music       = Mix_Music;

template<class T, std::size_t Size> using Array  = std::array<T, Size>;
template<class T>                   using Vector = std::vector<T>;

using Clock     = std::chrono::high_resolution_clock;
using TimePoint = Clock::time_point;
using Duration  = Clock::duration;

using std::min;
using std::max;

using fmt::print, fmt::println, fmt::format;



#ifdef FINAL
#else
#define BasePath "../../"    //    out/build/${architecture}-${configuration}
// OR build/${configuration}-${compiler}/bin
#endif

#if defined( _DEBUG )
#define DebugOnly( ... ) __VA_ARGS__
#define IfDebug if constexpr( true )
#else
#define DebugOnly( ... )
#define IfDebug if constexpr( false )
#endif




#endif //SDL_BZGAME_GLOBAL_H
