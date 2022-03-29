#include "Parser.h"

void Parser::execute_command(Scene &scene, const std::string &command) {
    std::istringstream ss(command);
    std::string s;
    ss >> s;
    if (s == "create") {
        ss >> s;
        if (s == "circle") {
            ss >> s;
            long long int id = get_id(command, s);
            ss >> s;
            int color = get_color(command, s);
            ss >> s;
            double x = get_coor(command, s);
            ss >> s;
            double y = get_coor(command, s);
            ss >> s;
            double radius = get_side(command, s, "radius");
            check_figure(command, scene, id);
            scene.create_circle(id, color, x, y, radius);
        } else if (s == "rectangle") {
            ss >> s;
            long long int id = get_id(command, s);
            ss >> s;
            int color = get_color(command, s);
            ss >> s;
            double x = get_coor(command, s);
            ss >> s;
            double y = get_coor(command, s);
            ss >> s;
            double w = get_side(command, s, "w");
            ss >> s;
            double h = get_side(command, s, "h");
            check_figure(command, scene, id);
            scene.create_rectangle(id, color, x, y, w, h);
        } else if (s == "square") {
            ss >> s;
            long long int id = get_id(command, s);
            ss >> s;
            int color = get_color(command, s);
            ss >> s;
            double x = get_coor(command, s);
            ss >> s;
            double y = get_coor(command, s);
            ss >> s;
            double side = get_side(command, s, "side");
            check_figure(command, scene, id);
            scene.create_square(id, color, x, y, side);
        } else if (s == "triangle") {
            ss >> s;
            long long int id = get_id(command, s);
            ss >> s;
            int color = get_color(command, s);
            ss >> s;
            double x = get_coor(command, s);
            ss >> s;
            double y = get_coor(command, s);
            ss >> s;
            double a = get_side(command, s, "a");
            ss >> s;
            double b = get_side(command, s, "b");
            check_figure(command, scene, id);
            scene.create_triangle(id, color, x, y, a, b);
        } else {
            throw std::invalid_argument(command + "\nDon't know this command, for more info type -help!");
        }
    } else if (s == "set") {
        ss >> s;
        if (s == "color") {
            ss >> s;
            long long int id = get_id(command, s);
            ss >> s;
            int color = get_color(command, s);
            figure_exist(command, scene, id);
            scene.set_color(id, color);
        } else {
            throw std::invalid_argument(command + "\nDon't know this command, for more info type -help!");
        }
    } else if (s == "move") {
        ss >> s;
        long long int id = get_id(command, s);
        ss >> s;
        double x = get_coor(command, s);
        ss >> s;
        double y = get_coor(command, s);
        figure_exist(command, scene, id);
        scene.move(id, x, y);
    } else if (s == "scale") {
        ss >> s;
        long long int id = get_id(command, s);
        ss >> s;
        double scale = get_scale(command, s);
        figure_exist(command, scene, id);
        scene.scale(id, scale);
    } else if (s == "bring") {
        ss >> s;
        if (s == "to") {
            ss >> s;
            if (s == "front") {
                ss >> s;
                long long int id = get_id(command, s);
                figure_exist(command, scene, id);
                scene.bring_to_front(id);
            } else if (s == "back") {
                ss >> s;
                long long int id = get_id(command, s);
                figure_exist(command, scene, id);
                scene.bring_to_back(id);
            }
        }
    } else if (s == "draw") {
        ss >> s;
        std::ofstream file(s);
        if (!file.is_open()) {
            throw std::invalid_argument(command + "\nCan not open file \"" + s + "\"!");
        }
        ss >> s;
        double scene_x = get_coor(command, s);
        ss >> s;
        double scene_y = get_coor(command, s);
        ss >> s;
        double scene_w = get_side(command, s, "scene_w");
        ss >> s;
        double scene_h = get_side(command, s, "scene_h");
        ss >> s;
        int width = get_int_side(command, s, "width");
        ss >> s;
        int height = get_int_side(command, s, "height");
        scene.draw(file, scene_x, scene_y, scene_w, scene_h, width, height);
    } else {
        throw std::invalid_argument(command + "\nDon't know this command, for more info type -help!");
    }
}

void Parser::check_figure(const std::string &command, const Scene &scene, long long int id) {
    if (scene.contain_figure(id)) {
        throw std::invalid_argument(command + "\nFigure with id = " + std::to_string(id) + " already exists!");
    }
}

void Parser::figure_exist(const std::string &command, const Scene &scene, long long int id) {
    if (!scene.contain_figure(id)) {
        throw std::invalid_argument(command + "\nFigure with id = " + std::to_string(id) + " does not exist!");
    }
}

long long int Parser::get_id(const std::string &command, const std::string &s) {
    try {
        return std::stoll(s);
    } catch (const std::invalid_argument &a) {
        throw std::invalid_argument(command + "\nCan't read <id>, for more info type -help!");
    }
}

int Parser::get_color(const std::string &command, const std::string &s) {
    int color;
    try {
        color = std::stoi(s);
    } catch (const std::invalid_argument &a) {
        throw std::invalid_argument(command + "\nCan't read <color>, for more info type -help!");
    }
    if (color < 0 || color > 3) {
        throw std::invalid_argument(command + "\n<color> must be in {0, 1, 2, 3}.");
    }
    return color;
}

double Parser::get_scale(const std::string &command, const std::string &s) {
    try {
        return std::stod(s);
    } catch (const std::invalid_argument &a) {
        throw std::invalid_argument(command + "\nCan't read <scale>, for more info type -help!");
    }
}

double Parser::get_coor(const std::string &command, const std::string &s) {
    try {
        return std::stod(s);
    } catch (const std::invalid_argument &a) {
        throw std::invalid_argument(command + "\nCan't read coordinate, for more info type -help!");
    }
}

double Parser::get_side(const std::string &command, const std::string &s, const std::string &parameter) {
    double side;
    try {
        side = std::stod(s);
    } catch (const std::invalid_argument &a) {
        throw std::invalid_argument(command + "\nCan't read <" + parameter + ">, for more info type -help!");
    }
    if (side < 0) {
        throw std::invalid_argument(command + "\n<" + parameter + "> cannot be negative.");
    }
    return side;
}

int Parser::get_int_side(const std::string &command, const std::string &s, const std::string &parameter) {
    int side;
    try {
        side = std::stoi(s);
    } catch (const std::invalid_argument &a) {
        throw std::invalid_argument(command + "\nCan't read <" + parameter + ">, for more info type -help!");
    }
    if (side < 0) {
        throw std::invalid_argument(command + "\n<" + parameter + "> cannot be negative.");
    }
    return side;
}