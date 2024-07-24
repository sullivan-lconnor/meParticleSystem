/*
 * Initializes a simulation with a given number of particles and recieves command control requests 
 *  From python
*/

#ifndef SIMULATOR
#define SIMULATOR

#include "particle.h"

#include <functional>
#include <math.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

class Simulator {
protected:
    std::string _name;
    int _mode;
    std::vector<Particle> _points;
    std::function<void(double)> _run_function;
    double G_const = 10;

public:
// Constructors Setters / Getters
    Simulator(std::string name, int mode) : _name(name), _mode(mode) {
        switch ( _mode )
        {
        case 1:
            _run_function = std::bind(&Simulator::runTicks, this, std::placeholders::_1);
            break;
        
        case 2:
            _run_function = std::bind(&Simulator::runOrbitalTicks, this, std::placeholders::_1);
            break;
                
        default:
            throw std::invalid_argument( "Received mode value that does not exist" );
            break;
        }
    }    

    std::vector<std::tuple<double,double>> getPoints() {
        std::vector<std::tuple<double,double>> result;
        for (auto p : _points) {
            result.push_back(p.get_pos());
        }
        return result;
    }

public:
// Control functions
    void addParticle(double mass, double x_pos, double y_pos, double dx, double dy, double ddx, double ddy) {
        _points.push_back(Particle(mass, x_pos, y_pos, dx, dy, ddx, ddy));
    }

    void run(double ticks) {
        _run_function(ticks);
    }

    void runTicks(double ticks) {
        for (auto& p : _points) { 
            p.move(ticks);
        }
    }

    void runOrbitalTicks(double ticks) {
        //NOTE: we may need to rebuild the list if we want all the points to impel the others statically
        // Currently, points will move then impel other points after moving which isn't quite right
        for (auto& p1 : _points) {
            for (auto& p2 : _points) {
                p1.impel(ticks, get_GravImpuls(p1,p2));
            }
        }
        runTicks(ticks);
    }

// Measurement functions
    double getDistance(Particle a, Particle b) {
        return std::sqrt ( getDistance2(a,b) );
    }

    double getDistance2(Particle a, Particle b) {
        double distance = std::pow(a.get_x() - b.get_x(),2) + std::pow(a.get_y() - b.get_y(),2);
        
        // We cannot get closer than this
        if (distance < 1) { distance = 1; }

        return distance;
    }

    Acceleration get_GravImpuls(Particle a, Particle b) {
        Acceleration result;
        // Check zero distance
        if (a.get_x() == b.get_x() && a.get_y() == b.get_y()) { return result; }
        // return Acceleration 
        double A = G_const * ( a.get_mass() + b.get_mass() ) / getDistance2(a,b);

        double x_dir = (b.get_x()-a.get_x());
        double y_dir = (b.get_y()-a.get_y());
        double magnitude = std::sqrt( std::pow(x_dir, 2) + std::pow(y_dir,2) );

        double x_acc = ( A * (x_dir/magnitude) );
        double y_acc = ( A * (y_dir/magnitude) );
        
        result.set_ddx(x_acc);
        result.set_ddy(y_acc);
        return result;
    }

};

#endif // SIMULATOR