#pragma once
#include <SFML/Graphics.hpp>
#include <Game.hpp>
namespace msp {
	struct Point {
		float x; float y;
	};
	class Circle {
		float x; float y; sf::CircleShape shape; int width; int height;
		sf::Vector2f velocity;
	public:
		Circle(float x, float y, float vx, float vy, float radius,int width,int height) : velocity(vx, vy), width(width), height(height) {
			this->x = x; this->y = y;
			shape.setRadius(radius);
			shape.setOrigin(radius, radius);
			shape.setPosition(x, y);
			shape.setFillColor(sf::Color(rand() % 235 + 20, rand() % 235 + 20, rand() % 235 + 20, rand() % 240 + 15));

		}
		void update(float dt) {
			shape.move(velocity * dt);

			if (shape.getPosition().x - shape.getRadius() < 0 || shape.getPosition().x + shape.getRadius() > width) {
				velocity.x *= -1;
			}

			if (shape.getPosition().y - shape.getRadius() < 0 || shape.getPosition().y + shape.getRadius() > height) {
				velocity.y *= -1;
			}
		}
		sf::CircleShape Circle::Get(){
			return shape;
		}
		sf::Vector2f& Velocity(){
			return velocity;};
		const sf::Vector2f& Circle::getPosition() const {
			return shape.getPosition();
		}
		float	Circle::getRadius() const {
			return shape.getRadius();
		}
	};
}