//
// Created by bzl on 19.05.2024.
//

#pragma once


#include "core/Game.h"

class BxGame : public Game{
public:
    BxGame();
    ~BxGame() override;

    bool HandleEvent(const Event &event) override;
};

