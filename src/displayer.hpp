#pragma once

#include <utility>

class Game;

class Displayer {
private:
    int window_start_x_ = 0;
    int window_start_y_ = 0;

    int window_size_x_ = 10;
    int window_size_y_ = 10;

public:
    void SetWindowStart(int start_x, int start_y);

    void SetWindowSize(int width_x, int width_y);

    std::pair<int, int> GetWindowStart() const;

    std::pair<int, int> GetWindowSize() const;

    void DynamicFitWindow(const Game& game, bool fit_window_size);

    void Show(const Game& game) const;
};