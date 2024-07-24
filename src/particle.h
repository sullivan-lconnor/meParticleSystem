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

struct Acceleration {
    double _ddx;
    double _ddy;

    Acceleration(double ddx, double ddy) : _ddx(ddx), _ddy(ddy) {}
    Acceleration() : _ddx(0.0), _ddy(0.0) {}

    void set_ddx(double ddx) { _ddx = ddx; }
    void set_ddy(double ddy) { _ddy = ddy; }
    double get_ddx() const { return _ddx; }
    double get_ddy() const { return _ddy; }
};

class Particle {
protected:
    double _mass;
    Position _pos;
    Velocity _vos;
    Acceleration _acc;

public:

    // Default Constructor
    Particle() : _mass(0.0), _pos(Position(0,0)), _vos(Velocity(0,0)), _acc(Acceleration(0,0)) {};

    // Pos Constructor
    Particle(double mass, double x, double y) : _mass(mass), _pos(Position(x,y)), _vos(Velocity(0,0)), _acc(Acceleration(0,0)) {};

    // Pos Vel Constructor
    Particle(double mass, double x, double y, double dx, double dy) : _mass(mass), _pos(Position(x,y)), _vos(Velocity(dx,dy)), _acc(Acceleration(0,0)) {};

    // Pos Vel Acc Constructor
    Particle(double mass, double x, double y, double dx, double dy, double ddx, double ddy) : _mass(mass), _pos(Position(x,y)), _vos(Velocity(dx,dy)), _acc(Acceleration(ddx,ddy)) {};

    // Getters / Setters
    double get_mass() const { return _mass; }
    double get_x() const { return _pos.get_x(); }
    double get_y() const { return _pos.get_y(); }
    double get_dx() const { return _vos.get_dx(); }
    double get_dy() const { return _vos.get_dy(); }
    double get_ddx() const { return _acc.get_ddx(); }
    double get_ddy() const { return _acc.get_ddy(); }

    void set_mass(double mass) { _mass = mass; }

    std::tuple<double, double> get_pos() const { return std::make_tuple(get_x(), get_y()); }

public:
    // Control functions
    
    /*
    * Moves particle _pos by _vos based on given number of ticks
    */
    void move(double ticks) {
        impel(ticks);
        _pos.set_x( get_x() + (get_dx() * ticks) );
        _pos.set_y( get_y() + (get_dy() * ticks) );
    }

    /*
    * Alters velocity of particle based on given acceleration
    */
    void impel(double ticks) {
        _vos.set_dx( get_dx() + (get_ddx() * ticks) );
        _vos.set_dy( get_dy() + (get_ddy() * ticks) );
    }

    void impel(double ticks, Acceleration a) {
        _vos.set_dx( get_dx() + (a.get_ddx() * ticks) );
        _vos.set_dy( get_dy() + (a.get_ddy() * ticks) );
    }

};

#endif //PARTICLE
