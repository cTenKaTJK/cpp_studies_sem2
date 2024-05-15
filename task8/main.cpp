#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Circle!");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    sf::CircleShape cyc(100.f);
    cyc.setFillColor(sf::Color(210, 150, 40));
    cyc.setOutlineThickness(5.f);
    cyc.setOutlineColor(sf::Color(170, 130, 25));
    cyc.setPosition(100, 100);

    sf::Font font;
    if (!font.loadFromFile("./src/font.ttf"))
        return -1;
    sf::Text text(L"ДОБРО ПОЖАЛОВАТЬ НА СЕРВЕР\n\t\tШИЗОФРЕНИЯ", font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setPosition(400, 100);

    sf::Music music;
    if (!music.openFromFile("./src/sound.ogg"))
        return -1;
    music.setLoop(true);
    music.play();


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(cyc);
        window.draw(text);
        window.display();
    }

    return 0;
}