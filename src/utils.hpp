#pragma once

#include <vector>

struct Position {
    int x;
    int y;

    Position(int x=0, int y=0) : x(x), y(y) {}

    // required for std::unordered_set
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    std::vector<Position> GetNeighbors() const {
        std::vector<Position> result;
        result.reserve(8);
        for (int nx = x - 1; nx <= x + 1; nx++) {
            for (int ny = y - 1; ny <= y + 1; ny++) {
                // exclude self position
                if (nx == x && ny == y) {
                    continue;
                }
                result.push_back(Position(nx, ny));
            }
        }
        return result;
    }
};

// required for std::unordered_set
namespace std {
    template <>
    struct hash<Position> {
        size_t operator()(const Position& p) const {
            return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
        }
    };
}
