#include <boost/python.hpp>

#include "../flameSolver.h"

using namespace boost::python;

void exportFlameSolver()
{
    class_<FlameSolver, boost::noncopyable>("FlameSolver")
        .def(init<object>())
        .def("initialize", &FlameSolver::initialize)
        .def("run", &FlameSolver::tryrun)
        .def("writeStateFile", &FlameSolver::writeStateFile)
        .def("writeTimeseriesFile", &FlameSolver::writeTimeseriesFile)
        .def_readonly("timeVector", &FlameSolver::timeVector)
        .def_readonly("heatReleaseRate", &FlameSolver::heatReleaseRate)
        .def_readonly("consumptionSpeed", &FlameSolver::consumptionSpeed)
        .def_readonly("flamePosition", &FlameSolver::flamePosition)
        ;
}