//
// Created by sageblatt on 01.04.2022.
//
#ifndef ALIEN_STARTINGMENU_H
#define ALIEN_STARTINGMENU_H

#include "MainMenu.h"

#include "Menu.h"

using namespace sf;
using std::unique_ptr;

class StartingMenu: public Menu {
protected:
    unique_ptr<Font> font;
    unique_ptr<Text> tab_text;

    std::array<unique_ptr<Texture>, 6> lor_textures;
    std::array<unique_ptr<Sprite>, 6> lor_sprites;

    unique_ptr<Clock> timer;

    std::array<float, 3> lor_x;
    std::array<float, 3> lor_y;

    const float LOR_SPEED = 50;

public:
    explicit StartingMenu(std::shared_ptr<RenderWindow> wind);

    void lor(unsigned n);
    int run() override;
};


#endif //ALIEN_STARTINGMENU_H
