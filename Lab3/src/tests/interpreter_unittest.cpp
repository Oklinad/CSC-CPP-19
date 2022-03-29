#include "gtest/gtest.h"

#include "paint/Parser.h"
#include "paint/Scene.h"

#include <string>


TEST(polynom, create_circle) {
    Scene scene = Scene();
    Parser::execute_command(scene, "create circle 1 2 3 3 2");
    Parser::execute_command(scene, "draw test.txt 0 0 6 6 6 6");

    std::vector<std::string> my_str = {"......",
                                       "..oo..",
                                       ".oooo.",
                                       ".oooo.",
                                       "..oo..",
                                       "......"};
    std::vector<std::vector<char>> my_canvas;
    for (auto s : my_str) {
        std::vector<char> vec(s.begin(), s.end());
        my_canvas.push_back(vec);
    }

    EXPECT_EQ(my_canvas, scene.get_canvas());
}

TEST(polynom, create_rectangle) {
    Scene scene = Scene();
    Parser::execute_command(scene, "create rectangle 1 2 1 1 2 3");
    Parser::execute_command(scene, "draw test.txt 0 0 6 6 6 6");

    std::vector<std::string> my_str = {"......",
                                       "......",
                                       ".oo...",
                                       ".oo...",
                                       ".oo...",
                                       "......"};
    std::vector<std::vector<char>> my_canvas;
    for (auto s : my_str) {
        std::vector<char> vec(s.begin(), s.end());
        my_canvas.push_back(vec);
    }

    EXPECT_EQ(my_canvas, scene.get_canvas());
}

TEST(polynom, create_square) {
    Scene scene = Scene();
    Parser::execute_command(scene, "create square 1 2 1 1 3");
    Parser::execute_command(scene, "draw test.txt 0 0 6 6 6 6");

    std::vector<std::string> my_str = {"......",
                                       "......",
                                       ".ooo..",
                                       ".ooo..",
                                       ".ooo..",
                                       "......"};
    std::vector<std::vector<char>> my_canvas;
    for (auto s : my_str) {
        std::vector<char> vec(s.begin(), s.end());
        my_canvas.push_back(vec);
    }

    EXPECT_EQ(my_canvas, scene.get_canvas());
}

TEST(polynom, create_triangle) {
    Scene scene = Scene();
    Parser::execute_command(scene, "create triangle 1 2 1 1 3 3");
    Parser::execute_command(scene, "draw test.txt 0 0 6 6 6 6");

    std::vector<std::string> my_str = {"......",
                                       "......",
                                       ".o....",
                                       ".oo...",
                                       ".ooo..",
                                       "......"};
    std::vector<std::vector<char>> my_canvas;
    for (auto s : my_str) {
        std::vector<char> vec(s.begin(), s.end());
        my_canvas.push_back(vec);
    }

    EXPECT_EQ(my_canvas, scene.get_canvas());
}

TEST(polynom, set_color) {
    Scene scene = Scene();
    Parser::execute_command(scene, "create rectangle 1 2 1 1 2 2");
    Parser::execute_command(scene, "set color 1 3");
    Parser::execute_command(scene, "draw test.txt 0 0 6 6 6 6");

    std::vector<std::string> my_str = {"......",
                                       "......",
                                       "......",
                                       ".**...",
                                       ".**...",
                                       "......"};
    std::vector<std::vector<char>> my_canvas;
    for (auto s : my_str) {
        std::vector<char> vec(s.begin(), s.end());
        my_canvas.push_back(vec);
    }

    EXPECT_EQ(my_canvas, scene.get_canvas());
}

TEST(polynom, scale) {
    Scene scene = Scene();
    Parser::execute_command(scene, "create rectangle 1 2 1 1 2 2");
    Parser::execute_command(scene, "scale 1 2");
    Parser::execute_command(scene, "draw test.txt 0 0 6 6 6 6");

    std::vector<std::string> my_str = {"......",
                                       "......",
                                       "oooo..",
                                       "oooo..",
                                       "oooo..",
                                       "oooo.."};
    std::vector<std::vector<char>> my_canvas;
    for (auto s : my_str) {
        std::vector<char> vec(s.begin(), s.end());
        my_canvas.push_back(vec);
    }

    EXPECT_EQ(my_canvas, scene.get_canvas());
}

TEST(polynom, move) {
    Scene scene = Scene();
    Parser::execute_command(scene, "create rectangle 1 2 1 1 2 2");
    Parser::execute_command(scene, "move 1 2 2");
    Parser::execute_command(scene, "draw test.txt 0 0 6 6 6 6");

    std::vector<std::string> my_str = {"......",
                                       "...oo.",
                                       "...oo.",
                                       "......",
                                       "......",
                                       "......"};
    std::vector<std::vector<char>> my_canvas;
    for (auto s : my_str) {
        std::vector<char> vec(s.begin(), s.end());
        my_canvas.push_back(vec);
    }

    EXPECT_EQ(my_canvas, scene.get_canvas());
}

TEST(polynom, two_rectangle) {
    Scene scene = Scene();
    Parser::execute_command(scene, "create rectangle 1 2 1 1 4 4");
    Parser::execute_command(scene, "create rectangle 2 3 1 1 2 2");
    Parser::execute_command(scene, "draw test.txt 0 0 6 6 6 6");

    std::vector<std::string> my_str = {"......",
                                       ".oooo.",
                                       ".oooo.",
                                       ".**oo.",
                                       ".**oo.",
                                       "......"};
    std::vector<std::vector<char>> my_canvas;
    for (auto s : my_str) {
        std::vector<char> vec(s.begin(), s.end());
        my_canvas.push_back(vec);
    }

    EXPECT_EQ(my_canvas, scene.get_canvas());
}

TEST(polynom, bring_to_back) {
    Scene scene = Scene();
    Parser::execute_command(scene, "create rectangle 1 2 1 1 4 4");
    Parser::execute_command(scene, "create rectangle 2 3 1 1 2 2");
    Parser::execute_command(scene, "bring to back 2");
    Parser::execute_command(scene, "draw test.txt 0 0 6 6 6 6");

    std::vector<std::string> my_str = {"......",
                                       ".oooo.",
                                       ".oooo.",
                                       ".oooo.",
                                       ".oooo.",
                                       "......"};
    std::vector<std::vector<char>> my_canvas;
    for (auto s : my_str) {
        std::vector<char> vec(s.begin(), s.end());
        my_canvas.push_back(vec);
    }

    EXPECT_EQ(my_canvas, scene.get_canvas());
}

TEST(polynom, bring_to_front) {
    Scene scene = Scene();

    Parser::execute_command(scene, "create rectangle 2 3 1 1 2 2");
    Parser::execute_command(scene, "create rectangle 1 2 1 1 4 4");
    Parser::execute_command(scene, "bring to front 2");
    Parser::execute_command(scene, "draw test.txt 0 0 6 6 6 6");

    std::vector<std::string> my_str = {"......",
                                       ".oooo.",
                                       ".oooo.",
                                       ".**oo.",
                                       ".**oo.",
                                       "......"};
    std::vector<std::vector<char>> my_canvas;
    for (auto s : my_str) {
        std::vector<char> vec(s.begin(), s.end());
        my_canvas.push_back(vec);
    }

    EXPECT_EQ(my_canvas, scene.get_canvas());
}