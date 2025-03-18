#pragma once

#include <unordered_set>
#include <vector>

#include "utils.hpp"

class GameLogic {
private:
    std::unordered_set<Position> cell_live_set_;
    int step_cnt_ = 0;

public:
    void Reset();

    void SetInitLiveCells(const std::vector<Position>& live_cell_poses);

    std::unordered_set<Position> GetAffectedPoses() const;

    const std::unordered_set<Position>& GetCellLiveSet() const;

    bool IsCellLive(Position pose) const;

    int CheckLiveNeighborsCount(Position pose) const;

    void Update();
};