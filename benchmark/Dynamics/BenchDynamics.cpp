#include <cstdint>

#include "Graph.hpp"
#include "Itinerary.hpp"
#include "Dynamics.hpp"
#include "Bench.hpp"

using Graph = dsm::Graph<uint32_t, uint32_t>;
using Itinerary = dsm::Itinerary<uint32_t>;
using Dynamics = dsm::FirstOrderDynamics<uint32_t, uint32_t, uint32_t>;

using Bench = sb::Bench<long long int>;

int main() {

  Graph graph{};
  graph.importMatrix("../test/data/matrix.dat", false);
  for (const auto &streetPair : graph.streetSet()) {
    streetPair.second->setMaxSpeed(13.9);
  }

  Itinerary it1{0, 10};
  Itinerary it2{1, 7};
  Itinerary it3{2, 4};
  Itinerary it4{3, 1};
  Itinerary it5{4, 10};
  Itinerary it6{5, 7};
  Itinerary it7{6, 4};
  Itinerary it8{7, 1};
  Itinerary it9{8, 10};
  Itinerary it10{9, 7};
  Itinerary it11{10, 4};
  Itinerary it12{11, 1};
  Itinerary it13{12, 10};
  Itinerary it14{13, 7};
  Itinerary it15{14, 4};
  Itinerary it16{15, 1};

  Dynamics dynamics{graph};
  dynamics.addItinerary(it1);
  dynamics.addItinerary(it2);
  dynamics.addItinerary(it3);
  dynamics.addItinerary(it4);
  dynamics.addItinerary(it5);
  dynamics.addItinerary(it6);
  dynamics.addItinerary(it7);
  dynamics.addItinerary(it8);
  dynamics.addItinerary(it9);
  dynamics.addItinerary(it10);
  dynamics.addItinerary(it11);
  dynamics.addItinerary(it12);
  dynamics.addItinerary(it13);
  dynamics.addItinerary(it14);
  dynamics.addItinerary(it15);
  dynamics.addItinerary(it16);
  dynamics.setSeed(69);
  dynamics.setErrorProbability(0.3);
  dynamics.setMinSpeedRateo(0.95);

  const int n_rep{100};
  Bench b1(n_rep);
  std::cout << "Benchmarking updatePaths\n";
  dynamics.updatePaths();
  b1.benchmark([&dynamics]() -> void { dynamics.updatePaths(); });
  b1.print<sb::milliseconds>();
}
