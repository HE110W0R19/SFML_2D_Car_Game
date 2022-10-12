#include <SFML/Graphics.hpp> //<- main sfml library for working with graphics
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <random>

class Mouse
{
    sf::Vector2i mouse_pos_window;//an int vector that stores our mouse x and y coordinates
public:
    void update_poz(sf::RenderWindow& RWindow);
    /*int check_button_press(_objects& tmp_butt);*/
};

void Mouse::update_poz(sf::RenderWindow& RWindow)
{
    this->mouse_pos_window = sf::Mouse::getPosition(RWindow);
    std::cout << sf::Mouse::getPosition(RWindow).x << " " << sf::Mouse::getPosition(RWindow).y << std::endl;
}

//int Mouse::check_button_press(_objects& tmp_butt)
//{
//    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
//        || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
//    {
//        if (tmp_butt.get_start_butt().getGlobalBounds().contains(mouse_pos_window.x, mouse_pos_window.y))
//        {
//            return 1;
//        }
//        else if (tmp_butt.get_stop_butt().getGlobalBounds().contains(mouse_pos_window.x, mouse_pos_window.y))
//        {
//            return 0;
//        }
//    }
//    return 2;
//}

class Backround
{
private:
    int X_backround_pos = 0, Y_backround_pos = 0;
    std::string back_image_name = "../Images/Road/Backround.png";
protected:
    sf::Image backround;
    sf::Texture back_texture;
    sf::Sprite back_sprite;
public:
    Backround();
    void print_backround(sf::RenderWindow& RWindow);
};

Backround::Backround()
{
    backround.loadFromFile(back_image_name);
    back_texture.loadFromImage(backround);
    back_sprite.setTexture(back_texture);
    back_sprite.setPosition(X_backround_pos, Y_backround_pos);
}

void Backround::print_backround(sf::RenderWindow& RWindow)
{
    if (RWindow.isOpen())
    {
        RWindow.draw(back_sprite);
    }
}

class Road
{
private:
    float X_road_pos = 120.f;
    int road_amount = 5;
    std::string road_image_name = "../Images/Road/Road.png";
    std::vector<float> vec_y_pos{};
protected:
    sf::Image road_image;
    sf::Texture road_texture;
    sf::Sprite road_sprite;
    std::vector<sf::Sprite> vec_road{};
public:
    Road();
    void init_pos();
    void draw_road(sf::RenderWindow& RWindow);
    void move_road(sf::RenderWindow& RWindow, float speed);
};

Road::Road()
{
    road_image.loadFromFile(road_image_name);
    road_texture.loadFromImage(road_image);
    road_sprite.setTexture(road_texture);
    for (int i = 0; i < road_amount; ++i)
    {
        vec_road.push_back(road_sprite);
    }
}

void Road::init_pos()
{
    float tmp = -650.f;
    for (int i = 0; i < road_amount; ++i, tmp += 400)
    {
        vec_y_pos.push_back(tmp);
        vec_road[i].setPosition(X_road_pos, vec_y_pos[i]);
    }
}

void Road::draw_road(sf::RenderWindow& RWindow)
{
    for (int i = 0; i < road_amount; ++i)
    {
        RWindow.draw(vec_road[i]);
    }
}

void Road::move_road(sf::RenderWindow& RWindow, float speed)
{
    float y_end_map = 850.f, y_start_map = -650.f;
    for (int i = 0; i < 4; ++i) 
    {
        if (vec_road[i].getPosition().y >= y_end_map)
        {
            vec_y_pos[i] = y_start_map; 
            vec_road[i].setPosition(X_road_pos, vec_y_pos[i]); 
        }
        RWindow.draw(vec_road[i]);
        vec_road[i].move(0, speed);
    }
}

class Car
{
private:

protected:

public:

};

class Game_logic
{
private:
    Mouse _mouse;
    Backround _backround;
    Road _road;
public:
    Game_logic();
    void draw_elems(sf::RenderWindow& RWindow);
};

Game_logic::Game_logic()
{
    _road.init_pos();
}

void Game_logic::draw_elems(sf::RenderWindow& RWindow)
{
    _mouse.update_poz(RWindow);
    _road.draw_road(RWindow);
    _road.move_road(RWindow, 0.3);
    _backround.print_backround(RWindow);
}

int main()
{
    int X_screen_size = 1400, Y_screen_size = 900;
    sf::RenderWindow window(sf::VideoMode(X_screen_size, Y_screen_size), "||| Car Racing |||");
    
    Game_logic game;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        game.draw_elems(window);
        window.display();
    }

    return 0;
}