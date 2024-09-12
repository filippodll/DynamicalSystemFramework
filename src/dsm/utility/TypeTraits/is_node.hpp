
#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

namespace dsm {
  template <typename Id, typename Size>
    requires(std::unsigned_integral<Id> && std::unsigned_integral<Size>)
  class Node;

  // define is_node type trait
  template <typename T>
  struct is_node : std::false_type {};

  template <typename Id, typename Size>
  struct is_node<Node<Id, Size>> : std::true_type {};

  template <typename Id, typename Size>
  struct is_node<const Node<Id, Size>> : std::true_type {};

  template <typename Id, typename Size>
  struct is_node<const Node<Id, Size>&> : std::true_type {};

  template <typename T>
  struct is_node<std::is_base_of_v<Node<typename T::Id_t, typename T::Size_t>,
                                   std::remove_const_t<std::remove_reference_t<T>>>>
      : std::true_type {};

  template <typename Id, typename Size>
  struct is_node<std::unique_ptr<Node<Id, Size>>> : std::true_type {};

  template <typename T>
  inline constexpr bool is_node_v = is_node<T>::value;

};  // namespace dsm
