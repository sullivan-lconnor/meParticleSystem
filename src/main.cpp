#include "particle.h"
#include "simulator.h"

#include <iostream>



int main() {
    Simulator a("test", 1);
    a.addParticle(0,0,1,1);
    std::cout << "Point starts at 0,0 \n";
    for (int i = 0; i < 10; i++) {
        a.runTicks(1);
    }
    std::cout << "Point ends at "<< std::get<0>(a.getPoints()[0]) <<","<< std::get<1>(a.getPoints()[0]) <<"\n";
    std::cout << "Compilation test completed!" << std::endl;    
}