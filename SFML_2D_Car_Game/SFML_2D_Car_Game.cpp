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
    this->backround.loadFromFile(this->back_image_name);
    this->back_texture.loadFromImage(this->backround);
    this->back_sprite.setTexture(this->back_texture);
    this->back_sprite.setPosition((int)this->X_backround_pos, (int)this->Y_backround_pos);
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
    this->road_image.loadFromFile(this->road_image_name);
    this->road_texture.loadFromImage(this->road_image);
    this->road_sprite.setTexture(this->road_texture);
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
        vec_road[i].move(0, speed);
    }
}

class Car
{
protected:
    float x_car_pos = 0, y_car_pos = 0;
    std::string car_image_name = "";
    sf::Image car_image;
    sf::Texture car_texture;
    sf::Sprite car_sprite;
public:
    virtual void Init_car() = 0;
    virtual void draw_car(sf::RenderWindow& RWindow) = 0;
};

class Green_Car : Car
{
public:
    void Init_car();
    void draw_car(sf::RenderWindow& RWindow);
};

void Green_Car::Init_car()
{
    this->x_car_pos = 550; this->y_car_pos = 600;
    this->car_image_name = "../Images/Cars/Car_3.png";
    this->car_image.loadFromFile(this->car_image_name);
    this->car_texture.loadFromImage(this->car_image);
    this->car_sprite.setTexture(this->car_texture);
    this->car_sprite.setPosition(this->x_car_pos, this->y_car_pos);
}

void Green_Car::draw_car(sf::RenderWindow& RWindow)
{
    RWindow.draw(this->car_sprite);
}

class White_Car : Car
{
public:
    void Init_car();
    void draw_car(sf::RenderWindow& RWindow);
};

void White_Car::Init_car()
{
    this->x_car_pos = 560; this->y_car_pos = 600;
    this->car_image_name = "../Images/Cars/Car_2.png";
    this->car_image.loadFromFile(car_image_name);
    this->car_texture.loadFromImage(car_image);
    this->car_sprite.setTexture(car_texture);
    this->car_sprite.setPosition(x_car_pos, y_car_pos);
}

void White_Car::draw_car(sf::RenderWindow& RWindow)
{
    RWindow.draw(car_sprite);
}

class Game_logic
{
private:
    Mouse _mouse;
    Backround _backround;
    Road _road;
    White_Car _car;
public:
    Game_logic();
    void draw_elems(sf::RenderWindow& RWindow);
};

Game_logic::Game_logic()
{
    _road.init_pos();
    _car.Init_car();
}

void Game_logic::draw_elems(sf::RenderWindow& RWindow)
{
    _mouse.update_poz(RWindow);
    _road.draw_road(RWindow);
    _car.draw_car(RWindow);
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