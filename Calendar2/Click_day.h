#pragma once

void click_day(int x, int y) {
    x -= 100;
    y -= 120;
    int x_num = 0;
    int y_num = 0;
    if (x > 0 && y > 0) {
        x_num = x / 105;
        y_num = y / 105;
    }
}