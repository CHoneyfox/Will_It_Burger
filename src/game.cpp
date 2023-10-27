#include "game.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

void Game::draw()
{
    if (!m_win)
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Connect different Items to make a burger", 225, 0, 20, BLACK);

            for (Item& item : m_items)
                DrawTextureV(item.getTexture(), (Vector2){item.getPosition().x, item.getPosition().y}, WHITE);

        EndDrawing();
    }
    else
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Yay you've won", 200, 0, 30, BLACK);

            for (Item& item : m_items)
                if (item.getType() == Type::Burger)
                    DrawTextureV(item.getTexture(), (Vector2){item.getPosition().x, item.getPosition().y}, WHITE);

        EndDrawing();
    }
}

bool Game::check()
{
    bool win = false;
    for (int i = 0; i < m_items.size(); i++)
    {
        Item& item = m_items[i];
        for (int j = i+1; j < m_items.size(); j++)
        {
            Item& otherItem = m_items[j];

            if (CheckCollisionRecs(item.getPosition(), otherItem.getPosition()))
            {
                Item newItem = item.combine(otherItem);
                if (newItem.getType() == Type::none)
                    continue;
                
                if (newItem.getType() == Type::Burger)
                    win = true;

                m_items.push_back(newItem);
            }
        }
    }

    for (int i = 0; i < m_items.size(); i++)
    {
        if (m_items[i].getType() == Type::none)
        {
            m_items.erase(m_items.begin()+i);
        }
    }


    return win;
}

Game::Game()
    : m_win(false), m_items()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Will It Burger");
    SetTargetFPS(60);

    m_items.push_back(Item((Vector2) {0, 300}, LoadTexture("res/gfx/tree.png"), Type::Tree));
    m_items.push_back(Item((Vector2) {0, 600}, LoadTexture("res/gfx/water.png"), Type::Water));
    m_items.push_back(Item((Vector2) {200, 100}, LoadTexture("res/gfx/blender.png"), Type::Blender));
    m_items.push_back(Item((Vector2) {600, 0}, LoadTexture("res/gfx/dna.png"), Type::DNA));
    m_items.push_back(Item((Vector2) {400, 400}, LoadTexture("res/gfx/wheat.png"), Type::Wheat));
    m_items.push_back(Item((Vector2) {600, 600}, LoadTexture("res/gfx/chainsaw.png"), Type::Chainsaw));
    m_items.push_back(Item((Vector2) {600, 400}, LoadTexture("res/gfx/stone.png"), Type::Stone));
    m_items.push_back(Item((Vector2) {400, 700}, LoadTexture("res/gfx/grass.png"), Type::Grass));
    m_items.push_back(Item((Vector2) {350, 50}, LoadTexture("res/gfx/flamethrower.png"), Type::FlameThrower));
}

Game::~Game()
{

}

void Game::run()
{
    while (!WindowShouldClose())
    {
        
        if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT))
        {
            for (Item &item : m_items)
                if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){item.getPosition().x, item.getPosition().y, item.getPosition().width, item.getPosition().height}))
                {
                    Vector2 moveTo;
                    Vector2 mousePos;
                    Rectangle lastPos;
                    while (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                    {
                        lastPos = item.getPosition();
                        mousePos = GetMousePosition();
                        moveTo = (Vector2){mousePos.x - lastPos.width/2, mousePos.y - lastPos.height/2};
                        item.setPosition(moveTo);

                        draw();

                        if (IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT))
                        {
                            if (check())
                                m_win = true;
                        }
                    }
                }
        }
        draw();
    }
}