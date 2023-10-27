#include <iostream>
#include <vector>
#include <raylib.h>

#include "item.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

static void draw(std::vector<Item>& p_items, bool win)
{
    if (!win)
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Connect different Items to make a burger", 225, 0, 20, BLACK);

            for (Item& item : p_items)
                DrawTextureV(item.getTexture(), (Vector2){item.getPosition().x, item.getPosition().y}, WHITE);

        EndDrawing();
    }
    else
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Yay you've won", 200, 0, 30, BLACK);

            for (Item& item : p_items)
                if (item.getType() == Type::Burger)
                    DrawTextureV(item.getTexture(), (Vector2){item.getPosition().x, item.getPosition().y}, WHITE);

        EndDrawing();
    }
}

static bool checkCollisions(std::vector<Item>& p_items)
{
    bool win = false;
    for (int i = 0; i < p_items.size(); i++)
    {
        Item& item = p_items[i];
        for (int j = i+1; j < p_items.size(); j++)
        {
            Item& otherItem = p_items[j];

            if (CheckCollisionRecs(item.getPosition(), otherItem.getPosition()))
            {
                Item newItem = item.combine(otherItem);
                if (newItem.getType() == Type::none)
                    continue;
                
                if (newItem.getType() == Type::Burger)
                    win = true;

                p_items.push_back(newItem);
            }
        }
    }

    for (int i = 0; i < p_items.size(); i++)
    {
        if (p_items[i].getType() == Type::none)
        {
            p_items.erase(p_items.begin()+i);
        }
    }


    return win;
}


int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Will It Burger");
    SetTargetFPS(60);

    std::vector<Item> items;

    items.push_back(Item((Vector2) {0, 300}, LoadTexture("res/gfx/tree.png"), Type::Tree));
    items.push_back(Item((Vector2) {0, 600}, LoadTexture("res/gfx/water.png"), Type::Water));
    items.push_back(Item((Vector2) {200, 100}, LoadTexture("res/gfx/blender.png"), Type::Blender));
    items.push_back(Item((Vector2) {600, 0}, LoadTexture("res/gfx/dna.png"), Type::DNA));
    items.push_back(Item((Vector2) {400, 400}, LoadTexture("res/gfx/wheat.png"), Type::Wheat));
    items.push_back(Item((Vector2) {600, 600}, LoadTexture("res/gfx/chainsaw.png"), Type::Chainsaw));
    items.push_back(Item((Vector2) {600, 400}, LoadTexture("res/gfx/stone.png"), Type::Stone));
    items.push_back(Item((Vector2) {400, 700}, LoadTexture("res/gfx/grass.png"), Type::Grass));
    items.push_back(Item((Vector2) {350, 50}, LoadTexture("res/gfx/flamethrower.png"), Type::FlameThrower));
    

    bool win = false;
    while (!WindowShouldClose())
    {
        if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT))
        {
            for (Item &item : items)
                if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){item.getPosition().x, item.getPosition().y, item.getPosition().width, item.getPosition().height}))
                {
                    Vector2 moveTo;
                    Vector2 mousePos;
                    Rectangle lastPos;
                    item.onclick();
                    while (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                    {
                        lastPos = item.getPosition();
                        mousePos = GetMousePosition();
                        moveTo = (Vector2){mousePos.x - lastPos.width/2, mousePos.y - lastPos.height/2};
                        item.setPosition(moveTo);

                        draw(items, win);

                        if (IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT))
                        {
                            if (checkCollisions(items))
                            {
                                win = true;
                            }
                        }
                    }
                }
        }

        draw(items, win);
    }

    return 0;
}