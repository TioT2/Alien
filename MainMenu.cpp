#include "MainMenu.h"

MainMenu::MainMenu(std::shared_ptr<RenderWindow> wind) {
    window = wind;

    //текстуры
    for (auto i = 0; i < 4; i++)
        textures.emplace_back(make_unique<Texture>());

    std::ignore = textures[0]->loadFromFile("../images/CONTINUE.png");
    std::ignore = textures[1]->loadFromFile("../images/EXIT.png");
    std::ignore = textures[2]->loadFromFile("../images/NEW_GAME.png");
    std::ignore = textures[3]->loadFromFile("../images/background_4.png");

    //спрайты
    for (auto i = 0; i < 4; i++)
        sprites.emplace_back(make_unique<Sprite>(*textures[i]));
}

int MainMenu::run() {
    sprites[0]->setPosition(Vector2f(350, 200));
    sprites[1]->setPosition(Vector2f(350, 400));
    sprites[2]->setPosition(Vector2f(350, 200));
    sprites[3]->setPosition(Vector2f(0, 0));

    //номер меню
    int menuNum = 0;

    //вызов окна меню
    while (window->isOpen()) {
        sprites[0]->setColor(Color::White);
        sprites[1]->setColor(Color::White);
        sprites[2]->setColor(Color::White);
        menuNum = 0;
        window->clear(Color(129, 181, 221));

        if (IntRect({500, 400}, {300, 100}).contains(Mouse::getPosition(*window))) {
            sprites[1]->setColor(Color::Red);
            menuNum = 1; //кнопка exit(убрали continue)
        }
        if (IntRect({450, 200}, {600, 100}).contains(Mouse::getPosition(*window))) {
            sprites[2]->setColor(Color::Red);
            menuNum = 2; //кнопка new_game
        }

        if (Mouse::isButtonPressed(Mouse::Button::Left)) {
            if (menuNum == 1)
                window->close(); //если нажали первую кнопку, то выходим из меню
        }

        if (Mouse::isButtonPressed(Mouse::Button::Left)) {
            if (menuNum == 2) //если нажали кнопку new_game, то перешли в GameMenu
                return 0;
        }

        window->draw(*sprites[3]);
        for (auto i = 1; i < 3; i++)
            window->draw(*sprites[i]);
        window->display();

        for (;;) {
            Event event = Event::Closed();
            if (auto eopt = window->pollEvent(); eopt)
                event = *eopt;
            else
                break;

            if (event.is<Event::Closed>() ||
                (event.is<Event::KeyPressed>() && event.getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape)) {
                    window->close();
            }
        }
    }
    return 1;
}
