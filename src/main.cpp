#include "particle.h"
#include "simulator.h"

#include <iostream>



int main() {
    Simulator a("test", 1);
    a.addParticle(1,1,0,1,0,0,0);
    std::cout << "Point Starts at "<< std::get<0>(a.getPoints()[0]) <<","<< std::get<1>(a.getPoints()[0]) <<"\n";

    for (int i = 0; i < 10; i++) {
        a.run(0.1);
        std::cout<<std::get<0>(a.getPoints()[0])<<std::endl;
    }
    std::cout << "Point ends at "<< std::get<0>(a.getPoints()[0]) <<","<< std::get<1>(a.getPoints()[0]) <<"\n";
    std::cout << "Compilation test completed!" << std::endl;    
}