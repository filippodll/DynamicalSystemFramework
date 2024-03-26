
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "headers/Node.hpp"
#include "headers/Street.hpp"

namespace py = pybind11;

using Id = uint32_t;
using Size = uint32_t;
using Node = dsm::Node<Id, Size>;
using Street = dsm::Street<Id, Size>;

PYBIND11_MODULE(dsm, m) {
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

  py::class_<Street>(m, "Street")
      .def(py::init<Id, const Street&>())
      .def(py::init<Id, std::pair<Id, Id>>())
      .def(py::init<Id, Size, double, std::pair<Id, Id>>())
      .def(py::init<Id, Size, double, double, std::pair<Id, Id>>())
      .def("setId", &Street::setId)
      .def("setCapacity", &Street::setCapacity)
      .def("setTransportCapacity", &Street::setTransportCapacity)
      .def("setLength", &Street::setLength)
      .def("setQueue", &Street::setQueue)
      .def("setNodePair", py::overload_cast<Id, Id>(&Street::setNodePair))
      .def("setNodePair",
           py::overload_cast<const Node&, const Node&>(&Street::setNodePair))
      .def("setNodePair", py::overload_cast<std::pair<Id, Id>>(&Street::setNodePair))
      .def("setMaxSpeed", &Street::setMaxSpeed)
      .def("setAngle",
           py::overload_cast<std::pair<double, double>, std::pair<double, double>>(
               &Street::setAngle))
      .def("setAngle", py::overload_cast<double>(&Street::setAngle))
      .def("id", &Street::id)
      .def("capacity", &Street::capacity)
      .def("transportCapacity", &Street::transportCapacity)
      .def("length", &Street::length)
      .def("queue", &Street::queue)
      .def("nodePair", &Street::nodePair)
      .def("density", &Street::density)
      .def("maxSpeed", &Street::maxSpeed)
      .def("angle", &Street::angle)
      .def("enqueue", &Street::enqueue)
      .def("dequeue", &Street::dequeue)
      .def("isSpire", &Street::isSpire);
}
