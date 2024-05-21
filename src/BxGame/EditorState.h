//
// Created by bzl on 19.05.2024.
//

#pragma once

#include "core/Game.h"


class TileMap;

class EditorState : public GameState {
private:
    shared_ptr<TileMap> Map = nullptr;
public:
    explicit EditorState(Game & game_, Renderer * renderer_) : GameState(game_, renderer_){}

    ~EditorState() override;

    void Init()                             override;
    void UnInit()                           override;

    void Input()                            override;
    bool HandleEvent( const Event & event)  override;

    void Update (const u32 framesSinceStart, const u32 msSinceStart, const float deltaT ) override;
    void Render (const u32 framesSinceStart, const u32 msSinceStart, const float deltaT ) override;



};


