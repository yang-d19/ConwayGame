#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

#include "game.hpp"

void Game::Reset() {
    cell_live_set_.clear();
    step_cnt_ = 0;
}

void Game::SetInitLiveCells(const std::vector<Position>& live_cell_poses) {
    for (auto& pose : live_cell_poses) {
        cell_live_set_.insert(pose);
    }
}

std::unordered_set<Position> Game::GetAffectedPoses() const {
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

const std::unordered_set<Position>& Game::GetCellLiveSet() const {
    return cell_live_set_;
}

bool Game::IsCellLive(Position pose) const {
    return cell_live_set_.find(pose) != cell_live_set_.end();
}

int Game::CheckLiveNeighborsCount(Position pose) const {
    int cnt = 0;
    for (auto& neighbor_pose : pose.GetNeighbors()) {
        if (IsCellLive(neighbor_pose)) {
            cnt++;
        }
    }
    return cnt;
}

void Game::Update() {
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

void Game::Show(bool dynamic_fit_window_start, 
                bool dynamic_fit_window_size, 
                const std::string& msg) {
    if (dynamic_fit_window_start) {
        dispayer_.DynamicFitWindow(*this, dynamic_fit_window_size);
    }
    dispayer_.Show(*this);
    std::cout << "--------------------" << std::endl;
    std::cout << msg << std::endl;
}

/**
 * If max_step < 0, run infinite steps
 */
void Game::Run(int max_step, 
              int interval_ms, 
              int display_width_x, 
              int display_width_y, 
              bool dynamic_fit_window_start, 
              bool dynamic_fit_window_size) {

    dispayer_.SetWindowStart(-1, -1);
    dispayer_.SetWindowSize(display_width_x, display_width_y);

    while (max_step < 0 || step_cnt_ <= max_step) {
        std::stringstream msg_ss;
        msg_ss << std::fixed << std::setprecision(2);
        msg_ss << "step: " << step_cnt_ << " / " << (max_step >= 0 ? std::to_string(max_step) : "INF") << std::endl;
        msg_ss << "freq: " << 1000.0 / interval_ms << " Hz" << std::endl;
        msg_ss << "live cell count: " << cell_live_set_.size() << std::endl;

        auto [start_x, start_y] = dispayer_.GetWindowStart();
        auto [size_x, size_y ] = dispayer_.GetWindowSize();
        msg_ss << "window start: [" << start_x << ", " << start_y << "]" << std::endl;
        msg_ss << "window size: [" << size_x << ", " << size_y << "]" << std::endl;

        Show(dynamic_fit_window_start, dynamic_fit_window_size, msg_ss.str());
        Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
        step_cnt_++;
    }
}