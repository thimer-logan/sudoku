#include "Cell.h"

Cell::Cell(int x, int y) {
    _location = {x, y};
    generate_neighbours();
}

Cell::Cell(Point point) {
    _location = point;
    generate_neighbours();
}

int Cell::get_value() const {
    return _value;
}

void Cell::set_value(int value) {
    _value = value;
}

Point Cell::get_location() const {
    return _location;
}

std::set<Point> Cell::get_neighbours() const {
    return _neighbours;
}

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    os << cell.get_value();
    return os;
}

void Cell::generate_neighbours() {
    // generate row & col neighbors
    for (int n = 0; n < 9; ++n) {
        _neighbours.insert({n, _location.y});
        _neighbours.insert({_location.x, n});
    }

    auto iFloor = (_location.x / 3) * 3;
    auto jFloor = (_location.y / 3) * 3;

    // generate cell neighbors
    for (int n = iFloor; n < iFloor + 3; ++n) {
        for (int m = jFloor; m < jFloor + 3; ++m) {
            _neighbours.insert({n, m});
        }
    }
}
