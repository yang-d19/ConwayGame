#pragma once

#include "game_logic.hpp"
#include "displayer.hpp"
#include "utils.hpp"

#include <vector>

struct GameParams {
    // maximum running steps
    int max_step_cnt;
    // interval between two game frames (in ms)
    int frame_interval_ms;
};

struct DisplayParams {
    // window parameters
    int window_start_x;
    int window_start_y;
    int window_size_x;
    int window_size_y;

    // whether adjust window start positin
    bool dynamic_fit_window_start;
    // whether adjust window size
    bool dynamic_fit_window_size;
};

class Controller {
private:
    GameLogic game_;
    Displayer displayer_;

    // configurable parameters
    GameParams game_params_;
    DisplayParams display_params_;

    // running steps of current game
    int running_steps_ = 0;

public:
    /**
     * @brief Set the Game Parameter object
     * 
     * @param game_params 
     */
    void SetGameParameter(const GameParams& game_params) {
        game_params_ = game_params;
    }

    /**
     * @brief Set the Displayer Parameter object
     * 
     * @param display_params 
     */
    void SetDisplayerParameter(const DisplayParams& display_params) {
        display_params_ = display_params;
    }

    /**
     * @brief Set the Init Pattern object
     * 
     * @param live_cell_poses 
     */
    void SetInitPattern(const std::vector<Position>& live_cell_poses) {
        game_.SetInitLiveCells(live_cell_poses);
    }

    /**
     * @brief Dump debug message from member variables
     * 
     * @return std::string 
     */
    std::string DumpDebugMsg() const;

    /**
     * @brief Run game logic until reach step count limit
     * 
     */
    void Run();

    /**
     * @brief Load universe to game from a file
     * 
     * @param file_name 
     * @return true : Load succeed
     * @return false : Load failed
     */
    bool LoadUniverseFromFile(const std::string& file_name);
    
    /**
     * @brief Save universe in game to a file
     * 
     * @param file_name 
     * @return true : Save succeed
     * @return false : Save failed
     */
    bool SaveUniverseToFile(const std::string& file_name);
};