#include "StartingMenu.h"

using std::make_unique;

StartingMenu::StartingMenu(std::shared_ptr<RenderWindow> wind) {
    window = wind;

    font = make_unique<Font>();
    std::ignore = font->openFromFile("../fonts/tab.ttf");

    tab_text = make_unique<Text>(*font, "Press Tab to continue", 20);
    tab_text->setPosition(Vector2f(100, 700));

    timer = make_unique<Clock>();
    timer->restart();

    lor_x = {-300, -100, 400};
    lor_y = {700, 500, 300};

    //текстуры
    for (auto i = 0; i < 3; i++)
        textures.emplace_back(make_unique<Texture>());

    for (auto i = 0; i < 6; i++)
        lor_textures[i] = make_unique<Texture>();

    std::ignore = textures[0]->loadFromFile("../images/PLAY.png");
    std::ignore = textures[1]->loadFromFile("../images/alien_wave_2.png");
    std::ignore = textures[2]->loadFromFile("../images/first_screen.png");

    std::ignore = lor_textures[0]->loadFromFile("../images/lor_1.png");
    std::ignore = lor_textures[1]->loadFromFile("../images/The_Earth.png");
    std::ignore = lor_textures[2]->loadFromFile("../images/lor_2.png");
    std::ignore = lor_textures[3]->loadFromFile("../images/gym.png");
    std::ignore = lor_textures[4]->loadFromFile("../images/lor_3.png");
    std::ignore = lor_textures[5]->loadFromFile("../images/monsters.png");

    //спрайты
    for (auto i = 0; i < 3; i++)
        sprites.emplace_back(make_unique<Sprite>(*textures[i]));

    for (auto i = 0; i < 6; i++)
        lor_sprites[i] = make_unique<Sprite>(*lor_textures[i]);
}

int StartingMenu::run() {
    sprites[0]->setPosition(Vector2f(300, 600));
    sprites[1]->setPosition(Vector2f(-400, -500));
    sprites[2]->setPosition(Vector2f(0, 0));

    //номер меню
    int menuNum = 0;

    //вызов окна меню
    while (window->isOpen()) {
        window->clear(Color(129, 181, 221));

        if (IntRect({400, 600}, {400, 100}).contains(Mouse::getPosition(*window))) {
            sprites[0]->setColor(Color::Red);
            menuNum = 1;
        }

        if (Mouse::isButtonPressed(Mouse::Button::Left)) {
            if (menuNum == 1) {
                window->clear(Color(129, 181, 221));
                return 0;
            }
        }

        window->draw(*sprites[2]);
        window->draw(*sprites[0]);
        window->draw(*sprites[1]);
        window->display();

        for (auto event = window->pollEvent(); event; event = window->pollEvent()) {
            if (event->is<Event::Closed>() || (event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape)) {
                window->close();
            }
        }
    }
    return 1;
}

void StartingMenu::lor(unsigned n) {
    timer->restart();
    auto i1 = 2 * n - 2; //0
    auto i2 = 2 * n - 1; //1
    lor_sprites[i2]->setPosition(Vector2f(0, 0));
    lor_sprites[i1]->setPosition(Vector2f(-700, 300));

    float x = lor_x[n - 1];
    float y = lor_y[n - 1];

    while (window->isOpen()) {
        if (y >= 0) {
            auto t = timer->getElapsedTime().asSeconds();
            y = y - LOR_SPEED * t;
            lor_sprites[i1]->setPosition(Vector2f(x, y));
            timer->restart();
        }

        window->draw(*lor_sprites[i2]);
        window->draw(*lor_sprites[i1]);

        if (y <= 0)
            window->draw(*tab_text);

        window->display();
        window->clear();

        for (;;) {
            Event event = Event::Closed();
            if (auto eopt = window->pollEvent(); eopt)
                event = *eopt;
            else
                break;

            if (auto e = event.getIf<Event::KeyPressed>(); e != nullptr && e->code == Keyboard::Key::Tab)
                return;
            else if (event.is<Event::Closed>())
                window->close();
        }
    }
}
