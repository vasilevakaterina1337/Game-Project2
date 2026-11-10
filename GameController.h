#pragma once
#include "Base.h"
#include "GameField.h"

class GameController {
    Base base_;
    GameField field_;
    bool isRunning_;
public:
    GameController();
    void run();
};
