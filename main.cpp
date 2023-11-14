#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <vector>

#include "Camera.h"
#include "Element.h"

/*
TO BUILD: (Change SFML install location to yours)
g++ -std=c++11 *.cpp -I/usr/local/Cellar/sfml/2.6.0/include -o application -L/usr/local/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-window -lsfml-system
*/

const float SCREEN_WIDTH = 500;
const float SCREEN_HEIGHT = 300;
const float SCREEN_UP_SCALE = 2;

const float moveSpeed = 0.5f;

Camera camera(1, 0, 2, 90, -80, SCREEN_WIDTH, SCREEN_HEIGHT);

Element robotBase(5.0f, 6.0f, 5.0f, 6.0f, 0.0f, 1.5f, sf::Color::Red);
Element robotArm1(5.0f, 6.0f, 5.0f, 6.0f, 1.5f, 3.5f, sf::Color::Yellow);


std::vector<Element> elements = {robotBase, robotArm1};

void draw(sf::RenderWindow &window, sf::Texture &texture, sf::Sprite &sprite)
{
    
    sf::Uint8* pixels = new sf::Uint8[int(SCREEN_WIDTH * SCREEN_HEIGHT) * 4];

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            int index = x + y * SCREEN_WIDTH;


            sf::Color pixelColor = camera.castRay(x, y, elements); 

            pixels[index * 4 + 0] = pixelColor.r;
            pixels[index * 4 + 1] = pixelColor.g;
            pixels[index * 4 + 2] = pixelColor.b;
            pixels[index * 4 + 3] = pixelColor.a;

        }
    }

    window.clear();

    texture.update(pixels);
    sprite.setTexture(texture);
    window.draw(sprite);

    window.display();

}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "C++ Robot Sim");
    
    window.setSize(sf::Vector2u(SCREEN_WIDTH * SCREEN_UP_SCALE, SCREEN_HEIGHT * SCREEN_UP_SCALE));

    sf::Texture texture;
    if (!texture.create(int(SCREEN_WIDTH), int(SCREEN_HEIGHT)))
    {
        return -1;
    }
    sf::Sprite sprite;


    sf::Clock clock;
    sf::Clock fpsUpdateClock;
    int frameCount = 0;

    float cameraPitch = 90;
    float cameraYaw = -80;

    float cameraX = 1.0f;
    float cameraY = 0.0f;
    float cameraZ = 2.0f;

    while (window.isOpen())
    {   

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        frameCount++;
        if (fpsUpdateClock.getElapsedTime().asSeconds() >= 1.0) {
            std::cout << "FPS: " << frameCount << std::endl;
            fpsUpdateClock.restart();  // Restart the clock
            frameCount = 0;  // Reset frame count
        }
        


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            camera.setPitch(camera.getPitch() + 5);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            camera.setPitch(camera.getPitch() - 5);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            camera.setYaw(camera.getYaw() - 5);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            camera.setYaw(camera.getYaw() + 5);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            camera.setX(camera.getX() + moveSpeed * cos(camera.getYaw() * 3.14159 / 180));
            camera.setY(camera.getY() + moveSpeed * sin(camera.getYaw() * 3.14159 / 180));
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            camera.setX(camera.getX() - moveSpeed * cos(camera.getYaw() * 3.14159 / 180));
            camera.setY(camera.getY() - moveSpeed * sin(camera.getYaw() * 3.14159 / 180));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            camera.setX(camera.getX() - moveSpeed * cos((camera.getYaw() + 90) * 3.14159 / 180));
            camera.setY(camera.getY() - moveSpeed * sin((camera.getYaw() + 90) * 3.14159 / 180));
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            camera.setX(camera.getX() + moveSpeed * cos((camera.getYaw() + 90) * 3.14159 / 180));
            camera.setY(camera.getY() + moveSpeed * sin((camera.getYaw() + 90) * 3.14159 / 180));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            camera.fastRender = true;
            std::cout << "fastRender: enabled" << std::endl;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
            camera.fastRender = false;
            std::cout << "fastRender: disabled" << std::endl;
        }

        // move camera up and down with i and k
        /*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            camera.setZ(camera.getZ() + moveSpeed);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            camera.setZ(camera.getZ() - moveSpeed);
        }
        */

        draw(window, texture, sprite);
    }

    return 0;
}


