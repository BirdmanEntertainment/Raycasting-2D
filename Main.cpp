#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Ray.h"
#include "Box.h"

using namespace std;

std::vector<Ray> rayVector;
std::vector<Boundary> boundaryVector;
std::vector<sf::RectangleShape> barVector;
std::vector<Box> boxVector;

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

	Box testBox(100, 100, 150, 150);
	Box testBox2(500, 500, 800, 800);
	Box testBox3(100, 400, 200, 500);
	boxVector.insert(boxVector.begin(), testBox);
	boxVector.insert(boxVector.begin(), testBox2);
	boxVector.insert(boxVector.begin(), testBox3);



    sf::RenderWindow window(sf::VideoMode(windowW, windowH), "test");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		///
		/// KEYBOARD EVENT CHECKING
		///

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

		// Clear window before drawing
        window.clear();


		// Draw all rays and boundaries, while simultaneously checking each ray against each boundary 
		for(int i = 0; i < rayVector.size(); i++)
		{
			rayVector.at(i).drawRay(window);
			
			for(int j = 0; j < boundaryVector.size(); j++)
			{
				boundaryVector.at(j).drawBoundary(window);

				float cpX = rayVector.at(i).getCollisionPoint(boundaryVector.at(j)).x;
				float cpY = rayVector.at(i).getCollisionPoint(boundaryVector.at(j)).y;


				rayVector.at(i).x = particleX;
				rayVector.at(i).y = particleY;

			}

			for(int j = 0; j < boxVector.size(); j++)
			{
				boxVector.at(j).drawBox(window);

				for(int l = 0; l < boxVector.at(j).boundaries.size(); l++)
				{	
					
					float cpX = rayVector.at(i).getCollisionPoint(boxVector.at(j).boundaries.at(l)).x;
					float cpY = rayVector.at(i).getCollisionPoint(boxVector.at(j).boundaries.at(l)).y;
				}

			}
		}

		// Render 3D half of screen
		for (int i = 0; i < rayCount; i++)
		{
			sf::RectangleShape bar;
			bar.setOrigin(1, windowH/2);
			bar.setSize(sf::Vector2f(1, windowH));
			bar.setPosition(windowW - i, windowH/2);
			bar.setFillColor(sf::Color(0, 100, 255, 255 / rayVector.at(i).length + 200));
			bar.scale(1, 100 / rayVector.at(i).length);
			window.draw(bar);
		}

		particleX = sf::Mouse::getPosition(window).x;
		particleY = sf::Mouse::getPosition(window).y;
        window.display();
    }

    return 0;
}
