#pragma once

#include <string>
#include <utility>

class GameLogic;

class Displayer {
private:
    // x value of upper left pose
    int window_start_x_ = 0;
    // y value of upper left pose
    int window_start_y_ = 0;

    // window size in x axis
    int window_size_x_ = 10;
    // window size in y axis
    int window_size_y_ = 10;

public:
    /**
     * @brief Set window start position
     * 
     * @param start_x 
     * @param start_y 
     */
    void SetWindowStart(int start_x, int start_y);

    /**
     * @brief Set window sizes
     * 
     * @param width_x 
     * @param width_y 
     */
    void SetWindowSize(int width_x, int width_y);

    /**
     * @brief Get window start position
     * 
     * @return std::pair<int, int> : x pose and y pose
     */
    std::pair<int, int> GetWindowStart() const;

    /**
     * @brief Get window sizes
     * 
     * @return std::pair<int, int> : x size and y size
     */
    std::pair<int, int> GetWindowSize() const;

    /**
     * @brief Dynamicly fit window position or/and size
     * 
     * @param game : The game logic object
     * @param fit_window_size : if true, fit window size too; elsewise, fit window start position only
     */
    void DynamicFitWindow(const GameLogic& game, bool fit_window_size);

    /**
     * @brief Display game content
     * 
     * @param game 
     */
    void ShowMainWindow(const GameLogic& game) const;

    /**
     * @brief Display some extra debug message
     * 
     * @param msg 
     */
    void ShowExtraMessage(const std::string& msg) const;
};