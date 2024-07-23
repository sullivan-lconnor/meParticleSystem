#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "simulator.h"
#include "particle.h"

namespace py = pybind11;

PYBIND11_MODULE(simulation, m) {
    py::class_<Position>(m, "Position")
        .def(py::init<double, double>())
        .def("get_x", &Position::get_x)
        .def("get_y", &Position::get_y)
        .def("set_x", &Position::set_x)
        .def("set_y", &Position::set_y);

    py::class_<Velocity>(m, "Velocity")
        .def(py::init<double, double>())
        .def("get_dx", &Velocity::get_dx)
        .def("get_dy", &Velocity::get_dy)
        .def("set_dx", &Velocity::set_dx)
        .def("set_dy", &Velocity::set_dy);

    py::class_<Particle>(m, "Particle")
        .def(py::init<double, double, double, double>())
        .def("get_x", &Particle::get_x)
        .def("get_y", &Particle::get_y)
        .def("get_dx", &Particle::get_dx)
        .def("get_dy", &Particle::get_dy)
        .def("get_pos", &Particle::get_pos)
        .def("move", &Particle::move);

    py::class_<Simulator>(m, "Simulator")
        .def(py::init<std::string, int>())
        .def("addParticle", &Simulator::addParticle)
        .def("runTicks", &Simulator::runTicks)
        .def("getPoints", &Simulator::getPoints);
}
