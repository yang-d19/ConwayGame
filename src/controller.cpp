#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>

#include "controller.hpp"

void Controller::Run() {
    displayer_.SetWindowStart(display_params_.window_start_x, display_params_.window_start_y);
    displayer_.SetWindowSize(display_params_.window_size_x, display_params_.window_size_y);

    // If max_step_cnt set to -1, run infinite steps
    // Else, run at most max_step_cnt steps
    while (game_params_.max_step_cnt < 0 || running_steps_ <= game_params_.max_step_cnt) {

        if (display_params_.dynamic_fit_window_start) {
            displayer_.DynamicFitWindow(game_, display_params_.dynamic_fit_window_size);
        }
        displayer_.ShowMainWindow(game_);
        displayer_.ShowExtraMessage(DumpDebugMsg());

        game_.Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(game_params_.frame_interval_ms));
        running_steps_++;
    }
}

std::string Controller::DumpDebugMsg() const {
    std::stringstream msg_ss;
    msg_ss << std::fixed << std::setprecision(2);
    msg_ss << "step: " << running_steps_ << " / ";
    msg_ss << (game_params_.max_step_cnt >= 0 ? std::to_string(game_params_.max_step_cnt) : "INF");
    msg_ss << std::endl;
    msg_ss << "freq: " << 1000.0 / game_params_.frame_interval_ms << " Hz" << std::endl;
    msg_ss << "live cell count: " << game_.GetCellLiveSet().size() << std::endl;

    auto [start_x, start_y] = displayer_.GetWindowStart();
    auto [size_x, size_y ] = displayer_.GetWindowSize();
    msg_ss << "window start: [" << start_x << ", " << start_y << "]" << std::endl;
    msg_ss << "window size: [" << size_x << ", " << size_y << "]" << std::endl;

    return msg_ss.str();
}

bool Controller::LoadUniverseFromFile(const std::string& file_name) {
    std::vector<Position> live_cell_poses;
    std::ifstream file(file_name);
    if (!file) {
        std::cerr << "Unable to open: " << file_name << std::endl;
        return false;
    }
    Position tmp_pose;
    while (file >> tmp_pose.x >> tmp_pose.y) {
        live_cell_poses.push_back(tmp_pose);
    }
    game_.SetInitLiveCells(live_cell_poses);
    return true;
}

bool Controller::SaveUniverseToFile(const std::string& file_name) {
    std::ofstream file(file_name);
    if (!file) {
        std::cerr << "Unable to create: " << file_name << std::endl;
        return false;
    }
    for (const auto& pos : game_.GetCellLiveSet()) {
        file << pos.x << " " << pos.y << "\n";
    }
    return true;
}
