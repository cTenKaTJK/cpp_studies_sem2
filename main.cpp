#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


#define GRAVITY 1.8
#define N 0.35
#define COUNT 5
#define SPAN 40
#define HEIGHT 600
#define WIDTH 800
#define RADIUS 16


enum class Direction {UP, DOWN};

class MovingCircle
{
private:
    sf::CircleShape shape_;
    Direction direction_;
    float speed_;
    int x_, y_;
    unsigned radius_;
    bool falling_;

public:
    MovingCircle() {
        speed_ = 0;
        falling_ = false;
        direction_ = Direction::DOWN;
        radius_ = RADIUS;
        x_ = SPAN;
        y_ = SPAN;
        shape_.setFillColor(sf::Color::Magenta);
        shape_.setPosition(x_, y_);
        shape_.setRadius(RADIUS);
    }

    MovingCircle(int x, int y, unsigned radius, sf::Color color) {
        speed_ = 0;
        falling_ = false;
        radius_ = radius;
        direction_ = Direction::DOWN;
        x_ = x;
        y_ = y;
        shape_.setFillColor(color);
        shape_.setPosition(x_, y_);
        shape_.setRadius(radius_);
    }

    ~MovingCircle() {}

    MovingCircle(const MovingCircle& other) {
        speed_ = 0;
        falling_ = false;
        y_ = other.y_;
        x_ = other.x_ + SPAN;
        shape_ = other.shape_;
        shape_.setPosition(x_, y_);
    }

    sf::CircleShape shape() { return shape_; }

    void lock() { falling_ = false; }

    void unlock() { falling_ = true; }

    void up() {
        speed_ -= GRAVITY;
        y_ -= speed_;
        shape_.setPosition(x_, y_);
    }

    void down() {
        speed_ += GRAVITY;
        y_ += speed_;
        shape_.setPosition(x_, y_);
    }

    void bounce() {
        if (direction_ == Direction::DOWN)
            direction_ = Direction::UP;
    }

    void fall() {
        if (direction_ == Direction::UP)
            direction_ = Direction::DOWN;
    }

    void frame() {
        if (falling_) {
            if (direction_ == Direction::DOWN)
                down();

            else if (direction_ == Direction::UP)
                up();

            if ((y_ >= HEIGHT - radius_ * 2) && (speed_ <= 0.5)) {
                lock();
            }

            else if (y_ >= HEIGHT - radius_ * 2)
                bounce();

            if (speed_ <= 0)
                fall();
        }
    }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Blip-Blop");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    sf::Font font;
    if (!font.loadFromFile("./src/font.ttf"))
        return -1;
    sf::Text text(L"для начала нажмите любую клавишу", font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Magenta);
    text.setPosition(164, 32);

    MovingCircle* cycls = new MovingCircle[COUNT];
    for (short i = 0; i < COUNT; i++) {
        unsigned radius = 8 + rand() % 32;
        int x = (1 + rand() % 19) * SPAN;
        int y = radius + rand() % 200;
        uint8_t color_r = 100 + rand() % 155;
        uint8_t color_g = 100 + rand() % 155;
        uint8_t color_b = 100 + rand() % 155;
        cycls[i] = MovingCircle(x, y, radius, sf::Color(color_r, color_g, color_b));
    }

    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    for (short i = 0; i < COUNT; i++) cycls[i].unlock();

                default:
                    break;
            }
        }
        window.clear();

        for (short i = 0; i < COUNT; i++) {
            cycls[i].frame();
            window.draw(cycls[i].shape());
        }

        window.draw(text);

        window.display();
    }

    return 0;
}