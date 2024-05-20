//
// Created by bzl on 19.05.2024.
//

#ifndef BXGAME_EDITORSTATE_H
#define BXGAME_EDITORSTATE_H


#include "core/Game.h"

class EditorState : public GameState {
public:
    explicit EditorState(Game & game_, Renderer * renderer_) : GameState(game_, renderer_){}

    ~EditorState() override = default;

    void Init()                             override;
    void UnInit()                           override;

    void Input()                            override;
    bool HandleEvent( const Event & event)  override;

    void Update (const u32 framesSinceStart, const u32 msSinceStart, const float deltaT ) override;
    void Render (const u32 framesSinceStart, const u32 msSinceStart, const float deltaT ) override;



};


#endif //BXGAME_EDITORSTATE_H
