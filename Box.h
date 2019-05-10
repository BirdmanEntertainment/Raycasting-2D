//#include "Boundary.h"

class Box {

    public:
        int x1, y1, x2, y2;

        std::vector<Boundary> boundaries;
        
        Box(int x1, int y1, int x2, int y2)
        {
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;

            Boundary bTop(x1, y1, x2, y1);
            Boundary bRight(x2, y1, x2, y2);
            Boundary bBottom(x2, y2, x1, y2);
            Boundary bLeft(x1, y2, x1, y1);

            boundaries.insert(boundaries.begin(), bTop);
            boundaries.insert(boundaries.begin(), bRight);
            boundaries.insert(boundaries.begin(), bBottom);
            boundaries.insert(boundaries.begin(), bLeft);
        }

        void drawBox(sf::RenderWindow& rWindow)
        {
            sf::RectangleShape fillIn(sf::Vector2f(x2-x1, y2-y1));
            fillIn.setPosition(x1, y1);
            fillIn.setFillColor(sf::Color(255, 255, 255, 255));
            rWindow.draw(fillIn);
            for(int i = 0; i < boundaries.size(); i++)
            {
                boundaries.at(i).drawBoundary(rWindow);
            }
        }
};
