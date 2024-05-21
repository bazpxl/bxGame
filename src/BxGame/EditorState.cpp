//
// Created by bzl on 19.05.2024.
//

#include "EditorState.h"
#include <core/global.h>

#include "core/world_data.h"


void EditorState::Init() {
    // Map = std::make_shared<TileMap>(BasePath"assets/map.json");

    Map = std::make_shared<TileMap>(Vector<Layer>( {{{{1,1},{1,1}}, true}}), 32);
    Map->saveToJson(BasePath"assets/map.json");
    print("Saved\n");
}

EditorState::~EditorState() = default;

void EditorState::UnInit() {

}

void EditorState::Input(){

}


bool EditorState::HandleEvent(const Event &event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            const Keysym& what_key = event.key.keysym;

            if (what_key.scancode == SDL_SCANCODE_ESCAPE){
                exit(14);
            }else
            {
                return false; // Not handled
            }

            return true; // Confusing control flow: Handled by all but the else case

        }
        case SDL_MOUSEBUTTONDOWN:
            break;
        default:
            break;
    }
    return false;
}


void EditorState::Update(const u32 framesSinceStart, const u32 msSinceStart, const float deltaT) {
    print("Editor: Update()");
}

void EditorState::Render(const u32 framesSinceStart, const u32 msSinceStart, const float deltaT) {
    print("Editor: Render()");
}