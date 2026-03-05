#include "GameMenu.h"
using std::make_unique;

GameMenu::GameMenu(std::shared_ptr<RenderWindow> wind) {
    window = wind;

    //текстуры
    for (auto i = 0; i < 5; i++)
        textures.emplace_back(make_unique<Texture>());

    // Try to load textures
    std::ignore = textures[0]->loadFromFile("../images/planet_2.png");
    std::ignore = textures[1]->loadFromFile("../images/planet_1.png");
    std::ignore = textures[2]->loadFromFile("../images/planet_3.png");
    std::ignore = textures[3]->loadFromFile("../images/CHOOSE_A_PLANET.png");
    std::ignore = textures[4]->loadFromFile("../images/background_4.png");

    //спрайты
    for (auto i = 0; i < 5; i++)
        sprites.emplace_back(make_unique<Sprite>(*textures[i]));

}

int GameMenu::run() {
    sprites[0]->setPosition(Vector2f(950, 300)); // PURPLE 200X200
    sprites[1]->setPosition(Vector2f(500, 500)); // FIRE
    sprites[2]->setPosition(Vector2f(200, 250)); // ELECTRIC
    sprites[3]->setPosition(Vector2f(300, 60)); // CHOOSE_A_PLANET
    sprites[4]->setPosition(Vector2f(0, 0));

    //номер меню и открыто окно или нет
    int menuNum = 0;

    //вызов окна меню
    while (window->isOpen()) {
        sprites[0]->setColor(Color::White);
        sprites[1]->setColor(Color::White);
        sprites[2]->setColor(Color::White);
        menuNum = 0;
        window->clear(Color(129, 181, 221));

        if (IntRect(Vector2i(950, 300), Vector2i(200, 200)).contains(Mouse::getPosition(*window))) {
            sprites[0]->setColor(Color::Blue);
            menuNum = 1;
        } else if (IntRect(Vector2i(500, 500), Vector2i(200, 200)).contains(Mouse::getPosition(*window))) {
            sprites[1]->setColor(Color::Blue);
            menuNum = 2;
        } else if (IntRect(Vector2i(200, 250), Vector2i(200, 200)).contains(Mouse::getPosition(*window))) {
            sprites[2]->setColor(Color::Blue);
            menuNum = 3;
        }

        if (Mouse::isButtonPressed(Mouse::Button::Left)) {
            if (menuNum == 1 or menuNum == 2 or menuNum == 3)
                return menuNum;
        }

        window->draw(*sprites[4]);
        window->draw(*sprites[0]);
        window->draw(*sprites[1]);
        window->draw(*sprites[2]);
        window->draw(*sprites[3]);
        window->display();

        Event event = Event::Closed(); // Some default event initialization
        for (auto event = window->pollEvent(); event; event = window->pollEvent()) {
            if (event->is<Event::Closed>() || (event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape)) {
                    window->close();
            }
        }
    }
    return 1;
}
