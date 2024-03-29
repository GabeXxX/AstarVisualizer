//
// Created by Gabriele Bruni on 2019-07-30.
//


#include "Grid.h"


Grid::Grid(int width, int height) : width(width), height(height) {
}

bool Grid::inBounds(GridLocation id) const {
    return 0 <= id.getX() && id.getX() < width
           && 0 <= id.getY() && id.getY() < height;
}

bool Grid::passable(GridLocation id) const {
    return walls.find(id) == walls.end();
}

std::vector<GridLocation> Grid::neighbors(GridLocation id) const {
    std::vector<GridLocation> results;

    for (GridLocation dir : DIRS) {
        GridLocation next{id.getX() + dir.getX(), id.getY() + dir.getY()};
        if (inBounds(next) && passable(next)) {
            results.push_back(next);
        }
    }

    if ((id.getX() + id.getY()) % 2 == 0) {
        // aesthetic improvement on square grids
        std::reverse(results.begin(), results.end());
    }

    return results;

}

double Grid::cost(GridLocation from_node, GridLocation to_node) const {
    return forests.find(to_node) != forests.end() ? 5 : 1;
}

void Grid::setWalls(GridLocation loc) {
    walls.insert(loc);

}

void Grid::setForests(GridLocation loc) {
    forests.insert(loc);

}

std::array<GridLocation, 4> Grid::DIRS =
        {GridLocation{1, 0}, GridLocation{0, -1}, GridLocation{-1, 0}, GridLocation{0, 1}};


