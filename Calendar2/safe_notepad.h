#pragma once
#include <fstream>;
#include "read_file.h";

bool checkF(std::string file_name) {
    std::ifstream file;
    file.open(file_name);
    if (!file) {
        return false;
    }
    else {
        return true;
    }
}

void safe(std::string title, std::string note, int day_num) {
    std::string file_name = std::to_string(month_now) + "_" + std::to_string(year_now) + ".txt";
    if (!checkF(file_name)) {
        std::ofstream outfile(file_name);
        outfile << std::to_string(day_num) + ":" + title + "&" + note + '\n';
        outfile.close();
    }
    else {
        ofstream F;
        F.open(file_name, ios::app);
        F << std::to_string(day_num) + ":" + title + "&" + note + '\n';
        F.close();
    }
}