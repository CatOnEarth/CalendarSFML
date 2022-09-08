#pragma once
#include <string>

void days_with_note(int month, int year) {
    for (int tt = 0; tt < 31; ++tt) {
        day_with_note[tt] = 0;
    }
    std::string line;
    int ii = 0;
    int jj = 0;
    int day = 0;
    std::string ans;
    std::string file_name = std::to_string(month) + "_" + std::to_string(year) + ".txt";
    std::ifstream in(file_name); // окрываем файл для чтения
    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            while (line[ii] != ':') {
                ans += line[ii];
                ++ii;

            }
            day = std::atoi(ans.c_str());
            //std::cout << ans << std::endl;
            ++day_with_note[day - 1];
            ii = 0;
            ans = "";
        }
    }
    in.close();     // закрываем файл
}