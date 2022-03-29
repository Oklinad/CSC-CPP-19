#ifndef LAB3_SCENE_H
#define LAB3_SCENE_H


#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <memory>
#include "Figure.h"

class Scene {
    char colors[4] = {' ', '.', 'o', '*'};
    std::vector<long long int> queue;
    std::map<long long int, std::unique_ptr<Figure>> figures;
    std::vector<std::vector<char>> canvas;
    std::vector<double> coor_x, coor_y;

public:

    const std::vector<std::vector<char>> &get_canvas() const;

    bool contain_figure(long long int id) const;

    void create_circle(long long int id, int color, double x, double y, double radius);

    void create_rectangle(long long int id, int color, double x, double y, double w, double h);

    void create_square(long long int id, int color, double x, double y, double side);

    void create_triangle(long long int id, int color, double x, double y, double a, double b);

    void set_color(long long int id, int color);

    void move(long long int id, double dx, double dy);

    void scale(long long int id, double scale);

    void bring_to_back(long long int id);

    void bring_to_front(long long int id);

    void draw(std::ofstream &f, double scene_x, double scene_y, double scene_w, double scene_h, int width, int height);
};


#endif //LAB3_SCENE_H
