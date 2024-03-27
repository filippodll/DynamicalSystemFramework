
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "headers/Agent.hpp"
#include "headers/Itinerary.hpp"
#include "headers/Graph.hpp"
#include "headers/Node.hpp"
#include "headers/Street.hpp"

namespace py = pybind11;

using Id = uint32_t;
using Size = uint32_t;
using Node = dsm::Node<Id, Size>;
using Street = dsm::Street<Id, Size>;
using SparseMatrix = dsm::SparseMatrix<Id, bool>;
using Itinerary = dsm::Itinerary<Id>;
using Agent_i = dsm::Agent<Id, Size, int>;
using Agent_d = dsm::Agent<Id, Size, double>;
using Graph = dsm::Graph<Id, Size>;

using NodeMap = std::unordered_map<Id, std::unique_ptr<Node>>;
using StreetMap = std::unordered_map<Id, std::unique_ptr<Street>>;

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

  py::class_<Itinerary>(m, "Itinerary")
      .def(py::init<Id, Id>())
      .def(py::init<Id, Id, SparseMatrix>())
      .def("setDestination", &Itinerary::setDestination)
      .def("setPath", &Itinerary::setPath)
      .def("id", &Itinerary::id)
      .def("destination", &Itinerary::destination)
      .def("path", &Itinerary::path);

  py::class_<Agent_d>(m, "Agent_d")
      .def(py::init<Id, Id>())
      .def(py::init<Id, Id, Id>())
      .def("setSourceNodeId", &Agent_d::setSourceNodeId)
      .def("setItineraryId", &Agent_d::setItineraryId)
      .def("setSpeed", &Agent_d::setSpeed)
      .def("incrementDelay", py::overload_cast<>(&Agent_d::incrementDelay))
      .def("incrementDelay", py::overload_cast<double>(&Agent_d::incrementDelay))
      .def("decrementDelay", &Agent_d::decrementDelay)
      .def("incrementDistance", py::overload_cast<>(&Agent_d::incrementDistance))
      .def("incrementDistance", py::overload_cast<double>(&Agent_d::incrementDistance))
      .def("incrementTime", py::overload_cast<>(&Agent_d::incrementTime))
      .def("incrementTime", py::overload_cast<unsigned int>(&Agent_d::incrementTime))
      /* .def("resetTime", &Agent_d::resetTime) */
      .def("id", &Agent_d::id)
      .def("itineraryId", &Agent_d::itineraryId)
      .def("streetId", &Agent_d::streetId)
      .def("srcNodeId", &Agent_d::srcNodeId)
      .def("speed", &Agent_d::speed)
      .def("delay", &Agent_d::delay)
      .def("distance", &Agent_d::distance)
      .def("time", &Agent_d::time);

  py::class_<Agent_i>(m, "Agent_i")
      .def(py::init<Id, Id>())
      .def(py::init<Id, Id, Id>())
      .def("setSourceNodeId", &Agent_i::setSourceNodeId)
      .def("setItineraryId", &Agent_i::setItineraryId)
      .def("setSpeed", &Agent_i::setSpeed)
      .def("incrementDelay", py::overload_cast<>(&Agent_i::incrementDelay))
      .def("incrementDelay", py::overload_cast<int>(&Agent_i::incrementDelay))
      .def("decrementDelay", &Agent_i::decrementDelay)
      .def("incrementDistance", py::overload_cast<>(&Agent_i::incrementDistance))
      .def("incrementDistance", py::overload_cast<double>(&Agent_i::incrementDistance))
      .def("incrementTime", py::overload_cast<>(&Agent_i::incrementTime))
      .def("incrementTime", py::overload_cast<unsigned int>(&Agent_i::incrementTime))
      /* .def("resetTime", &Agent_i::resetTime) */
      .def("id", &Agent_i::id)
      .def("itineraryId", &Agent_i::itineraryId)
      .def("streetId", &Agent_i::streetId)
      .def("srcNodeId", &Agent_i::srcNodeId)
      .def("speed", &Agent_i::speed)
      .def("delay", &Agent_i::delay)
      .def("distance", &Agent_i::distance)
      .def("time", &Agent_i::time);

  py::class_<Graph>(m, "Graph")
	.def(py::init<>())
	.def(py::init<const SparseMatrix&>())
	.def(py::init<const StreetMap&>())
	.def(py::init<const Graph&>())
	.def(py::init<Graph&&>())
	.def("buildAdj", &Graph::buildAdj)
	.def("buildStreetAngles", &Graph::buildStreetAngles)
	.def("importMatrix", &Graph::importMatrix)
	.def("importCoordinates", &Graph::importCoordinates)
	.def("importOSMNodes", &Graph::importOSMNodes)
	.def("importOSMEdges", &Graph::importOSMEdges)
	.def("exportMatrix", &Graph::exportMatrix)
	/* .def("addNode", py::overload_cast<std::unique_ptr<Node>>(&Graph::addNode) */
	/* .def("addNode", py::overload_cast<const Node&>(&Graph::addNode) */
	/* .def("addStreet", py::overload_cast<std::unique_ptr<Street>>(&Graph::addStreet) */
	/* .def("addStreet", py::overload_cast<const Street&>(&Graph::addStreet) */
	.def("adjMatrix", &Graph::adjMatrix)
	.def("nodeSet", py::overload_cast<>(&Graph::nodeSet))
	.def("nodeSet", py::overload_cast<>(&Graph::nodeSet), py::const_)
	.def("streetSet", py::overload_cast<>(&Graph::streetSet))
	.def("streetSet", py::overload_cast<>(&Graph::streetSet), py::const_)
	.def("street", &Graph::street);
	/* .def("shortestPath", py::overload_cast<const Node&, const Node&>(&Graph::shortestPath)) */
	/* .def("shortestPath", py::overload_cast<Id, Id>(&Graph::shortestPath)); */
}
