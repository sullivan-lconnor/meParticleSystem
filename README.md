# meParticleSystem

This makes a simple particle simulation system in c++ and uses a pyQT5 display to show the positions
of the particles.  The python display simply calls the python update function to update the positions
of all the initialized particles.  As of now particles only react to their own initialized position 
and velocity data.

## Implementation  
Use pyBind11 to connect a c++ particle simulation system to a python QT display.

## Installation Requirements
Requires Python 3.10.11
Compile with C++ 11.

Navigate to /src
 >> mkdir build
 >> cd build
 >> cmake ..
 >> make

To run:
 >> python main.py

More simulation modes / tools to come!