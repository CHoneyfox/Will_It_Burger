#pragma once
#include <iostream>
#include <raylib.h>


/*
    Burger = Bun + Patty
        Bun = Flour + Milk
            Flour = Wheat + Blender
            Milk = Cow + Grass
        Patty = Cow + Knife or Chainsaw
            Cow = DNA + Water
            Knife = Stick + Stone
                Stick = Tree + Chainsaw
*/

enum class Type {
    none=-1,
    Bun,
    PattyRaw,
    PattyCooked,
    Burger,
    Wheat,
    Flour,
    Blender,
    Milk,
    Cow,
    Grass,
    Knife,
    DNA,
    Water,
    Stick,
    Stone,
    Tree,
    Chainsaw,
    FlameThrower,
};


class Item {
private:
    Rectangle   m_position;
    Texture     m_texture;
    Type        m_type;

public:

    Item(Vector2 p_position, Texture p_texture, Type p_type);
    Item();
    ~Item();

    Rectangle& getPosition();
    Texture& getTexture();
    Type getType();

    void setPosition(Vector2& p_position);
    void setTexture(Texture p_texture);
    void setType(Type p_type);

    Item combine(Item& p_otherItem);
};