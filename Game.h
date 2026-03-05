//
// Created by sageblatt on 12.04.2022.
//
#ifndef ALIEN_GAME_H
#define ALIEN_GAME_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <thread>

#include "StartingMenu.h"
#include "MainMenu.h"
#include "RandomNumberGenerator.h"
#include "AudioEngine.h"
#include "Level.h"

class Game {
private:
    std::unique_ptr<StartingMenu> starting_menu;
    std::unique_ptr<MainMenu> main_menu;
    std::unique_ptr<GameMenu> game_menu;
    std::unique_ptr<RandomNumberGenerator> rng;
    std::unique_ptr<AudioEngine> a_eng;
    std::array<std::unique_ptr<Level>, 3> planets;

    // Window is shared_ptr because it's passed to level constructors
    std::shared_ptr<sf::RenderWindow> window;

    std::unique_ptr<sf::Texture> load_texture;
    std::unique_ptr<sf::Sprite> load_sprite;

    Game() = default;

    static std::unique_ptr<Game> instance;

public:
    static Game& getInstance();

    MainMenu& getMainMenu();
    StartingMenu& getStartingMenu();
    GameMenu& getGameMenu();
    RandomNumberGenerator& getRng();
    AudioEngine& getAEng();

    sf::RenderWindow& getWindow();

    void init();
    void runGame();

    static void deleteGame();
};


#endif //ALIEN_GAME_H
