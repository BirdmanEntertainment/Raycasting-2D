#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Ray.h"
//#include "Boundary.h"

using namespace std;

std::vector<Ray> rayVector;
std::vector<Boundary> boundaryVector;
std::vector<sf::RectangleShape> barVector;

int particleX;
int particleY;

int windowW = 1800;
int windowH = 600;

int rayCount = 900;

double get_degrees(double input)
{
    const double halfC = M_PI / 180;
    return input * halfC;
}

int main()
{
	for(int i = 0; i < rayCount; i++)
	{
		Ray t1(particleX, particleY, get_degrees(90) / rayCount * i);
		rayVector.insert(rayVector.begin(), t1);
	}

	// BOUNDARY CREATION //
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		Boundary b1(rand() % windowW/2 + 1, rand() % windowH + 1, rand() % windowW/2 + 1, rand() % windowH + 1);

		boundaryVector.insert(boundaryVector.begin(), b1);
	}

	Boundary upperBoundary(0, 0, windowW/2, 0);
	Boundary rightBoundary(windowW/2, 0, windowW/2, windowH);
	Boundary lowerBoundary(0, windowH, windowW/2, windowH);
	Boundary leftBoundary(0, 0, 0, windowH);
	boundaryVector.insert(boundaryVector.begin(), upperBoundary);
	boundaryVector.insert(boundaryVector.begin(), rightBoundary);
	boundaryVector.insert(boundaryVector.begin(), lowerBoundary);
	boundaryVector.insert(boundaryVector.begin(), leftBoundary);


    sf::RenderWindow window(sf::VideoMode(windowW, windowH), "Ray-tracing 2D");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// particleX--;
		    for(int i = 0; i < rayVector.size(); i++)
			{
				rayVector.at(i).angle -= get_degrees(1);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			// particleX++;
		    for(int i = 0; i < rayVector.size(); i++)
			{
				rayVector.at(i).angle += get_degrees(1);
			}
		}

        window.clear();

		for(int i = 0; i < rayVector.size(); i++)
		{
			rayVector.at(i).drawRay(window);
			//cout << rayVector.at(i).length << endl;
			for(int j = 0; j < boundaryVector.size(); j++)
			{
				boundaryVector.at(j).drawBoundary(window);

				int cpX = rayVector.at(i).getCollisionPoint(boundaryVector.at(j)).x;
				int cpY = rayVector.at(i).getCollisionPoint(boundaryVector.at(j)).y;

				rayVector.at(i).x = particleX;
				rayVector.at(i).y = particleY;

			}
		}

		particleX = sf::Mouse::getPosition(window).x;
		particleY = sf::Mouse::getPosition(window).y;

		for (int i = 0; i < rayCount; i++)
		{
			sf::RectangleShape bar;
			bar.setOrigin(1, windowH/2);
			bar.setSize(sf::Vector2f(1, windowH));
			bar.setPosition(windowW/2 + i, windowH/2);
			bar.setFillColor(sf::Color(255, 255, 255, 5000 / rayVector.at(i).length));
			bar.scale(1, 100 / rayVector.at(i).length);
			window.draw(bar);
		}

        window.display();
    }

    return 0;
}
