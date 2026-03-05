#ifndef ALIEN_BULLET_H
#define ALIEN_BULLET_H

#include "Creature.h"

class Bullet {
protected:
    Texture texture;
    Sprite sprite {texture};

    std::unique_ptr<Clock> timer;
    float dt;

    int direction;

    bool life = true;
    const bool for_hero;

    float speed;

    const double damage;

public:
    Bullet(int dir, float x, float y, double dmg, float spd, bool for_hero_);

    void move();
    void draw(RenderWindow& window);

    void setLife(bool life);

    FloatRect getRect();
    bool isLife() const;
    bool isForHero() const;
    double getDamage() const;
};

#endif //ALIEN_BULLET_H
