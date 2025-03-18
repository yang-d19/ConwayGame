#include <vector>

#include "controller.hpp"

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

void DemoGliderPattern() {

    Controller controller;
    controller.SetInitPattern(glider_pattern_init);
    controller.SetGameParameter({
        20,
        400
    });
    controller.SetDisplayerParameter({
        -1,
        -1,
        10,
        10,
        true,
        false
    });

    controller.Run();
}

void DemoToadPattern() {

    Controller controller;
    controller.SetInitPattern(toad_pattern_init);
    controller.SetGameParameter({
        -1,
        500
    });
    controller.SetDisplayerParameter({
        -1,
        -1,
        8,
        8,
        true,
        true
    });

    controller.Run();
}

void DempGosperGliderGun() {
    const std::string in_filename = "data/gosper_glider_gun.txt";
    const std::string out_filename = "data/gosper_glider_gun-out.txt";

    Controller controller;
    controller.LoadUniverseFromFile(in_filename);
    controller.SetGameParameter({
        200,
        100
    });
    controller.SetDisplayerParameter({
        -1,
        -1,
        8,
        8,
        true,
        true
    });

    controller.Run();

    controller.SaveUniverseToFile(out_filename);
}

int main(void) {

    // DemoGliderPattern();

    DempGosperGliderGun();

    // DemoToadPattern();

    return 0;
}