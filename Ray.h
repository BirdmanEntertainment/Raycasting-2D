#include "Boundary.h"

class Ray {

	public:
		float x, y;
		float x2, y2;

		double angle = 0;
		float baseLength = 1500;
		float length;

		Ray(int x, int y, double angle)
		{
			setPos(x, y);
			this->angle = angle;
		}

		void setPos (int x, int y)
		{
			this->x = x;
			this->y = y;
		}

		sf::Vector2f getCollisionPoint(Boundary& b)
		{
			float x1 = this->x;
			float y1 = this->y;

			float x3 = b.x1;
			float y3 = b.y1;
			float x4 = b.x2;
			float y4 = b.y2;

			float pXNumerator = (x1*y2 - y1*x2)*(x3-x4)-(x1-x2)*(x3*y4-y3*x4);

			float pYNumerator = (x1*y2 - y1*x2)*(y3-y4)-(y1-y2)*(x3*y4-y3*x4);
			float den = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);

			float t = ((x1-x3)*(y3-y4) - (y1-y3)*(x3-x4)) / den;
			float u = -((x1-x2)*(y1-y3) - (y1-y2)*(x1-x3)) / den;


			if(t > 0 && t < 1 && u > 0 && u < 1)
			{
				x2 = x1+t * (x2-x1);
				y2 = y1+t * (y2 - y1);
				length = sqrt(pow(x2 - x, 2) + pow(y2 - y, 2) * 1.0);
			}
			return {x2, y2};
		}
		void drawRay(sf::RenderWindow& rWindow)
		{

			sf::Vertex line[2];
			line[0].position = sf::Vector2f(this->x, this->y);
			line[0].color  = sf::Color(255, 255, 255, 255);
			line[1].position = sf::Vector2f(this->x2, this->y2);
			line[1].color = sf::Color(255, 255, 255, 255);

			rWindow.draw(line, 2, sf::Lines);

			this->x2 = baseLength * cos(angle) + x;
			this->y2 = baseLength * sin(angle) + y;
		}
};
