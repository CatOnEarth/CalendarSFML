#pragma once

bool remove_line(std::string filename, size_t index)
{
    std::vector<std::string> vec;
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string str;
        while (std::getline(file, str))
            vec.push_back(str);
        file.close();
        if (vec.size() < index)
            return false;
        vec.erase(vec.begin() + index);
        std::ofstream outfile(filename);
        if (outfile.is_open())
        {
            std::copy(vec.begin(), vec.end(),
                std::ostream_iterator<std::string>(outfile, "\n"));
            outfile.close();
            return true;
        }
        return false;
    }
    return false;
}


void main_list_of_note(int cl_day) {
    int num_note[5] = { 0 };
    int flag = 0;
    sf::RenderWindow window_list_note(sf::VideoMode(1000, 600), L"Notes");
    std::string file_name = std::to_string(month_now) + "_" + std::to_string(year_now) + ".txt";
    std::string line;
    sf::Font font3;
    font3.loadFromFile("arial.ttf");
    std::string title_name = "";
    std::string text_note = "";
    int ii = 0;
    int day = 0;
    int y_ch = 0;
    std::string ans;
    sf:Text note_write; 
    sf::Sprite b_add_note;
    sf::Texture b_add_texture;
    b_add_texture.loadFromFile("add.png");
    b_add_note.setTexture(b_add_texture);
    b_add_note.setPosition(10, 10);
    sf::Sprite delete_1;
    sf::Sprite delete_2;
    int num_str;
    int kol_vo_str;
    sf::Sprite delete_3;
    sf::Sprite delete_4;
    sf::Sprite delete_5;
    sf::Texture delete_b;
    delete_b.loadFromFile("delete_note.jpg");
    delete_1.setTexture(delete_b);
    delete_2.setTexture(delete_b);
    delete_3.setTexture(delete_b);
    delete_4.setTexture(delete_b);
    delete_5.setTexture(delete_b);
    delete_1.setPosition(800, 30);
    delete_2.setPosition(800, 120);
    delete_3.setPosition(800, 210);
    delete_4.setPosition(800, 300);
    delete_5.setPosition(800, 390);
    window_list_note.clear(sf::Color::White);
    window_list_note.draw(b_add_note);
    window_list_note.display();
    while (window_list_note.isOpen()) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window_list_note);
        sf::Vector2f pos = window_list_note.mapPixelToCoords(pixelPos);
        sf::Event event;
        while (window_list_note.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_list_note.close();
            }


            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (b_add_note.getGlobalBounds().contains(pos.x, pos.y)) {
                        window_list_note.close();
                        main_note(cl_day);
                    }

                    if (delete_1.getGlobalBounds().contains(pos.x, pos.y)) {
                        remove_line(file_name, 0);
                    }
                    else if (delete_2.getGlobalBounds().contains(pos.x, pos.y)) {
                        remove_line(file_name, 1);
                    }
                    else if (delete_3.getGlobalBounds().contains(pos.x, pos.y)) {
                        remove_line(file_name, 2);
                    }
                    else if (delete_4.getGlobalBounds().contains(pos.x, pos.y)) {
                        remove_line(file_name, 3);
                    }
                    else if (delete_5.getGlobalBounds().contains(pos.x, pos.y)) {
                        remove_line(file_name, 4);
                    }
                }
            }
        }
        
        window_list_note.clear(sf::Color::White);
        y_ch = 0;
        num_str = 0;
        std::ifstream in(file_name);
        if (in.is_open()) {
            kol_vo_str = 0;
            flag = 0;
            while (std::getline(in, line)) {
                ++kol_vo_str;
                while (line[ii] != ':') {
                    ans += line[ii];
                    ++ii;
                }
                day = std::atoi(ans.c_str());
                if (day == cl_day) {
                    ++ii;
                    ++flag;
                    while (line[ii] != '&') {
                        title_name += line[ii];
                        ++ii;
                    }
                    ++ii;
                    while (ii <= line.size() - 1) {
                        text_note += line[ii];
                        ++ii;
                    }
                    num_note[num_str] = kol_vo_str;
                    ++num_str;

                    note_write.setFont(font3);
                    note_write.setCharacterSize(18);
                    note_write.setFillColor(sf::Color::Black);
                    note_write.setStyle(sf::Text::Bold | sf::Text::Underlined);
                    note_write.setString(title_name);
                    note_write.setPosition(100, 20 + y_ch);
                    window_list_note.draw(note_write);
                    title_name = "";

                    y_ch += 30;
                    note_write.setString(text_note);
                    note_write.setPosition(130, 20 + y_ch);
                    window_list_note.draw(note_write);
                    text_note = "";
                    y_ch += 50;



                }
                ii = 0;
                day = 0;
                ans = "";
            }
        }
        in.close();
        if (num_str == 1) {
            window_list_note.draw(delete_1);
        }
        else if (num_str == 2) {
            window_list_note.draw(delete_1);
            window_list_note.draw(delete_2);
        }
        else if (num_str == 3) {
            window_list_note.draw(delete_1);
            window_list_note.draw(delete_2);
            window_list_note.draw(delete_3);
        }
        else if (num_str == 4) {
            window_list_note.draw(delete_1);
            window_list_note.draw(delete_2);
            window_list_note.draw(delete_3);
            window_list_note.draw(delete_4);
        }
        else if (num_str == 5) {
            window_list_note.draw(delete_1);
            window_list_note.draw(delete_2);
            window_list_note.draw(delete_3);
            window_list_note.draw(delete_4);
            window_list_note.draw(delete_5);

        }
        window_list_note.draw(b_add_note);
        window_list_note.display();
        
    }
}


