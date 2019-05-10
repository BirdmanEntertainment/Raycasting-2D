class Boundary {

    public:
        int x1, y1, x2, y2;

        Boundary(int x1, int y1, int x2, int y2)
        {
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;
        }

        // std::vector<int> GetFirstPoint()
        // {
        //     return {x1, y1};
        // }
        //
        // std::vector<int> GetSecondPoint()
        // {
        //     return {x2, y2};
        // }

        void drawBoundary(sf::RenderWindow& rWindow)
        {
            sf::Vertex line[2];
            line[0].position = sf::Vector2f(this->x1, this->y1);
            line[0].color  = sf::Color::Blue;
            line[1].position = sf::Vector2f(this->x2, this->y2);
            line[1].color = sf::Color::Blue;
            rWindow.draw(line, 2, sf::Lines);
        }
};
