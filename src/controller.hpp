#pragma once

#include "game_logic.hpp"
#include "displayer.hpp"
#include "utils.hpp"

#include <vector>

struct GameParams {
    int max_step_cnt;
    int frame_interval_ms;
};

struct DisplayParams {
    int window_start_x;
    int window_start_y;
    int window_size_x;
    int window_size_y;

    bool dynamic_fit_window_start;
    bool dynamic_fit_window_size;
};

class Controller {
private:
    GameLogic game_;
    Displayer displayer_;

    GameParams game_params_;
    DisplayParams display_params_;

    int running_steps_ = 0;

public:
    void SetGameParameter(const GameParams& game_params) {
        game_params_ = game_params;
    }

    void SetDisplayerParameter(const DisplayParams& display_params) {
        display_params_ = display_params;
    }

    void SetInitPattern(const std::vector<Position>& live_cell_poses) {
        game_.SetInitLiveCells(live_cell_poses);
    }

    std::string DumpDebugMsg() const;

    void Run();

    bool LoadUniverseFromFile(const std::string& file_name);
    
    bool SaveUniverseToFile(const std::string& file_name);
    
};