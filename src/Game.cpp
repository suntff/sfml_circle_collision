#include <Game.hpp>
namespace msp
{
    Game::Game(int width, int height, int n, const std::string& capture){
        this->width = width; this->height = height; this->width = width; this->n = n; this->capture = capture;
        m1 = random(1, 50);//масса
        m2 = random(1, 50);
    }
    float Game::random(float min, float max){
        return (double)(rand()) / RAND_MAX * (max - min) + min;
    }
    bool Game::Are_too_near(const Circle& circle1, const Circle& circle2) {
        // Сравниваем расстояние между радиусами шаров и суммой их радиусов
        return pow(pow(circle1.Get().getPosition().x - circle2.Get().getPosition().x, 2) +
            pow(circle1.Get().getPosition().y - circle2.Get().getPosition().y, 2), 0.5)
            < circle1.Get().getRadius() + circle2.Get().getRadius();
    }
    void Game::Circle_collision(Circle& circle1, Circle& circle2){
        float v1x = circle1.Vx(); float v1y = circle1.Vy();
        float v2x = circle2.Vx(); float v2y = circle2.Vy();
        float v1x_r; float v1y_r;  float v2x_r; float v2y_r;
        v1x_r = (v1x * (m1 - m2) + (2 * m2 * v2x)) / (m1 + m2);//закон сохранения энергии
        v1y_r = (v1y * (m1 - m2) + (2 * m2 * v2y)) / (m1 + m2);
        v2x_r = (v2x * (m2 - m1) + (2 * m1 * v1x)) / (m1 + m2);
        v2y_r = (v2y * (m2 - m1) + (2 * m1 * v1y)) / (m1 + m2);
        circle1.Vx(v1x_r); circle1.Vy(v1y_r);
        circle2.Vx(v2x_r); circle2.Vy(v2y_r);
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

                Circle сircle(x, y, vx, vy, r, width, height);
                tooClose = false;
                for (const auto& c : circles) {
                    if (Are_too_near(сircle, c)) {
                        tooClose = true;
                        break;
                    }
                }
                if (!tooClose){
                    circles.push_back(сircle);
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
            for (size_t i = 0; i < circles.size(); ++i) {
                for (size_t j = i + 1; j < circles.size(); ++j) {
                    if (pow(pow(circles[i].Get().getPosition().x - circles[j].Get().getPosition().x, 2) +
                        pow(circles[i].Get().getPosition().y - circles[j].Get().getPosition().y, 2), 0.5) <=
                        circles[i].Get().getRadius() + circles[j].Get().getRadius()) {
                        Circle_collision(circles[i], circles[j]);
                    }
                }
            }
            float dt = clock.getElapsedTime().asSeconds();
            clock.restart();
            
            window.clear();
            for (int i = 0; i < circles.size(); ++i) {
                circles[i].update(dt);
                window.draw(circles[i].Get());
            }
            window.display();
        }
    }
}