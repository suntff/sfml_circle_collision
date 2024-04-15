#pragma once
#include <SFML/Graphics.hpp>
namespace msp {
	struct Point {
		float x; float y;
	};
	class Circle{
		sf::CircleShape shape; float x; float y; float r; float v; float alfa; int n;
	public:
		Circle() = default;
		Circle(Point p1, float r, float v, float alfa, int n);
		void Setup(Point p1, float r, float v, float alfa,int n);
		sf::CircleShape Get();
		void Move(float dt);
		float X() { return x; }
		float Y() { return y; }
		float R() { return r; }
		float Alfa() { return alfa; }
		void Alfa(float alfa) {
			this->alfa = alfa;
		}
		void Inverse_V() {
			v = -v;
		}
	};
}