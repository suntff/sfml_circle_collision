#pragma once
#include <string>
#include <cmath>
#include <vector> 
#include <Circle.hpp>
namespace msp
{
    class Game
    {
        std::vector<Circle> circles;
        int width; int height; int n; std::string capture; float m1; float m2;

    public:
        Game(int width, int height, int n, const std::string& capture);
        float random(float min, float max);
        bool Are_too_near(const Circle& ball1, const Circle& ball2);
        void Circle_collision(Circle& ball1, Circle& ball2);
        void Circles_create();
        void LifeCycle();
    };
}