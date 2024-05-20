//
// Created by bzl on 19.05.2024.
//

#include "Game.h"
#include "sdl_smartptrs.h"

Game::Game(const char *windowTitle, const Point wSize, const bool vSync) {

    if( SDL_Init( SDL_INIT_EVERYTHING ) )
    {
        print( stderr, "SDL_Init failed: {}\n", SDL_GetError() );
        exit( 1 );
    }

    if( TTF_Init() )
    {
        print( stderr, "TTF_Init failed: {}\n", TTF_GetError() );
        exit( 2 );
    }

    constexpr IMG_InitFlags imgFlags = (IMG_InitFlags) (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
    if( IMG_Init( imgFlags ) != imgFlags )
    {
        print( stderr, "IMG_Init failed: {}\n", IMG_GetError() );
        exit( 3 );
    }

    constexpr MIX_InitFlags mixFlags = (MIX_InitFlags) (MIX_INIT_MP3 | MIX_INIT_OGG);
    if( Mix_Init( mixFlags ) != mixFlags )
    {
        print( stderr, "Mix_Init failed: {}\n", Mix_GetError() );
        exit( 4 );
    }

    if( Mix_OpenAudio( MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024 ) < 0 )
    {
        print( stderr, "Mix_OpenAudio failed: {}\n", Mix_GetError() );
        exit( 5 );
    }

    window = CreateSharedWindow(
            "BX Game",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            wSize.x, wSize.y,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
            );

    renderer = CreateSharedRenderer(
                window,
                -1,
                SDL_RENDERER_ACCELERATED | (vSync ? SDL_RENDERER_PRESENTVSYNC : 0)
            );

    windowSize = wSize;

    allStates.reserve( 10 );
    std::fill( allStates.begin(), allStates.end(), nullptr );
}

int Game::Run() {
    SDL_assert( nextStateIdx >= 0 );

    Duration deltaTDur       = Duration::zero();
    Duration deltaTDurNeeded = Duration::zero();   // How much time was really necessary
    TimePoint start;

    while( IsRunning() )
    {
        start = Clock::now();

        const float deltaT       = std::chrono::duration<float>( deltaTDur       ).count();
        const float deltaTNeeded = std::chrono::duration<float>( deltaTDurNeeded ).count();

        OutputPerformanceInfo( start, deltaTDurNeeded );

        ActivateNextState();

        // The difference to last frame is usually 16-17 at 60Hz, 10 at 100Hz, 8-9 at 120Hz, 6-*7* at 144Hz
        const u64 msSinceStart = SDL_GetTicks64();

        SDL_GetWindowSize( window.get(), &windowSize.x, &windowSize.y );

        // Main loop trinity
        {
            Input();

            Update( msSinceStart, deltaT );

            Render( msSinceStart, deltaTNeeded );
        }

        deltaTDurNeeded = Clock::now() - start;

        // With VSync this should not be needed and only Delay( 0 );
        if( currState->IsFPSLimited() )
        {
            using namespace std::chrono_literals;

            const Duration dur = std::max( Duration::zero(), 16ms - deltaTDurNeeded );
            const u32 ms = static_cast<u32>( std::chrono::duration_cast<std::chrono::milliseconds>( dur ).count() );
            SDL_Delay( ms );
            deltaTDur = Clock::now() - start;
        }
        else
        {
            deltaTDur = deltaTDurNeeded;
        }

        ++framesSinceStart;
    }
    return 0;
}

void Game::Render(const u64 msSinceStart, const float deltaTNeeded) {
    currState->Render(framesSinceStart, msSinceStart, deltaTNeeded);
}

void Game::Update(const u64 msSinceStart, const float deltaT) {
    currState->Update(framesSinceStart, msSinceStart, deltaT);
}

void Game::Input() {

}

Game::~Game()
{
    allStates.clear();

    IMG_Quit();

    if( TTF_WasInit() )
        TTF_Quit();

    if( SDL_WasInit( 0 ) )
        SDL_Quit();
}

bool Game::HandleEvent(const Event &event) {
    return false;
}

// --------------------------------------------------------------------------------------------

float Game::AverageMSecPerFrame() const {
    const u32 passedFrames = framesSinceStart - lastPerfInfoFrame + 1;
    return std::chrono::duration<float>( accumulatedNeeded / passedFrames ).count() * 1000.0f;
}

void Game::ResetPerformanceInfo(const TimePoint current) {
    lastPerfInfoFrame = framesSinceStart;
    lastPerfInfoTime = current;
    accumulatedNeeded = Duration::zero();
}

void Game::OutputPerformanceInfo(const TimePoint current, const Duration needed) {
    using namespace std::chrono_literals;

    accumulatedNeeded += needed;

    const Duration passedTime = current - lastPerfInfoTime;

    switch( perfDrawMode )
    {
        case PerformanceDrawMode::Title:
            if( passedTime > 250ms )
            {
                const std::string avgms = format( "{}ms", AverageMSecPerFrame() );
                SDL_SetWindowTitle( window.get(), avgms.c_str() );
                ResetPerformanceInfo( current );
            }
            break;

        case PerformanceDrawMode::OStream:
            if( passedTime > 1000ms )
            {
                print( "{}ms", AverageMSecPerFrame() );
                ResetPerformanceInfo( current );
            }
            break;

        case PerformanceDrawMode::None:
        default: break;
    }
}

void Game::ActivateNextState() {
    if( nextStateIdx != currentStateIdx
        && nextStateIdx != -1 )
    {
        // Load the state or die
        if( nextStateIdx >= (int)allStates.size() || allStates[nextStateIdx] == nullptr )
        {
            print( stderr, "Activated out of range or nullptr state with the index: {}\n", nextStateIdx );
            exit( 11 );
        }
        else
        {
            if( currState != nullptr )
                currState->UnInit();

            currentStateIdx = nextStateIdx;
            currState = allStates[currentStateIdx];
            currState->Init();
        }
    }
}
