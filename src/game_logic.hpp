#pragma once

#include <unordered_set>
#include <vector>

#include "utils.hpp"

class GameLogic {
private:
    // live cells set
    std::unordered_set<Position> cell_live_set_;

public:

    void Reset();

    /**
     * @brief Set the Init Live Cells object before running the game
     * 
     * @param live_cell_poses 
     */
    void SetInitLiveCells(const std::vector<Position>& live_cell_poses);

    /**
     * @brief Get all adjacent poses of live cells
     * 
     * @return std::unordered_set<Position>
     */
    std::unordered_set<Position> GetAffectedPoses() const;

    /**
     * @brief Get the Cell Live Set object
     * 
     * @return const std::unordered_set<Position>& 
     */
    const std::unordered_set<Position>& GetCellLiveSet() const;

    /**
     * @brief Query whether a cell at given pose is live or not
     * 
     * @param pose 
     * @return true : The cell is live
     * @return false : The cell is dead
     */
    bool IsCellLive(Position pose) const;

    /**
     * @brief Get live cell count among a given cell's neighbors
     * 
     * @param pose 
     * @return int neighbor live cell count
     */
    int CheckLiveNeighborsCount(Position pose) const;

    /**
     * @brief Update the game to get next frame
     * 
     */
    void Update();
};