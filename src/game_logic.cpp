#include <vector>

#include "game_logic.hpp"

void GameLogic::Reset() {
    cell_live_set_.clear();
    step_cnt_ = 0;
}

void GameLogic::SetInitLiveCells(const std::vector<Position>& live_cell_poses) {
    for (auto& pose : live_cell_poses) {
        cell_live_set_.insert(pose);
    }
}

std::unordered_set<Position> GameLogic::GetAffectedPoses() const {
    std::unordered_set<Position> affected_poses;
    for (const auto& pose : cell_live_set_) {
        for (int nx = pose.x - 1; nx <= pose.x + 1; nx++) {
            for (int ny = pose.y - 1; ny <= pose.y + 1; ny++) {
                affected_poses.insert(Position(nx, ny));
            }
        }
    }
    return affected_poses;
}

const std::unordered_set<Position>& GameLogic::GetCellLiveSet() const {
    return cell_live_set_;
}

bool GameLogic::IsCellLive(Position pose) const {
    return cell_live_set_.find(pose) != cell_live_set_.end();
}

int GameLogic::CheckLiveNeighborsCount(Position pose) const {
    int cnt = 0;
    for (auto& neighbor_pose : pose.GetNeighbors()) {
        if (IsCellLive(neighbor_pose)) {
            cnt++;
        }
    }
    return cnt;
}

void GameLogic::Update() {
    std::vector<Position> state_revert_cells;
    auto affected_poses = GetAffectedPoses();

    // ====== Main Game Logic ====== //
    for (auto& pose : affected_poses) {
        int neighbor_live_cnt = CheckLiveNeighborsCount(pose);
        if (IsCellLive(pose)) {
            if (neighbor_live_cnt < 2 || neighbor_live_cnt > 3) {
                // (3) All other live cells die in the next generation
                state_revert_cells.push_back(pose);
            }
            // (1) Any live cell with two or three live neighbors survives
        } else {
            if (neighbor_live_cnt == 3) {
                // (2) Any dead cell with exactly three live neighbors becomes a live cell
                state_revert_cells.push_back(pose);
            }
            // (3) all other dead cells stay dead
        }
    }

    for (auto& pose : state_revert_cells) {
        if (IsCellLive(pose)) {
            cell_live_set_.erase(pose);
        } else {
            cell_live_set_.insert(pose);
        }
    }
}