#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <string>;
#include "date.h";



sf::RenderWindow window(sf::VideoMode(855, 950), L"Calendar", sf::Style::Close);
int coord_days_rectangle[2][50] = {0};
sf::Font font;
int day_with_note[31] = { 0 };
int year_now = 2019;
int month_now = 10;
int day_now = 1;
int day_month[6][7] = { 0 };
sf::Sprite LeftSelector;
sf::Sprite RightSelector;

#include "Note.h";
#include "List_of_note.h";

void mass_days() {
    int jj = 0;
    for (int x = 100; x < 700; x += 100) {
        for (int y = 120; y < 800; y += 100) {
            coord_days_rectangle[0][jj] = x;
            coord_days_rectangle[1][jj] = y;
            ++jj;
            y += 10;
        }
        x += 10;
    }
}



void draw_numbers() {
    std::string num_date = "1";
    int dd = 1;
    int first = 0;
    int ii2_ = 0;
    int start_month = write_day(day_now, month_now, year_now);
    if (start_month == -1) {
        start_month = 6;
    }
    int jj2_ = start_month;
    if (leap_year(year_now)) {
        day_in_month[1] = 29;
    }
    else {
        day_in_month[1] = 28;
    }
    for (int ii = 0; ii <= 35; ii+=7) {
        for (int jj = start_month-first; jj <= 6; ++jj) {
            ++jj2_;
            sf::Text text;
            text.setFont(font);
            if (jj == 5 || jj == 6) {
                text.setFillColor(sf::Color::Red);
            }
            else {
                text.setFillColor(sf::Color::Black);
            }
            text.setStyle(sf::Text::Bold | sf::Text::Underlined);
            text.setString(num_date);
            text.setPosition(coord_days_rectangle[0][ii] + 5, coord_days_rectangle[1][jj] - 35);
            window.draw(text);
            ++dd;
            num_date = std::to_string(dd);
            if (dd > day_in_month[month_now]) {
                    break;
            }
        }
        first = start_month;
        ++ii2_;
        jj2_ = 0;
        if (dd > day_in_month[month_now]) {
                break;
        }
    }
}


bool check_digit(std::string num) {
    for (int ii = 0; ii < num.size(); ++ii) {
        if (!isdigit(num[ii])) {
            return false;
        }
    }
    return true;
}


void change_year() {
    sf::RenderWindow win_change_year(sf::VideoMode(250, 200), "Set year", sf::Style::Close);
    std::string hhh;
    sf::Sprite b_go;
    sf::Text t_year;
    font.loadFromFile("arial.ttf");
    t_year.setFont(font);
    t_year.setFillColor(sf::Color::Black);
    t_year.setStyle(sf::Text::Bold | sf::Text::Underlined);
    t_year.setString("Set Year:");
    t_year.setPosition(20, 30);
    sf::Texture b_texture;
    b_texture.loadFromFile("open_year.png");
    b_go.setTexture(b_texture);
    b_go.setPosition(180, 130);
    Input input_year(50, 80, 150, 30);
    win_change_year.clear(sf::Color::White);
    win_change_year.draw(input_year.displayButton());
    win_change_year.draw(input_year.displayText());
    win_change_year.draw(b_go);
    win_change_year.draw(t_year);
    win_change_year.display();
    while (win_change_year.isOpen()) {
        
        sf::Event event;

        while (win_change_year.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                win_change_year.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    Vector2i mouse = Mouse::getPosition(win_change_year);
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(win_change_year);
                    sf::Vector2f pos = win_change_year.mapPixelToCoords(pixelPos);
                    input_year.select(mouse);

                    if (b_go.getGlobalBounds().contains(pos.x, pos.y)) {
                        hhh = input_year.readText();
                        //hhh.erase(hhh.size());
                        if (check_digit(hhh)) {
                            year_now = std::atoi(input_year.readText().c_str());
                            win_change_year.close();
                        }
                    }
                }
            }

            if (event.type == sf::Event::TextEntered) {
                if (input_year.select()) {
                    hhh = input_year.readText();
                    if (hhh.size() < 5) {
                        input_year.reText(event.text.unicode);
                    }
                }
            }
            
            win_change_year.clear(sf::Color::White);
            
            win_change_year.draw(input_year.displayButton());
            win_change_year.draw(input_year.displayText());
            win_change_year.draw(b_go);
            win_change_year.draw(t_year);
            win_change_year.display();
        }

    }
}



