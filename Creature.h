#ifndef ALIEN_CREATURE_H
#define ALIEN_CREATURE_H

#include <SFML/Graphics.hpp>

using namespace sf;


class Creature {
protected:
    std::unique_ptr<Clock> timer;

    const float FRAME_RATIO = 15;

    int width;
    int height;  // ширина, высота
    float speed_x;
    float speed_y; //скорости по x, y

    float cooldown_left = 0;

    float dt;

    float x;
    float y;
    double hp;

    int window_width;
    int window_height;

    float current_frame; //хранит текущий кадр
    float current_frame_2;

    Texture texture; //sfml текстура
    Sprite  sprite = Sprite(texture);

public:
    virtual void move() = 0;
    void draw(RenderWindow& window) const;
    void receiveDamage(double damage);

    void resetTimer();

    void setSpriteColor(Color c);

    virtual FloatRect getRect();
    double getHp() const;
};

#endif //ALIEN_CREATURE_H
