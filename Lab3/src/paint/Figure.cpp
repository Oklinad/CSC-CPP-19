#include "Figure.h"

Figure::Figure(long long int id, int color, double x, double y) : id(id), color(color), x(x), y(y) {}

Figure::~Figure() = default;

void Figure::set_color(int c) {
    color = c;
}

int Figure::getColor() const {
    return color;
}

void Figure::move(double dx, double dy) {
    x += dx;
    y += dy;
}


Circle::Circle(long long int id, int color, double x, double y, double radius) : Figure(id, color, x, y),
                                                                                 radius(radius) {}

void Circle::scale(double scale) {
    radius *= scale;
}

bool Circle::in_figure(double nx, double ny) {
    return ((nx - x) * (nx - x) + (ny - y) * (ny - y)) <= (radius * radius);
}


Rectangle::Rectangle(long long int id, int color, double x, double y, double w, double h) : Figure(id, color, x, y),
                                                                                            w(w), h(h) {}

void Rectangle::scale(double scale) {
    x += (1 - scale) * w / 2;
    y += (1 - scale) * h / 2;
    w *= scale;
    h *= scale;
}

bool Rectangle::in_figure(double nx, double ny) {
    return (nx >= x) && (ny >= y) && (nx - x <= w) && (ny - y <= h);
}


Square::Square(long long int id, int color, double x, double y, double side) : Figure(id, color, x, y),
                                                                               side(side) {}

void Square::scale(double scale) {
    x += (1 - scale) * side / 2;
    y += (1 - scale) * side / 2;
    side *= scale;
}

bool Square::in_figure(double nx, double ny) {
    return (nx >= x) && (ny >= y) && (nx - x <= side) && (ny - y <= side);
}


Triangle::Triangle(long long int id, int color, double x, double y, double a, double b) : Figure(id, color, x, y),
                                                                                          a(a), b(b) {}

void Triangle::scale(double scale) {
    x += (1 - scale) * a / 3;
    y += (1 - scale) * b / 3;
    a *= scale;
    b *= scale;
}

bool Triangle::in_figure(double nx, double ny) {
    return (nx >= x) && (ny >= y) && (nx - x <= a) && (ny - y <= b) && (b / a * (nx - x) <= y + b - ny);
}