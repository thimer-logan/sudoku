#pragma once

#include <iostream>
#include <set>

struct Point {
    int x;
    int y;
};

inline bool operator==(const Point &lhs, const Point &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator<(const Point &lhs, const Point &rhs) {
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}

class Cell {

public:
    Cell(int x, int y);
    Cell(int x, int y, int value);
    Cell(Point point);

    // Copy constructor
    Cell(const Cell& other);

    // Move constructor
    Cell(Cell&& other) noexcept;

    Cell& operator=(Cell&& other) noexcept;

    int get_value() const;
    void set_value(int value);

    Point get_location() const;

    std::set<Point> get_neighbours() const;

    friend std::ostream& operator<<(std::ostream& os, const Cell& cell);

private:
    int _value = 0;
    Point _location;
    std::set<Point> _neighbours;


    void generate_neighbours();

};

std::ostream& operator<<(std::ostream& os, const Cell& cell);
