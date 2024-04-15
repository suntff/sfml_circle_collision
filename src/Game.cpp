#include <Game.hpp>
#include <Circle.hpp>
#include <string>
#include <thread>
#include <chrono>
namespace msp {
	Game::Game(int width, int height, const std::string& capture) {
		this->width = width;
		this->height = height;
		this->capture = capture;
		n = rand() % 8 + 3;
	}
	Game::Game(const Game& other) {
		this->n = other.n;
		this->crl = new msp::Circle[n];
		for (int i = 0; i < n; i++) {
			this->crl[i] = other.crl[i];
		}
	}
	Game& Game::operator = (const Game& other) {
		this->n = other.n;
		delete[] this->crl;
		for (int i = 0; i < n; i++) {
			this->crl[i] = other.crl[i];
		}
		return *this;
	}
	float Game::random(float min, float max){
		return (double)(rand()) / RAND_MAX * (max - min) + min;
	}
	void Game::Setup_Circle() {
		crl = new msp::Circle[n];
		for (int i = 0; i < n; i++) {
			float r = random(5,40);
			msp::Point p1 = { random(r,1800-r), random(r,900-r) };
			float v = random(5,100);
			float alfa = random(0, 2*pi);
			crl[i].Setup(p1, r, v,alfa,n);
		}
	}
	void Game::Touch_Border(Circle& obj) {
		float x = obj.X();
		float y = obj.Y();
		float r = obj.R();
		if (x +r >= width || x - r <= 0) {
			obj.Alfa(pi - obj.Alfa());
		}
		if (y + r >= height || y - r <= 0) {
			obj.Alfa(2*pi - obj.Alfa());
		}
	}

	void Game::LifeCycle() {
		sf::Clock clock;
		window.create(sf::VideoMode(width, height), capture);
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
			}
			float dt = clock.getElapsedTime().asSeconds();
			clock.restart();
			for (int i = 0; i < n; i++) {
				crl[i].Move(dt);
			}
			for (int i = 0; i < n; i++) {
				Touch_Border(crl[i]);
			}
			window.clear();
			for (int i = 0; i < n; i++) {
				window.draw(crl[i].Get());
			}
			window.display();
		}
	}
	Game::~Game() {
		delete[] crl;
	}
}