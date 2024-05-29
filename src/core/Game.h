//
// Created by bzl on 19.05.2024.
//

#pragma once

#include <core/global.h>


class GameState;

class Game {
protected:
    shared_ptr<Window>     window;
    shared_ptr<Renderer>   renderer;

    shared_ptr<GameState> currState = nullptr;
    Vector<shared_ptr<GameState>> allStates;

    u32 framesSinceStart = 0;
    Point windowSize;

    int currentStateIdx = -1;
    int nextStateIdx    = -1;
    bool isRunning        = true;


public:

    // CONSTRUCTORS
    // -----------------------------------------------------------------------------------
    explicit Game(
            const char * windowTitle    = "default",
            const Point  windowSize     = Point(1024, 720),
            const bool   vSync          = true
            );
    Game(              const Game &  ) = delete; //     COPY-Constructor
    Game(                    Game && ) = delete; //     MOVE-Constructor
    Game &  operator=( const Game &  ) = delete; //     COPY-Assignment-Operator
    Game && operator=(       Game && ) = delete; //     MOVE-Assignment-Operator

    virtual ~Game();
    //------------------------------------------------------------------------------------
    [[nodiscard]] bool    IsRunning()     const { return isRunning; }
    virtual void SetNextState( int index ) { nextStateIdx = index; }

    virtual bool HandleEvent( const Event & event );
    virtual void Input();
    virtual void Update( const u64 msSinceStart, const float deltaT       );
    virtual void Render( const u64 msSinceStart, const float deltaTNeeded );
    virtual int Run();


    // All output msec per frame, see: http://renderingpipeline.com/2013/02/fps-vs-msecframe/
    enum class PerformanceDrawMode
    {
        None,
        Title,      // averaged and only updated every 250ms
        OStream,    // averaged and only updated every 1000ms
    };

    void SetPerfDrawMode( PerformanceDrawMode mode ) noexcept { perfDrawMode = mode; }

protected:
    virtual void ActivateNextState();

    PerformanceDrawMode perfDrawMode = PerformanceDrawMode::None;
    u32 lastPerfInfoFrame = 0;
    TimePoint lastPerfInfoTime = Clock::now();
    Duration accumulatedNeeded = Duration::zero();

    [[nodiscard]] float AverageMSecPerFrame() const;
    void ResetPerformanceInfo( const TimePoint current );
    void OutputPerformanceInfo( const TimePoint current, const Duration needed );

};

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

class GameState {
protected:
    Game &game;
    std::shared_ptr<Renderer> renderer;

public:
    // CONSTRUCTORS
    // -----------------------------------------------------------------------------------
    explicit GameState( Game & game_, shared_ptr<Renderer> render_ )
            :  game( game_ ), renderer( render_ )
    {}

    explicit GameState( Game && game_, shared_ptr<Renderer> render_ )         = delete; // prevent taking an rvalue
    GameState( const GameState &  other)                            = delete; // COPY-Constructor
    GameState( GameState && other)                                  = delete; // MOVE-Constructor
    GameState & operator=( const GameState & other)                 = delete; // COPY-ASSIGNMENT
    GameState && operator=( GameState && other)                     = delete; // MOVE-Assignment

    virtual ~GameState() = default;
    //------------------------------------------------------------------------------------

    virtual bool  IsFPSLimited()  const { return true; }

    virtual void Init() {}
    virtual void UnInit() {}

    // Returns a bool to know if the Event was handled
    virtual bool HandleEvent( const Event & event ) = 0;

    // This is mostly being replaced by HandleEvent, only use for stateful inputs
    virtual void Input() {};

    virtual void Update( const u32 framesSinceStart, const u32 msSinceStart, const float deltaT ) = 0;
    virtual void Render( const u32 framesSinceStart, const u32 msSinceStart, const float deltaT ) = 0;

};

