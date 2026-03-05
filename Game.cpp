//
// Created by sageblatt on 12.04.2022.
//
#include "Game.h"

std::unique_ptr<Game> Game::instance;

Game& Game::getInstance() {
    if (instance == nullptr)
        instance = std::unique_ptr<Game>(new Game());
    return *instance;
}

void Game::init() {
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Vector2u(1376, 768)), "Alien");
    load_texture = std::make_unique<Texture>();
    std::ignore = load_texture->loadFromFile("../images/loading.png");
    load_sprite = make_unique<Sprite>(*load_texture);

    window->clear();
    window->draw(*load_sprite);
    window->display();

    starting_menu = std::make_unique<StartingMenu>(window);
    main_menu = std::make_unique<MainMenu>(window);
    game_menu = std::make_unique<GameMenu>(window);
    rng = std::make_unique<RandomNumberGenerator>();
    a_eng = std::make_unique<AudioEngine>();

    // Initialize all levels
    for (auto lvl : {PURPLE, FIRE, ELECTRIC})
        planets[lvl] = std::make_unique<Level>(window, lvl);
}

void Game::runGame() {
    // It's safe to pass a_eng as a pointer because *this outlives audio_thread
    auto audio_thread = std::thread(&AudioEngine::run, a_eng.get());
    starting_menu->run();

    a_eng->setFadeFlag(LOR);
    for (auto i = 1; i < 4; i++)
        starting_menu->lor(i);

    a_eng->setFadeFlag(MAINMENU);
    main_menu->run();

    int planet_num;
    planet_num = game_menu->run() - 1;
    
    while (window->isOpen()) {
        a_eng->setFadeFlag(FIGHT);
        planets[planet_num]->run();
        a_eng->setFadeFlag(MAINMENU);
        planet_num = game_menu->run() - 1;
    }

    window->close();
    audio_thread.join();
}

MainMenu& Game::getMainMenu() {
    return *main_menu;
}

StartingMenu& Game::getStartingMenu() {
    return *starting_menu;
}

GameMenu& Game::getGameMenu() {
    return *game_menu;
}

RandomNumberGenerator& Game::getRng() {
    return *rng;
}

AudioEngine& Game::getAEng() {
    return *a_eng;
}

sf::RenderWindow & Game::getWindow() {
    return *window;
}

void Game::deleteGame() {
    instance.reset();
}
