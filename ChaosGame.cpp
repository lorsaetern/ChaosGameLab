//Chaos Game Lab
//Group: Lor saetern & Jesus Catanghal


// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    while (window.isOpen())
    {
        // Declare a new font
        Font font;
        // Load it from a file
        if (!font.loadFromFile("Gundam.otf"))
        {
            cout << "Can't load the font file." << endl;
        }
        // Create a text which uses our font
        Text text1("CLICK ANYWHERE TO MAKE 3 POINTS FOR A TRIANGLE. THE 4TH POINT STARTS THE CHAOS!", font);
        text1.setCharacterSize(20);
        text1.setStyle(Text::Regular);
        text1.setFillColor(Color::White);
        window.clear();
        window.draw(text1);

        // Load a graphic into the texture
        Texture textureBackground;
        if (!textureBackground.loadFromFile("gundam_rx_78_2.png"))
        {
            cout << "Can't load the background file." << endl;
        }
        textureBackground.loadFromFile("gundam_rx_78_2.png");
        Sprite spriteBackground;
        spriteBackground.setTexture(textureBackground);
        spriteBackground.setPosition(0, 0);
        window.draw(spriteBackground);

        /*
        ****************************************
        Handle the players input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        points.push_back(vertices[0]);
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        /*
        ****************************************
        Update
        ****************************************
        */

        if (points.size() > 0)
        {
            for (int i = 0; i < 72; i++)
            {
                ///generate more point(s)
                ///select random vertex
                ///calculate midpoint between random vertex and the last point in the vector
                ///push back the newly generated coord.
                int random_index = rand() % vertices.size();
                Vector2f mid_point = (vertices[random_index] + points.back()) / (float)2;
                points.push_back(mid_point);
            }
        }
        /*
        ****************************************
        Draw
        ****************************************
        */
        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(3, 3));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Red);
            window.draw(rect);
        }
        for (int i = 0; i < points.size(); i++)
        {
            RectangleShape rect(Vector2f(3, 3));
            rect.setPosition(Vector2f(points[i].x, points[i].y));
            rect.setFillColor(Color::Red);
            window.draw(rect);
        }
        window.display();
    }
}