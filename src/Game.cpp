#include <Game.hpp>
namespace msp
{
    Game::Game(int width, int height, int n, const std::string& capture){
        this->width = width; this->height = height; this->width = width; this->n = n; this->capture = capture;
        m1 = random(1, 100);//масса
        m2 = random(1, 100);
    }
    float Game::random(float min, float max){
        return (double)(rand()) / RAND_MAX * (max - min) + min;
    }
    bool Game::Are_too_near(const Circle& ball1, const Circle& ball2) {
        // Сравниваем расстояние между радиусами шаров и суммой их радиусов
        return pow(pow(ball1.getPosition().x - ball2.getPosition().x, 2) +
            pow(ball1.getPosition().y - ball2.getPosition().y, 2), 0.5)
            < ball1.getRadius() + ball2.getRadius();
    }
    void Game::Handling_collision(Circle& ball1, Circle& ball2){
        sf::Vector2f v1 = ball1.Velocity();
        sf::Vector2f v2 = ball2.Velocity();
        sf::Vector2f v1f, v2f;
        v1f.x = (v1.x * (m1 - m2) + (2 * m2 * v2.x)) / (m1 + m2);//закон сохранения энергии
        v1f.y = (v1.y * (m1 - m2) + (2 * m2 * v2.y)) / (m1 + m2);
        v2f.x = (v2.x * (m2 - m1) + (2 * m1 * v1.x)) / (m1 + m2);
        v2f.y = (v2.y * (m2 - m1) + (2 * m1 * v1.y)) / (m1 + m2);
        ball1.Velocity() = v1f;
        ball2.Velocity() = v2f;
    }
    void Game::Circles_create(){
        for (int i = 0; i < n; ++i){
            bool tooClose = true;
            while (tooClose) {
                float r = random(5, 60);
                float x = random(2 * r + 1, width - 2 * r - 1);
                float y = random(2 * r + 1, height - 2 * r - 1);
                float vx = random(5, 80);
                float vy = random(5, 80);

                Circle new_сircle(x, y, vx, vy, r, width, height);
                tooClose = false;
                for (const auto& circle : circles) {
                    if (Are_too_near(new_сircle, circle)) {
                        tooClose = true;
                        break;
                    }
                }
                if (!tooClose){
                    circles.push_back(new_сircle);
                }
            }
        }
    }
    void Game::Circle_collision(){
        for (size_t i = 0; i < circles.size(); ++i) {
            for (size_t j = i + 1; j < circles.size(); ++j) {
                if (pow(pow(circles[i].getPosition().x - circles[j].getPosition().x, 2) +
                    pow(circles[i].getPosition().y - circles[j].getPosition().y, 2), 0.5) <=
                    circles[i].getRadius() + circles[j].getRadius()) {
                    Handling_collision(circles[i], circles[j]);
                }
            }
        }
    }
    void Game::LifeCycle(){
        sf::RenderWindow window(sf::VideoMode(width, height), capture);
        Circles_create();
        sf::Clock clock;

        while (window.isOpen()){
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            float dt = clock.getElapsedTime().asSeconds();
            clock.restart();
            Circle_collision();

            // Обновление и отрисовка шариков
            window.clear();
            for (int i = 0; i < circles.size(); ++i) {
                circles[i].update(dt);
                window.draw(circles[i].Get());
            }
            window.display();
        }
    }
}