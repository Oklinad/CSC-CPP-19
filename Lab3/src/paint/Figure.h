#ifndef LAB3_FIGURE_H
#define LAB3_FIGURE_H


class Figure {
protected:
    long long int id;
    int color;
    double x, y;
public:
    Figure(long long int id, int color, double x, double y);

    void set_color(int color);

    int getColor() const;

    void move(double dx, double dy);

    virtual ~Figure();

    virtual void scale(double scale) {};

    virtual bool in_figure(double nx, double ny) { return false; };
};

class Circle : public Figure {
    double radius;
public:
    Circle(long long int id, int color, double x, double y, double radius);

    void scale(double scale) override;

    bool in_figure(double nx, double ny) override;
};

class Rectangle : public Figure {
    double w, h;
public:
    Rectangle(long long int id, int color, double x, double y, double w, double h);

    void scale(double scale) override;

    bool in_figure(double nx, double ny) override;
};

class Square : public Figure {
    double side;
public:
    Square(long long int id, int color, double x, double y, double side);

    void scale(double scale) override;

    bool in_figure(double nx, double ny) override;
};

class Triangle : public Figure {
    double a, b;
public:
    Triangle(long long int id, int color, double x, double y, double a, double b);

    void scale(double scale) override;

    bool in_figure(double nx, double ny) override;
};


#endif //LAB3_FIGURE_H
