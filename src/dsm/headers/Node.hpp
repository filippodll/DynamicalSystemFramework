/// @file       src/Node.hpp
/// @brief      Defines the Node class.
///
/// @details    This file contains the definition of the Node class.
///             The Node class represents a node in the network. It is templated by the type
///             of the node's id, which must be an unsigned integral type.

#ifndef Node_hpp
#define Node_hpp

#include <functional>
#include <queue>
#include <tuple>
#include <utility>

namespace dsm {
  /// @brief The Node class represents a node in the network.
  /// @tparam Id The type of the node's id. It must be an unsigned integral type.
  template <typename Id, typename... Ids>
    requires std::unsigned_integral<Id> && (std::unsigned_integral<Ids> && ...)
  class Node {
  private:
    std::tuple<std::queue<Ids>...> m_queue;
    std::pair<double, double> m_coords;
    Id m_id;

  public:
    Node() = default;
    /// @brief Construct a new Node object
    /// @param id, The node's id
    explicit Node(Id id);
    /// @brief Construct a new Node object
    /// @param id, The node's id
    /// @param coords, A std::pair containing the node's coordinates
    Node(Id id, std::pair<double, double> coords);
    /// @brief Construct a new Node object
    /// @param id, The node's id
    /// @param coords, A std::pair containing the node's coordinates
    /// @param queue, A std::queue containing the node's queue
    Node(Id id, std::pair<double, double> coords, std::queue<Ids>&&... queue);

    /// @brief Set the node's coordinates
    /// @param coords, A std::pair containing the node's coordinates
    void setCoords(std::pair<double, double> coords);
    /// @brief Set the node's queue
    /// @param queue, A std::queue containing the node's queue
    void setQueue(std::queue<Ids>&&... queue);

    /// @brief Get the node's id
    /// @return Id, The node's id
    Id id() const;
    /// @brief Get the node's coordinates
    /// @return std::pair<double,, double> A std::pair containing the node's coordinates
    const std::pair<double, double>& coords() const;
    /// @brief Get the node's queue
    /// @return std::queue<Id>, A std::queue containing the node's queue
    const std::tuple<std::queue<Ids>...>& queue() const;
  };

  template <typename Id, typename... Ids>
    requires std::unsigned_integral<Id> && (std::unsigned_integral<Ids> && ...)
  Node<Id, Ids...>::Node(Id id) : m_id{id} {}

  template <typename Id, typename... Ids>
    requires std::unsigned_integral<Id> && (std::unsigned_integral<Ids> && ...)
  Node<Id, Ids...>::Node(Id id, std::pair<double, double> coords) : m_coords{std::move(coords)}, m_id{id} {}

  template <typename Id, typename... Ids>
    requires std::unsigned_integral<Id> && (std::unsigned_integral<Ids> && ...)
  Node<Id, Ids...>::Node(Id id, std::pair<double, double> coords, std::queue<Ids>&&... queues)
      : m_queue{std::make_tuple(queues...)}, m_coords{std::move(coords)}, m_id{id} {}

  template <typename Id, typename... Ids>
    requires std::unsigned_integral<Id> && (std::unsigned_integral<Ids> && ...)
  Id Node<Id, Ids...>::id() const {
    return m_id;
  }

  template <typename Id, typename... Ids>
    requires std::unsigned_integral<Id> && (std::unsigned_integral<Ids> && ...)
  void Node<Id, Ids...>::setCoords(std::pair<double, double> coords) {
    m_coords = std::move(coords);
  }

  template <typename Id, typename... Ids>
    requires std::unsigned_integral<Id> && (std::unsigned_integral<Ids> && ...)
  void Node<Id, Ids...>::setQueue(std::queue<Ids>&&... queues) {
    m_queue = std::make_tuple(queues...);
  }

  template <typename Id, typename... Ids>
    requires std::unsigned_integral<Id> && (std::unsigned_integral<Ids> && ...)
  const std::pair<double, double>& Node<Id, Ids...>::coords() const {
    return m_coords;
  }

  template <typename Id, typename... Ids>
    requires std::unsigned_integral<Id> && (std::unsigned_integral<Ids> && ...)
  const std::tuple<std::queue<Ids>...>& Node<Id, Ids...>::queue() const {
    return m_queue;
  }

  // to be implemented
  /* template <typename Id> */
  /* class Intersection : public Node<Id, Ids...> { */
  /* private: */
  /*   std::function<void()> m_priority; */
  /* }; */

  /* template <typename Id> */
  /* class Roundabout : public Node<Id, Ids...> { */
  /* private: */
  /*   std::function<void()> m_priority; */
  /* }; */

  /* template <typename Id> */
  /* class TrafficLight : public Node<Id, Ids...> { */
  /* private: */
  /*   std::function<void()> m_priority; */
  /* }; */
};  // namespace dsm

#endif
