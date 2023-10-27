#pragma once

#include <iostream>
#include <vector>
#include <raylib.h>

#include "item.h"


class Game
{
private:
    bool m_win;
    std::vector<Item> m_items;


    void draw();
    bool check();

public:
    Game();
    ~Game();

    void run();
};