#include "Scene.h"

bool Scene::contain_figure(long long int id) const {
    return figures.count(id) > 0;
}

void Scene::create_circle(long long int id, int color, double x, double y, double radius) {
    figures[id] = std::make_unique<Circle>(id, color, x, y, radius);
    queue.push_back(id);
}

void Scene::create_rectangle(long long int id, int color, double x, double y, double w, double h) {
    figures[id] = std::make_unique<Rectangle>(id, color, x, y, w, h);
    queue.push_back(id);
}

void Scene::create_square(long long int id, int color, double x, double y, double side) {
    figures[id] = std::make_unique<Square>(id, color, x, y, side);
    queue.push_back(id);
}

void Scene::create_triangle(long long int id, int color, double x, double y, double a, double b) {
    figures[id] = std::make_unique<Triangle>(id, color, x, y, a, b);
    queue.push_back(id);
}

void Scene::set_color(long long int id, int color) {
    figures[id]->set_color(color);
}

void Scene::move(long long int id, double dx, double dy) {
    figures[id]->move(dx, dy);
}

void Scene::scale(long long int id, double scale) {
    figures[id]->scale(scale);
}

void Scene::bring_to_back(long long int id) {
    auto it = std::find(queue.begin(), queue.end(), id);
    std::rotate(queue.begin(), it, it + 1);
}

void Scene::bring_to_front(long long int id) {
    auto it = std::find(queue.begin(), queue.end(), id);
    std::rotate(it, it + 1, queue.end());
}

void Scene::draw(std::ofstream &f, double scene_x, double scene_y, double scene_w, double scene_h, int width,
                 int height) {
    canvas = std::vector<std::vector<char>>(height, std::vector<char>(width, colors[1]));
    for (int i = 0; i < height; ++i) {
        coor_y.push_back(scene_y + (i + 0.5) * scene_h / height);
    }
    for (int i = 0; i < width; ++i) {
        coor_x.push_back(scene_x + (i + 0.5) * scene_w / width);
    }
    for (long long int id : queue) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (figures[id]->in_figure(coor_x[j], coor_y[i])) {
                    canvas[height - 1 - i][j] = colors[figures[id]->getColor()];
                }
            }
        }
    }

    for (const std::vector<char> &v : canvas) {
        for (char c : v) {
            f << c;
        }
        f << std::endl;
    }
    f.close();
}

const std::vector<std::vector<char>> &Scene::get_canvas() const {
    return canvas;
}
