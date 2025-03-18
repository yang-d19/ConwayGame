#include <iostream>
#include <limits>

#include "displayer.hpp"
#include "game_logic.hpp"

constexpr char CLEAR[] = "\033[2J\033[H";
constexpr char BLACK_BLOCK[] = "\033[40m  \033[0m";
constexpr char WHITE_BLOCK[] = "\033[47m  \033[0m";

// limit window size for better visualization
constexpr int kWindowMaxWidthX = 30;
constexpr int kWindowMaxWidthY = 50;

void Displayer::SetWindowStart(int start_x, int start_y) {
    window_start_x_ = start_x;
    window_start_y_ = start_y;
}

void Displayer::SetWindowSize(int width_x, int width_y) {
    window_size_x_ = std::min(kWindowMaxWidthX, width_x);
    window_size_y_ = std::min(kWindowMaxWidthY, width_y);
}

std::pair<int, int> Displayer::GetWindowStart() const {
    return {window_start_x_, window_start_y_};
}

std::pair<int, int> Displayer::GetWindowSize() const {
    return {window_size_x_, window_size_y_};
}

void Displayer::DynamicFitWindow(const GameLogic& game, bool fit_window_size) {
    int min_x = std::numeric_limits<int>::max();
    int min_y = std::numeric_limits<int>::max();
    int max_x = std::numeric_limits<int>::min();
    int max_y = std::numeric_limits<int>::min();

    for (auto& pose: game.GetCellLiveSet()) {
        min_x = std::min(min_x, pose.x);
        min_y = std::min(min_y, pose.y);
        if (fit_window_size) {
            max_x = std::max(max_x, pose.x);
            max_y = std::max(max_y, pose.y);
        }
    }
    SetWindowStart(min_x - 1, min_y - 1);
    if (fit_window_size) {
        SetWindowSize(max_x - min_x + 3, max_y - min_y + 3);
    }
}

void Displayer::ShowMainWindow(const GameLogic& game) const {
    std::cout << CLEAR;
    for (int x = window_start_x_; x < window_start_x_ + window_size_x_; x++) {
        for (int y = window_start_y_ ; y < window_start_y_ + window_size_y_; y++) {
            std::cout << (game.IsCellLive(Position(x, y)) ? BLACK_BLOCK : WHITE_BLOCK);
        }
        std::cout << '\n';
    }
}

void Displayer::ShowExtraMessage(const std::string& msg) const {
    std::cout << "--------------------" << std::endl;
    std::cout << msg << std::endl;
}