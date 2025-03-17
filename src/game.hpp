#pragma once

#include "displayer.hpp"
#include "utils.hpp"
#include <string>
#include <unordered_set>
#include <vector>

class Game {
private:
    std::unordered_set<Position> cell_live_set_;
    int step_cnt_ = 0;

    Displayer dispayer_;

public:
    void Reset();

    void SetInitLiveCells(const std::vector<Position>& live_cell_poses);

    std::unordered_set<Position> GetAffectedPoses() const;

    const std::unordered_set<Position>& GetCellLiveSet() const;

    bool IsCellLive(Position pose) const;

    int CheckLiveNeighborsCount(Position pose) const;

    void Update();

    void Show(bool dynamic_fit_window_start, bool dynamic_fit_window_size, const std::string& msg);

    void Run(int max_step=-1, int interval_ms=1000, int display_width_x=10, int display_width_y=12, bool dynamic_adjust_window=true, bool dynamic_fit_window_size=true);
};