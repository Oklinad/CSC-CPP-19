#ifndef LAB3_PARSER_H
#define LAB3_PARSER_H

#include "Scene.h"
#include <string>
#include <sstream>

static class Parser {
    static long long int get_id(const std::string& command, const std::string &s);

    static int get_color(const std::string& command, const std::string &s);

    static double get_scale(const std::string& command, const std::string &s);

    static double get_coor(const std::string& command, const std::string &s);

    static double get_side(const std::string& command, const std::string &s, const std::string &parameter);

    static int get_int_side(const std::string& command, const std::string &s, const std::string &parameter);

    static void check_figure(const std::string &command, const Scene &scene, long long int id);

    static void figure_exist(const std::string &command, const Scene &scene, long long int id);
public:
    static void execute_command(Scene &scene, const std::string& command);

} parser;


#endif //LAB3_PARSER_H
