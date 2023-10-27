#include "item.h"

#define WEEB_MODE

Item::Item(Vector2 p_position, Texture p_texture, Type p_type)
    : m_position{p_position.x, p_position.y, (float)p_texture.width, (float)p_texture.height}, m_texture(p_texture), m_type(p_type)
{
    std::cout << (int)m_type << " was created" << std::endl;
}
Item::Item()
{
    std::cout << "Unknown item was created" << std::endl;
};

Item::~Item()
{
    std::cout << (int)m_type << " was deleted" << std::endl;
}

Rectangle& Item::getPosition()
{
    return m_position;
}

Texture& Item::getTexture()
{
    return m_texture;
}

Type Item::getType()
{
    return m_type;
}

void Item::setPosition(Vector2 &p_position)
{
    m_position.x = p_position.x;
    m_position.y = p_position.y;
}

void Item::setTexture(Texture p_texture)
{
    m_texture = p_texture;
    m_position.height = p_texture.height;
    m_position.width = p_texture.width;
}

void Item::setType(Type p_type)
{
    m_type = p_type;
}


void Item::onclick()
{
    std::cout << "clicked on " << (int)m_type << std::endl;
}

Item Item::combine(Item& p_otherItem)
{
    std::cout << "combined " << (int)m_type << " with " << (int)p_otherItem.getType() << std::endl;
    Item newItem((Vector2){m_position.x, m_position.y}, LoadTexture("res/gfx/none.png"), Type::none);

    switch (m_type)
    {
        case Type::Bun:
            if (p_otherItem.getType() == Type::PattyCooked)
            {
                newItem.setType(Type::Burger);
                newItem.setTexture(LoadTexture("res/gfx/burger.png"));
                m_type = Type::none;
                p_otherItem.setType(Type::none);
            }

            break;

        case Type::PattyRaw:
            if (p_otherItem.getType() == Type::FlameThrower)
            {
                newItem.setType(Type::PattyCooked);
                newItem.setTexture(LoadTexture("res/gfx/pattycooked.png"));
                m_type = Type::none;
            }
            break;

        case Type::PattyCooked:
            if (p_otherItem.getType() == Type::Bun)
            {
                newItem.setType(Type::Burger);
                newItem.setTexture(LoadTexture("res/gfx/burger.png"));
                m_type = Type::none;
                p_otherItem.setType(Type::none);
            }
            break;

        case Type::Burger:
            break;

        case Type::Wheat:
            if (p_otherItem.getType() == Type::Blender)
            {
                newItem.setType(Type::Flour);
                newItem.setTexture(LoadTexture("res/gfx/flour.png"));
                m_type = Type::none;
            }
            break;
        
        case Type::Blender:
            if (p_otherItem.getType() == Type::Wheat)
            {
                newItem.setType(Type::Flour);
                newItem.setTexture(LoadTexture("res/gfx/flour.png"));
                p_otherItem.setType(Type::none);
            }
            break;

        case Type::Flour:
            if (p_otherItem.getType() == Type::Milk)
            {
                newItem.setType(Type::Bun);
                newItem.setTexture(LoadTexture("res/gfx/bun.png"));
                m_type = Type::none;
                p_otherItem.setType(Type::none);
            }
            break;

        case Type::Milk:
            if (p_otherItem.getType() == Type::Flour)
            {
                newItem.setType(Type::Bun);
                newItem.setTexture(LoadTexture("res/gfx/bun.png"));
                m_type = Type::none;
                p_otherItem.setType(Type::none);
            }
            break;

        case Type::Cow:
            if (p_otherItem.getType() == Type::Knife || p_otherItem.getType() == Type::Chainsaw)
            {
                newItem.setType(Type::PattyRaw);
                newItem.setTexture(LoadTexture("res/gfx/pattyraw.png"));
                m_type = Type::none;
            }
            else if (p_otherItem.getType() == Type::Grass)
            {
                newItem.setType(Type::Milk);
                newItem.setTexture(LoadTexture("res/gfx/milk.png"));
                p_otherItem.setType(Type::none);
            }
            break;

        case Type::Grass:
            if (p_otherItem.getType() == Type::Cow)
            {
                newItem.setType(Type::Milk);
                newItem.setTexture(LoadTexture("res/gfx/milk.png"));
                m_type = Type::none;
            }
            break;

        case Type::Knife:
            if (p_otherItem.getType() == Type::Cow)
            {
                newItem.setType(Type::PattyRaw);
                newItem.setTexture(LoadTexture("res/gfx/pattyraw.png"));
                p_otherItem.setType(Type::none);
            }
            break;

        case Type::DNA:
            if (p_otherItem.getType() == Type::Water)
            {
                newItem.setType(Type::Cow);
                #ifdef WEEB_MODE
                newItem.setTexture(LoadTexture("res/gfx/cow_girl.png"));
                #else
                newItem.setTexture(LoadTexture("res/gfx/cow.png"));
                #endif
                m_type = Type::none;
                p_otherItem.setType(Type::none);
            }
            break;

        case Type::Water:
            if (p_otherItem.getType() == Type::DNA)
            {
                newItem.setType(Type::Cow);
                #ifdef WEEB_MODE
                newItem.setTexture(LoadTexture("res/gfx/cow_girl.png"));
                #else
                newItem.setTexture(LoadTexture("res/gfx/cow.png"));
                #endif
                m_type = Type::none;
                p_otherItem.setType(Type::none);
            }
            break;

        case Type::Stick:
            if (p_otherItem.getType() == Type::Stone)
            {
                newItem.setType(Type::Knife);
                newItem.setTexture(LoadTexture("res/gfx/cow.png"));
                m_type = Type::none;
                p_otherItem.setType(Type::none);
            }
            break;

        case Type::Stone:
            if (p_otherItem.getType() == Type::Stick)
            {
                newItem.setType(Type::Knife);
                newItem.setTexture(LoadTexture("res/gfx/knife.png"));
                m_type = Type::none;
                p_otherItem.setType(Type::none);
            }
            break;

        case Type::Tree:
            if (p_otherItem.getType() == Type::Chainsaw)
            {
                newItem.setType(Type::Stick);
                newItem.setTexture(LoadTexture("res/gfx/stick.png"));
                m_type = Type::none;
            }
            break;

        case Type::Chainsaw:
            if (p_otherItem.getType() == Type::Tree)
            {
                newItem.setType(Type::Stick);
                newItem.setTexture(LoadTexture("res/gfx/stick.png"));
                p_otherItem.setType(Type::none);
            }
            else if (p_otherItem.getType() == Type::Cow)
            {
                newItem.setType(Type::PattyRaw);
                newItem.setTexture(LoadTexture("res/gfx/pattyraw.png"));
                p_otherItem.setType(Type::none);
            }
            break;

        case Type::FlameThrower:
            if (p_otherItem.getType() == Type::PattyRaw)
            {
                newItem.setType(Type::PattyCooked);
                newItem.setTexture(LoadTexture("res/gfx/pattycooked.png"));
                p_otherItem.setType(Type::none);
            }
            break;

        default:
            break;
    }

    return newItem;
}