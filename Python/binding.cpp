
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "headers/Node.hpp"

namespace py = pybind11;

using Id = uint32_t;
using Size = uint32_t;
using Node = dsm::Node<Id, Size>;

PYBIND11_MODULE(Node, m) {
  py::class_<Node>(m, "Node")
      .def(py::init<>())
      .def(py::init<Id>())
      .def(py::init<Id, std::pair<double, double>>())
      .def("setCoords", &Node::setCoords)
      .def("setCapacity", &Node::setCapacity)
      .def("addAgent", static_cast<void (Node::*)(Id)>(&Node::addAgent))
      .def("removeAgent", &Node::removeAgent)
      .def("setStreetPriorities", &Node::setStreetPriorities)
      .def("addStreetPriority", &Node::addStreetPriority)
      .def("id", &Node::id)
      .def("coords", &Node::coords)
      .def("streetPriorities", &Node::streetPriorities)
      .def("capacity", &Node::capacity)
      .def("agents", &Node::agents)
      .def("isFull", &Node::isFull)
      .def("agentCounter", &Node::agentCounter);
}
