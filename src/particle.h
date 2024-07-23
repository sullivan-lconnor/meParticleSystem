/*
 * Defines a basic particle
*/
#ifndef PARTICLE
#define PARTICLE

#include <tuple>
#include <iostream>

struct Position {
    double _x;
    double _y;

    Position(double x, double y) : _x(x), _y(y) {}
    Position() : _x(0.0), _y(0.0) {}

    void set_x(double x) { _x = x; }
    void set_y(double y) { _y = y; }
    double get_x() const { return _x; }
    double get_y() const { return _y; }
};

struct Velocity {
    double _dx;
    double _dy;

    Velocity(double dx, double dy) : _dx(dx), _dy(dy) {}
    Velocity() : _dx(0.0), _dy(0.0) {}

    void set_dx(double dx) { _dx = dx; }
    void set_dy(double dy) { _dy = dy; }
    double get_dx() const { return _dx; }
    double get_dy() const { return _dy; }

};

class Particle {
protected:
    Position _pos;
    Velocity _vos;
public:
    // Getters / Setters
    Particle() : _pos(Position(0,0)), _vos(Velocity(0,0)) {};
    Particle(double x, double y, double dx, double dy) : _pos(Position(x,y)), _vos(Velocity(dx,dy)) {};

    double get_x() const { return _pos.get_x(); }
    double get_y() const { return _pos.get_y(); }
    double get_dx() const { return _vos.get_dx(); }
    double get_dy() const { return _vos.get_dy(); }

    std::tuple<double, double> get_pos() const { return std::make_tuple(get_x(), get_y()); }

public:
    // Control functions
    
    /*
    * Moves particle _pos by _vos based on given number of ticks
    */
    void move(int ticks) {
        _pos.set_x( get_x() + (get_dx() * ticks) );
        _pos.set_y( get_y() + (get_dy() * ticks) );
    }

};

#endif //PARTICLE
