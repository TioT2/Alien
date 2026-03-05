//
// Created by sageblatt on 13.04.2022.
//
#include "AudioEngine.h"
#include "Game.h"


AudioEngine::AudioEngine() {
    timer = std::make_unique<sf::Clock>();

    fade_flag = {0, 0};

    for (auto i = 0; i < TRACKS_AMOUNT; i++)
        tracks[i] = std::make_unique<sf::Music>();

    std::ignore = tracks[0]->openFromFile("../audio/StartingMenu.ogg");
    std::ignore = tracks[1]->openFromFile("../audio/MainMenu.ogg");
    std::ignore = tracks[2]->openFromFile("../audio/Lor.ogg");
    std::ignore = tracks[3]->openFromFile("../audio/Fight.ogg");

    current_track = STARTINGMENU;

    for (auto i = 0; i < TRACKS_AMOUNT; i++) {
        // tracks[i]->setLoop(true);
        tracks[i]->setLooping(true);
        tracks[i]->setVolume(0);
    }
}

void AudioEngine::fade(int next_song) {
    fade_flag[0] = 0;
    timer->restart();
    tracks[next_song]->setVolume(0);
    auto t = timer->getElapsedTime().asSeconds();

    while (t < FADE_LEN) {
        tracks[current_track]->setVolume(100.f - 100.f * t / FADE_LEN);
        t = timer->getElapsedTime().asSeconds();
    }

    tracks[current_track]->stop();
    current_track = static_cast<Songs>(next_song);
    tracks[current_track]->play();

    timer->restart();
    t = timer->getElapsedTime().asSeconds();

    while (t < FADE_LEN)
    {
        tracks[current_track]->setVolume(100.f * t/FADE_LEN);
        t = timer->getElapsedTime().asSeconds();
    }
}

void AudioEngine::run() {
    tracks[current_track]->setVolume(100);
    tracks[current_track]->play();

    while(Game::getInstance()->getWindow()->isOpen()) {
        if (fade_flag[0])
            fade(fade_flag[1]);
    }

    tracks[current_track]->stop();
}

void AudioEngine::setFadeFlag(Songs number_of_track) {
    fade_flag[0] = 1;
    fade_flag[1] = number_of_track;
}

