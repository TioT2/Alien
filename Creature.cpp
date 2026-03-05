#include "Creature.h"

void Creature::draw(RenderWindow& window) const {
    window.draw(sprite);
}

FloatRect Creature::getRect() {
    x = sprite.getPosition().x;
    y = sprite.getPosition().y;
    return FloatRect({x, y}, {100, 100});
}

void Creature::setSpriteColor(Color c) {
    sprite.setColor(c);
}

void Creature::receiveDamage(double damage) {
    hp -= damage;
}

double Creature::getHp() const {
    return hp;
}

void Creature::resetTimer() {
    timer->restart();
}
