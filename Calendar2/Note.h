#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <windows.h>
#include "FormSFML.h"
#include "safe_notepad.h";

using namespace std;
using namespace form;
using namespace sf;

sf::Text text_title_note;
sf::Font font2;

sf::Text text_name2_;
sf::Text text_nom;

void Title(int day) {
    
    font2.loadFromFile("arial.ttf");
    text_title_note.setFont(font2);
    text_title_note.setFillColor(sf::Color::Black);
    text_title_note.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text_title_note.setString(L"Note on: " + std::to_string(day) + "." + std::to_string(month_now + 1) + "." + std::to_string(year_now));
    text_title_note.setPosition(40, 20);
}

void creation_names() {
    font2.loadFromFile("arial.ttf");
    text_nom.setFont(font2);
    text_name2_.setFont(font2);

    text_nom.setFillColor(sf::Color::Black);
    text_nom.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text_name2_.setFillColor(sf::Color::Black);
    text_name2_.setStyle(sf::Text::Bold | sf::Text::Underlined);

    text_nom.setString("The Title of the note:");
    text_nom.setPosition(70, 85);
    text_name2_.setString("Note:");
    text_name2_.setPosition(70, 165);

}

void main_note(int clicked_day) {
    string hhh;
    RenderWindow window_note(sf::VideoMode(1000, 350), L"Create note");
    Button b_save(770, 260, 100, 30, "Save");
    Input input_name(70, 130, 800, 30);
    Input input_note(70, 210, 800, 30);
    creation_names();
    

    while (window_note.isOpen())
    {
        sf::Event event;
        while (window_note.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window_note.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    Vector2i mouse = Mouse::getPosition(window_note); // Считываем координаты мыши(если че обратиться можно будет mouse.x mouse.y)
                    input_name.select(mouse);	
                    input_note.select(mouse); //поле ввода
                    if (b_save.select(mouse)) {
                        if (day_with_note[clicked_day - 1] <= 4) {
                            safe(input_name.readText(), input_note.readText(), clicked_day);
                            window_note.close();
                        }
                        else {
                            std::cout << "a lot of notes" << std::endl;
                        }
                    }
                }
            }
            if (event.type == sf::Event::TextEntered) {     
                if (input_note.select()) {
                    hhh = input_note.readText();
                    input_note.reText(event.text.unicode); 
                }
                if (input_name.select()) {
                    hhh = input_name.readText();
                    input_name.reText(event.text.unicode);
                }
            }


        }

        window_note.clear(sf::Color::White);
        window_note.draw(b_save.displayButton());
        window_note.draw(b_save.displayText());

        window_note.draw(input_name.displayButton());
        window_note.draw(input_name.displayText());

        window_note.draw(input_note.displayButton());
        window_note.draw(input_note.displayText());
        Title(clicked_day);
        window_note.draw(text_title_note); 
        window_note.draw(text_name2_);
        window_note.draw(text_nom);
        window_note.display();
        sleep(milliseconds(1000 / 60));//Задержка
    }
}