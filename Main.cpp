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

float viewingAngle;

float mouseSpeedX;
float mouseSpeedY;

int moveSpeed = 2;

double get_radians(double input)
{
	const double halfC = M_PI / 180;
	return input * halfC;
}

double get_degrees(double input)
{
	return input * (180 / M_PI);
}

int main()
{
	for (int i = 0; i < rayCount; i++)
	{
		Ray t1(particleX, particleY, get_radians(90) / rayCount * i);
		rayVector.insert(rayVector.begin(), t1);
	}

	// BOUNDARY CREATION //
	// srand(time(NULL));
	// for (int i = 0; i < 5; i++)
	// {
	// 	Boundary b1(rand() % windowW/2 + 1, rand() % windowH + 1, rand() % windowW/2 + 1, rand() % windowH + 1);

	// 	boundaryVector.insert(boundaryVector.begin(), b1);
	// }

	Boundary upperBoundary(0, 0, windowW / 2, 0);
	Boundary rightBoundary(windowW / 2, 0, windowW / 2, windowH);
	Boundary lowerBoundary(0, windowH, windowW / 2, windowH);
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

	viewingAngle = 0.783653;

	// Draw player
	sf::CircleShape player(15.f);
	player.setOrigin(15, 15);
	player.setFillColor(sf::Color(255, 255, 255, 255));

	sf::RenderWindow window(sf::VideoMode(windowW, windowH), "Raycasting-2D");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseMotion)
			{
				mouseSpeedX = event.mouseMotion.x; // Delta x
				mouseSpeedY = event.mouseMotion.y; // Delta y
			}
		}

		///
		/// KEYBOARD EVENT CHECKING
		///

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// particleX--;
			viewingAngle -= get_radians(1);

			for (int i = 0; i < rayVector.size(); i++)
			{
				rayVector.at(i).angle -= get_radians(1);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			// particleX++;
			viewingAngle += get_radians(1);
			for (int i = 0; i < rayVector.size(); i++)
			{
				rayVector.at(i).angle += get_radians(1);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			int moveX = 3 * cos(viewingAngle);
			int moveY = 3 * sin(viewingAngle);

			particleX += moveX;
			particleY += moveY;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			int moveX = 3 * cos(viewingAngle);
			int moveY = 3 * sin(viewingAngle);

			particleX -= moveX;
			particleY -= moveY;
		}

		if (viewingAngle > 2 * M_PI)
		{
			viewingAngle = 0;
		}
		else if (viewingAngle < 0)
		{
			viewingAngle = 2 * M_PI;
		}

		// Clear window before drawing
		window.clear();

		// Draw all rays and boundaries, while simultaneously checking each ray against each boundary
		for (int i = 0; i < rayVector.size(); i++)
		{
			rayVector.at(i).drawRay(window);
			// if(i == rayVector.size()/2)
			// {
			// 	cout << rayVector.at(i).angle << " , " << viewingAngle << endl;
			// }

			for (int j = 0; j < boundaryVector.size(); j++)
			{
				boundaryVector.at(j).drawBoundary(window);

				float cpX = rayVector.at(i).getCollisionPoint(boundaryVector.at(j)).x;
				float cpY = rayVector.at(i).getCollisionPoint(boundaryVector.at(j)).y;

				rayVector.at(i).x = particleX;
				rayVector.at(i).y = particleY;
			}

			for (int j = 0; j < boxVector.size(); j++)
			{
				boxVector.at(j).drawBox(window);

				for (int l = 0; l < boxVector.at(j).boundaries.size(); l++)
				{

					float cpX = rayVector.at(i).getCollisionPoint(boxVector.at(j).boundaries.at(l)).x;
					float cpY = rayVector.at(i).getCollisionPoint(boxVector.at(j).boundaries.at(l)).y;
				}
			}
		}

		//cout << viewingAngle << endl;

		player.setPosition(particleX, particleY);
		window.draw(player);

		// Render 3D half of screen
		for (int i = 0; i < rayCount; i++)
		{

			int shadeAmount = 500 / rayVector.at(i).length + 150;

			sf::RectangleShape bar;
			bar.setOrigin(1, windowH / 2);
			bar.setSize(sf::Vector2f(1, windowH));
			bar.setPosition(windowW - i, windowH / 2);
			bar.setFillColor(sf::Color(0, 100, 255, shadeAmount));
			bar.scale(1, 100 / rayVector.at(i).length);
			window.draw(bar);
		}

		// particleX = sf::Mouse::getPosition(window).x;
		// particleY = sf::Mouse::getPosition(window).y;
		window.display();
	}

	return 0;
}
