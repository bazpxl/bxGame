//
// Created by bzl on 19.05.2024.
//

#include "BxGame.h"
#include "EditorState.h"

BxGame::BxGame() : Game("BzGame", Point(1024,720),  true)
{
    allStates = {
        std::make_shared<EditorState>(*this, renderer)
    };

    SetNextState(0);
    SetPerfDrawMode( PerformanceDrawMode::Title );

}

bool BxGame::HandleEvent(const Event &event)
{
        // Global Keybindings, will be checked before the ones in GameState
        if( Game::HandleEvent( event ) )
            return true;

        switch( event.type )
        {
            case SDL_KEYDOWN:
            {
                const Keysym & what_key = event.key.keysym;

                if( what_key.scancode == SDL_SCANCODE_9 )
                {
                    // Both Game and GameState can change the State,
                    // but it will only be changed after the current frame
                    SetNextState( 0 );
                    return true;
                }
                break;
            }

            default:
                break;
        }

        return false;
}



BxGame::~BxGame() = default;
