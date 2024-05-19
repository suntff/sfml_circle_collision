#pragma once
#include <SFML/Graphics.hpp>
#include <Game.hpp>
namespace msp {
	struct Point {
		float x; float y;
	};
	class Circle {
		float x; float y; sf::CircleShape shape; int width; int height;float vx; float vy;
	public:
		Circle(float x, float y, float vx, float vy, float radius, int width, int height) {
			this->x = x; this->y = y; this->vx = vx; this->vy = vy; this->width = width; this->height = height;
			shape.setRadius(radius);
			shape.setOrigin(radius, radius);
			shape.setPosition(x, y);
			shape.setFillColor(sf::Color(rand() % 235 + 20, rand() % 235 + 20, rand() % 235 + 20, rand() % 240 + 15));

		}
		void update(float dt) {
			shape.move(vx * dt,vy*dt);

			if (shape.getPosition().x - shape.getRadius() < 0 || shape.getPosition().x + shape.getRadius() > width) {
				vx *= -1;
			}

			if (shape.getPosition().y - shape.getRadius() < 0 || shape.getPosition().y + shape.getRadius() > height) {
				vy *= -1;
			}
		}
		const sf::CircleShape Circle::Get() const{
			return shape;
		}
		float Vx() { return vx; }; float Vy() { return vy; };
		void Vx(float value) { vx = value; }; void Vy(float value) { vy = value; };

	};
}