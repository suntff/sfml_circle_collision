#pragma once
#include <string>
#include <Circle.hpp>
#include <cmath>
namespace msp
{
	class Game
	{
		int width;
		int height;
		std::string capture;
		msp::Circle* crl;
		int n;
		float v;
		float alfa;
		const long double pi = acos(-1);
		sf::RenderWindow window;
	public:
		Game(int width, int height, const std::string& capture);
		Game(const Game& other);
		Game& operator = (const Game& other);
		float random(float min, float max);
		void Setup_Circle();
		void Touch_Border(Circle& obj);
		void LifeCycle();
		~Game();
	};

}