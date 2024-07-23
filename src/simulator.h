/*
 * Initializes a simulation with a given number of particles and recieves command control requests 
 *  From python
*/

#ifndef SIMULATOR
#define SIMULATOR

#include "particle.h"

#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>


class Simulator {
protected:
    std::string _name;
    int _mode;
    std::vector<Particle> _points;

public:
// Constructors Setters / Getters
    Simulator(std::string name, int mode) : _name(name), _mode(mode) {
        switch ( _mode )
        {
        case 1:
            // Does nothing, simulator awaits manual intervention
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
    void addParticle(double x_pos, double y_pos, double dx, double dy) {
        _points.push_back(Particle(x_pos, y_pos, dx, dy));
    }

    void runTicks(int ticks) {
        for (auto& p : _points) { 
            p.move(ticks);
        }
    }
};

#endif // SIMULATOR