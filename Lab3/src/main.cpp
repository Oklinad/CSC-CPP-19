#include <iostream>
#include <cstring>

#include "paint/Scene.h"
#include "paint/Parser.h"


int main(int argc, char *argv[]) {
    std::string help = "HELP:\n"
                       "Interpreter of text files describing commands over 2D figures.\n"
                       "Usage:\n"
                       "./interpreter -help\n"
                       "./interpreter <filename>\n\n"
                       "List of commands:\n"
                       "    create circle <id> <color> <x> <y> <radius>\n"
                       "    create rectangle <id> <color> <x> <y> <w> <h>\n"
                       "    create square <id> <color> <x> <y> <side>\n"
                       "    create triangle <id> <color> <x> <y> <a> <b>\n"
                       "    set color <id> <color>\n"
                       "    move <id> <dx> <dy>\n"
                       "    scale <id> <scale>\n"
                       "    bring to back <id>\n"
                       "    bring to front <id>\n"
                       "    draw <filename> <scene_x> <scene_y> <scene_w> <scene_h> <width> <height>";

    if (argc == 2) {
        if (std::strcmp(argv[1], "-help") == 0) {
            std::cout << help << std::endl;
        } else {
            std::ifstream file(argv[1]);
            if (file.is_open()) {
                Scene scene = Scene();
                std::string command;
                try {
                    while (getline(file, command))
                        Parser::execute_command(scene, command);
                } catch (const std::invalid_argument &a) {
                    std::cerr << a.what() << std::endl;
                    return 1;
                }
                file.close();
            } else {
                std::cerr << "Can not open file \"" << argv[1] << "\"!" << std::endl;
                return 1;
            }
        }
    } else {
        std::cerr << "The program needs the path to the file with the code!\n" << help << std::endl;
        return 1;
    }
    return 0;
}
