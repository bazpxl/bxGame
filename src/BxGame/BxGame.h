//
// Created by bzl on 19.05.2024.
//

#ifndef BXGAME_BXGAME_H
#define BXGAME_BXGAME_H


#include "core/Game.h"

class BxGame : public Game{
public:
    BxGame();
    ~BxGame() override;

    bool HandleEvent(const Event &event) override;
};


#endif //BXGAME_BXGAME_H