void fill_day_month() {
    for (int ii = 0; ii <= 5; ++ii) {
        for (int jj = 0; jj <= 6; ++jj) {
            day_month[ii][jj] = 0;
        }
    }
    int dd = 1;
    int first = 0;
    int ii2_ = 0;
    int start_month = write_day(day_now, month_now, year_now);
    if (start_month == -1) {
        start_month = 6;
    }
    int jj2_ = start_month;
    if (leap_year(year_now)) {
        day_in_month[1] = 29;
    }
    else {
        day_in_month[1] = 28;
    }
    for (int ii = 0; ii <= 35; ii += 7) {
        for (int jj = start_month - first; jj <= 6; ++jj) {
            day_month[ii2_][jj2_] = dd;
            ++jj2_;
            ++dd;
            if (dd > day_in_month[month_now]) {
                break;
            }
        }
        first = start_month;
        ++ii2_;
        jj2_ = 0;
        if (dd > day_in_month[month_now]) {
            break;
        }
    }
}

void draw_names() {
    std::string month_name[12] = { "Januar","February" ,"March" ,"April" ,"May" ,"June" ,"Jule" ,"August" ,"September" ,"October"
    ,"November" ,"December" };
    std::string day_names[7] = { "Mon" ,"Tue" ,"Wed" ,"Thu" ,"Fri" ,"Sat" ,"Sun" };
    for (int ii = 0; ii <= 6; ++ii) {
        sf::Text text;
        text.setFont(font);
        if (ii == 5 || ii == 6) {
            text.setFillColor(sf::Color::Red);
        }
        else {
            text.setFillColor(sf::Color::Black);
        }
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        text.setString(day_names[ii]);
        text.setPosition(20, 110*(ii+1));
        window.draw(text);
    }
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setString(month_name[month_now]);
    text.setPosition(370, 30);
    window.draw(text);

    sf::Text text_year;
    text_year.setFont(font);
    text_year.setFillColor(sf::Color::Black);
    text_year.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text_year.setString(std::to_string(year_now));
    text_year.setPosition(370, 870);
    window.draw(text_year);

}

int click_day(int x, int y) {
    x -= 100;
    y -= 80;
    int x_num = 0;
    int y_num = 0;
    if (x > 0 && y > 0) {
        x_num = x / 110;
        y_num = y / 110;
        if (day_month[x_num][y_num] != 0) {
            return day_month[x_num][y_num];
        }
    }
    return -1;
}

void draw_days() {
    int ii = 0;
    int jj = 0;
    for (int x = 100; x < 700; x += 100) {
        for (int y = 120; y < 800; y += 100) {
            if (day_month[ii][jj % 7] != 0) {
                sf::RectangleShape rectangle(sf::Vector2f(100, 100));
                rectangle.setPosition(x, y-40);
                if (day_with_note[day_month[ii][jj % 7] - 1]  != 0) {
                    rectangle.setFillColor(sf::Color::Green);
                }
                else {
                    rectangle.setFillColor(sf::Color(192, 192, 192));
                }
                window.draw(rectangle);
            }
            y += 10;
            ++jj;
        }
        ++ii;
        x += 10;
    }
}

int main() {
    sf::Texture T_Left;
    sf::Texture T_Right;
    T_Right.loadFromFile("SelectorRight.png");
    T_Left.loadFromFile("SelectorLeft.png");
    LeftSelector.setTexture(T_Left);
    RightSelector.setTexture(T_Right);
    RightSelector.setPosition(800, 50);
    LeftSelector.setPosition(30, 50);
    mass_days();
    
    font.loadFromFile("arial.ttf");
    days_with_note(month_now, year_now);
    fill_day_month();
    while (window.isOpen())
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            //std::cout << pos.y;
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Left) {

                    if (pos.x > 370 && pos.x < 420 && pos.y > 870 && pos.y < 900) {
                        change_year();
                        fill_day_month();
                        days_with_note(month_now, year_now);
                    }

                    if (RightSelector.getGlobalBounds().contains(pos.x, pos.y)) {
                        if ((month_now + 1) / 12 == 1) {
                            ++year_now;
                            month_now = 0;
                        }
                        else {
                            ++month_now;
                        }
                        fill_day_month();
                        days_with_note(month_now, year_now);
                    }
                    if (LeftSelector.getGlobalBounds().contains(pos.x, pos.y)) {
                        if ((month_now - 1 < 0)) {
                            month_now = 11;
                            --year_now;
                        }
                        else {
                            --month_now;
                        }
                        fill_day_month();
                        days_with_note(month_now, year_now);
                    }
                    if (click_day(pos.x, pos.y) != -1 && pos.x < 645 && pos.y < 838) {
                        main_list_of_note(click_day(pos.x, pos.y));
                        days_with_note(month_now, year_now);
                    }
                }
            }
            
            window.clear(sf::Color::White);
            draw_days();
            draw_numbers();
            window.draw(LeftSelector);
            window.draw(RightSelector);
            draw_names();
            window.display();
        }
        window.clear(sf::Color::White);
        draw_days();
        draw_numbers();
        window.draw(RightSelector);
        window.draw(LeftSelector);
        draw_names();
        
        window.display();
        
    }
    return 0;
}

