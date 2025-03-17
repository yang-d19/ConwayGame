#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "game.hpp"

const std::vector<Position> toad_pattern_init = {
    {0, 1},
    {0, 2},
    {0, 3},
    {1, 0},
    {1, 1},
    {1, 2}};

const std::vector<Position> glider_pattern_init = {
    {0, 1}, 
    {1, 2}, 
    {2, 0}, 
    {2, 1}, 
    {2, 2}};

bool LoadUniverseFromFile(const std::string& file_name, std::vector<Position>& live_cell_poses) {
    std::ifstream file(file_name);
    if (!file) {
        std::cerr << "Unable to open: " << file_name << std::endl;
        return false;
    }
    Position tmp_pose;
    while (file >> tmp_pose.x >> tmp_pose.y) {
        live_cell_poses.push_back(tmp_pose);
    }
    return true;
}

bool SaveUniverseToFile(const std::string& file_name, const std::unordered_set<Position>& cell_live_set) {
    std::ofstream file(file_name);
    if (!file) {
        std::cerr << "Unable to create: " << file_name << std::endl;
        return false;
    }
    for (const auto& pos : cell_live_set) {
        file << pos.x << " " << pos.y << "\n";
    }
    return true;
}

bool DemoGliderPattern() {
    Game game;
    game.SetInitLiveCells(glider_pattern_init);
    game.Run(20, 500);
    return true;
}

bool DemoToadPattern() {
    Game game;
    game.SetInitLiveCells(toad_pattern_init);
    game.Run(-1, 500);
    return true;
}

bool DempGosperGliderGun() {
    const std::string in_filename = "data/gosper_glider_gun.txt";
    const std::string out_filename = "data/gosper_glider_gun-out.txt";

    Game game;
    std::vector<Position> live_cells_in_universe;
    bool is_loaded = LoadUniverseFromFile(in_filename, live_cells_in_universe);
    if (!is_loaded) {
        return false;
    }

    game.SetInitLiveCells(live_cells_in_universe);
    game.Run(200, 100);

    bool is_saved = SaveUniverseToFile(out_filename, game.GetCellLiveSet());
    if (!is_saved) {
        return false;
    }

    return true;
}

int main(void) {

    DemoGliderPattern();

    DempGosperGliderGun();

    DemoToadPattern();

    return 0;
}