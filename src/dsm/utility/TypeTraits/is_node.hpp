#ifndef is_node_hpp
#define is_node_hpp

#include <concepts>
#include <memory>
#include <type_traits>

namespace dsm {
  template <typename Id, typename... Ids>
    requires std::unsigned_integral<Id> && (std::unsigned_integral<Ids> && ...)
  class Node;

  // Alias for shared pointers
  template <typename T>
  using shared = std::shared_ptr<T>;

  // define is_node type trait
  template <typename T>
  struct is_node : std::false_type {};

  template <typename Id, typename... Ids>
  struct is_node<Node<Id, Ids...>> : std::true_type {};

  template <typename Id, typename... Ids>
  struct is_node<const Node<Id, Ids...>> : std::true_type {};

  template <typename Id, typename... Ids>
  struct is_node<const Node<Id, Ids...>&> : std::true_type {};

  template <typename Id, typename... Ids>
  struct is_node<shared<Node<Id, Ids...>>> : std::true_type {};

  template <typename T>
  inline constexpr bool is_node_v = is_node<T>::value;

};  // namespace dsm

#endif
