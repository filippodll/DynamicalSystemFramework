/// @file       /src/dsm/headers/SparseMatrix.hpp
/// @brief      Defines the SparseMatrix class.
///
/// @details    This file contains the definition of the SparseMatrix class.
///             The SparseMatrix class represents a sparse matrix. It is templated by the type
///             of the matrix's index and the type of the matrix's value.
///             The matrix's index must be an unsigned integral type.

#pragma once

#include <concepts>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#include <cmath>

#include "../utility/Logger.hpp"

namespace dsm {
  /// @brief The SparseMatrix class represents a sparse matrix.
  /// @tparam Index The type of the matrix's index. It must be an unsigned integral type.
  /// @tparam T The type of the matrix's value.
  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  class SparseMatrix {
    std::unordered_map<Index, T> _matrix;
    Index _rows, _cols;
    T _defaultReturn;

  public:
    SparseMatrix();

    /// @brief SparseMatrix constructor
    /// @param rows number of rows
    /// @param cols number of columns
    /// @throw std::invalid_argument if rows or cols are < 0
    SparseMatrix(Index rows, Index cols);

    /// @brief SparseMatrix constructor - colum
    /// @param index number of rows
    /// @throw std::invalid_argument if index is < 0
    explicit SparseMatrix(Index index);

    /// @brief insert a value in the matrix
    /// @param i row index
    /// @param j column index
    /// @param value value to insert
    /// @throw std::out_of_range if the index is out of range
    void insert(Index i, Index j, T value);

    /// @brief insert a value in the matrix
    /// @param i index
    /// @param value value to insert
    /// @throw std::out_of_range if the index is out of range
    void insert(Index i, T value);

    /// @brief insert a value in the matrix. If the element already exist, it
    /// overwrites it
    /// @param i row index
    /// @param j column index
    /// @param value value to insert
    /// @throw std::out_of_range if the index is out of range
    void insert_or_assign(Index i, Index j, T value);

    /// @brief insert a value in the matrix. If the element already exist, it
    /// overwrites it
    /// @param index index in vectorial form
    /// @param value value to insert
    /// @throw std::out_of_range if the index is out of range
    void insert_or_assign(Index index, T value);

    /// @brief insert a value in the matrix and expand the matrix if necessary.
    /// @param i row index
    /// @param j column index
    /// @param value value to insert
    void insert_and_expand(Index i, Index j, T value);

    /// @brief remove a value from the matrix
    /// @param i row index
    /// @param j column index
    /// @throw std::out_of_range if the index is out of range
    /// @throw std::runtime_error if the element is not found
    void erase(Index i, Index j);

    /// @brief remove a value from the matrix
    /// @param index index in vectorial form
    /// @throw std::out_of_range if the index is out of range
    /// @throw std::runtime_error if the element is not found
    void erase(Index index);

    /// @brief remove a row from the matrix
    /// @param index row index
    /// @throw std::out_of_range if the index is out of range
    void eraseRow(Index index);

    /// @brief remove a column from the matrix
    /// @param index column index
    /// @throw std::out_of_range if the index is out of range
    void eraseColumn(Index index);

    /// @brief set to 0 all the elements in a row
    void emptyRow(Index index);

    /// @brief set to 0 all the elements in a column
    void emptyColumn(Index index);

    /// @brief empty the matrix and set the dimensions to zero
    void clear();

    /// @brief check if the element is non zero
    /// @param i row index
    /// @param j column index
    /// @return true if the element is non zero
    /// @throw std::out_of_range if the index is out of range
    bool contains(Index i, Index j) const;

    /// @brief check if the element is non zero
    /// @param index index in vectorial form
    /// @return true if the element is non zero
    /// @throw std::out_of_range if the index is out of range
    bool contains(Index const index) const;

    /// @brief get the input degree of all nodes
    /// @return a SparseMatrix vector with the input degree of all nodes
    /// @throw std::runtime_error if the matrix is not square
    SparseMatrix<Index, int> getDegreeVector() const;

    /// @brief get the strength of all nodes
    /// @return a SparseMatrix vector with the strength of all nodes
    /// @throw std::runtime_error if the matrix is not square
    SparseMatrix<Index, double> getStrengthVector() const;

    /// @brief get the laplacian matrix
    /// @return the laplacian matrix
    /// @throw std::runtime_error if the matrix is not square
    SparseMatrix<Index, int> getLaplacian() const;

    /// @brief get a row as a row vector
    /// @param index row index
    /// @param keepIndex if true, the index of the elements in the row will be
    /// the same as the index of the elements in the matrix
    /// @return a row vector if keepIndex is false, otherwise a matrix with the
    /// same dimensions as the original matrix
    /// @throw std::out_of_range if the index is out of range
    SparseMatrix getRow(Index index, bool keepIndex = false) const;

    /// @brief get a column as a column vector
    /// @param index column index
    /// @param keepIndex if true, the index of the elements in the column will
    /// be the same as the index of the elements in the matrix
    /// @return a column vector if keepIndex is false, otherwise a matrix with
    /// the same dimensions as the original matrix
    /// @throw std::out_of_range if the index is out of range
    SparseMatrix getCol(Index index, bool keepIndex = false) const;

    /// @brief get a matrix of double with every row normalized to 1
    /// @return a matrix of double
    SparseMatrix<Index, double> getNormRows() const;

    /// @brief get a matrix of double with every column normalized to 1
    /// @return a matrix of double
    SparseMatrix<Index, double> getNormCols() const;

    /// @brief get the number of rows
    /// @return number of rows
    Index getRowDim() const { return _rows; }

    /// @brief get the number of columns
    /// @return number of columns
    Index getColDim() const { return _cols; }

    /// @brief get the number of non zero elements in the matrix
    /// @return number of non zero elements
    Index size() const { return _matrix.size(); };

    /// @brief get the maximum number of elements in the matrix
    /// @return maximum number of elements
    Index max_size() const { return _rows * _cols; }

    /// @brief symmetrize the matrix
    void symmetrize();

    /// @brief reshape the matrix
    void reshape(Index rows, Index cols);

    /// @brief reshape the matrix
    void reshape(Index dim);

    /// @brief return the begin iterator of the matrix
    /// @return the begin iterator
    typename std::unordered_map<Index, T>::const_iterator begin() const {
      return _matrix.begin();
    }

    /// @brief return the end iterator of the matrix
    /// @return the end iterator
    typename std::unordered_map<Index, T>::const_iterator end() const {
      return _matrix.end();
    }

    /// @brief access an element of the matrix
    /// @param i row index
    /// @param j column index
    /// @return the element
    /// @throw std::out_of_range if the index is out of range
    const T& operator()(Index i, Index j) const;

    /// @brief access an element of the matrix
    /// @param i row index
    /// @param j column index
    /// @return the element
    /// @throw std::out_of_range if the index is out of range
    T& operator()(Index i, Index j);

    /// @brief access an element of the matrix
    /// @param index index in vectorial form
    /// @return the element
    /// @throw std::out_of_range if the index is out of range
    const T& operator()(Index index) const;

    /// @brief access an element of the matrix
    /// @param index index in vectorial form
    /// @return the element
    /// @throw std::out_of_range if the index is out of range
    T& operator()(Index index);

    /// @brief sum of two matrices
    /// @param other the other matrix
    /// @return the sum of the two matrices
    /// @throw std::runtime_error if the dimensions do not match
    template <typename I, typename U>
      requires std::unsigned_integral<I>
    SparseMatrix<Index, T> operator+(const SparseMatrix<I, U>& other) {
      if (this->_rows != other._rows || this->_cols != other._cols) {
        throw std::runtime_error(buildLog("Dimensions do not match"));
      }
      auto result = SparseMatrix<Index, T>(this->_rows, this->_cols);
      std::unordered_map<Index, bool> unique;
      for (auto& it : this->_matrix) {
        unique.insert_or_assign(it.first, true);
      }
      for (auto& it : other._matrix) {
        unique.insert_or_assign(it.first, true);
      }
      for (auto& it : unique) {
        result.insert(it.first / this->_cols,
                      it.first % this->_cols,
                      (*this)(it.first) + other(it.first));
      }
      return result;
    }

    /// @brief difference of two matrices
    /// @param other the other matrix
    /// @return the difference of the two matrices
    /// @throw std::runtime_error if the dimensions do not match
    template <typename I, typename U>
      requires std::unsigned_integral<I>
    SparseMatrix<Index, T> operator-(const SparseMatrix<I, U>& other) {
      if (this->_rows != other._rows || this->_cols != other._cols) {
        throw std::runtime_error(buildLog("Dimensions do not match"));
      }
      auto result = SparseMatrix(this->_rows, this->_cols);
      std::unordered_map<Index, bool> unique;
      for (auto& it : this->_matrix) {
        unique.insert_or_assign(it.first, true);
      }
      for (auto& it : other._matrix) {
        unique.insert_or_assign(it.first, true);
      }
      for (auto& it : unique) {
        result.insert(it.first / this->_cols,
                      it.first % this->_cols,
                      (*this)(it.first) - other(it.first));
      }
      return result;
    }

    /// @brief transpose the matrix
    /// @return the transposed matrix
    SparseMatrix operator++();

    /// @brief sum of two matrices
    /// @param other the other matrix
    /// @return the sum of the two matrices
    /// @throw std::runtime_error if the dimensions do not match
    template <typename I, typename U>
      requires std::unsigned_integral<I>
    SparseMatrix& operator+=(const SparseMatrix<I, U>& other);

    /// @brief difference of two matrices
    /// @param other the other matrix
    /// @return the difference of the two matrices
    /// @throw std::runtime_error if the dimensions do not match
    template <typename I, typename U>
      requires std::unsigned_integral<I>
    SparseMatrix& operator-=(const SparseMatrix<I, U>& other);
  };

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  SparseMatrix<Index, T>::SparseMatrix()
      : _matrix{std::unordered_map<Index, T>()}, _rows{}, _cols{}, _defaultReturn{0} {}

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  SparseMatrix<Index, T>::SparseMatrix(Index rows, Index cols)
      : _matrix{std::unordered_map<Index, T>()},
        _rows{rows},
        _cols{cols},
        _defaultReturn{0} {}

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  SparseMatrix<Index, T>::SparseMatrix(Index index)
      : _matrix{std::unordered_map<Index, T>()},
        _rows{index},
        _cols{1},
        _defaultReturn{0} {}

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  void SparseMatrix<Index, T>::insert(Index i, Index j, T value) {
    const auto index = i * _cols + j;
    this->insert(index, value);
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  void SparseMatrix<Index, T>::insert(Index i, T value) {
    if (i > _rows * _cols - 1) {
      throw std::out_of_range(buildLog("Index " + std::to_string(i) + " out of range " +
                                       std::to_string(_rows * _cols - 1)));
    }
    _matrix.emplace(std::make_pair(i, value));
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  void SparseMatrix<Index, T>::insert_or_assign(Index i, Index j, T value) {
    const auto index = i * _cols + j;
    this->insert_or_assign(index, value);
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  void SparseMatrix<Index, T>::insert_or_assign(Index index, T value) {
    if (index > _rows * _cols - 1) {
      throw std::out_of_range(buildLog("Index " + std::to_string(index) +
                                       " out of range " +
                                       std::to_string(_rows * _cols - 1)));
    }
    _matrix.insert_or_assign(index, value);
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  void SparseMatrix<Index, T>::insert_and_expand(Index i, Index j, T value) {
    if (!(i < _rows) || !(j < _cols)) {
      Index delta = std::max(i - _rows, j - _cols);
      if (_cols == 1) {
        if (!((i + delta) < (_rows + delta))) {
          ++delta;
        }
        this->reshape(_rows + delta);
      } else {
        if (!((i * (_cols + delta) + j) < (_rows + delta) * (_cols + delta))) {
          ++delta;
        }
        this->reshape(_rows + delta, _cols + delta);
      }
    }
    _matrix.insert_or_assign(i * _cols + j, value);
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  void SparseMatrix<Index, T>::erase(Index i, Index j) {
    if (i >= _rows || j >= _cols) {
      throw std::out_of_range(buildLog("Index out of range"));
    }
    if (_matrix.find(i * _cols + j) == _matrix.end()) {
      throw std::runtime_error(buildLog("Element not found"));
    }
    _matrix.erase(i * _cols + j);
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  void SparseMatrix<Index, T>::erase(Index index) {
    if (index > _rows * _cols - 1) {
      throw std::out_of_range(buildLog("Index out of range"));
    }
    if (_matrix.find(index) == _matrix.end()) {
      throw std::runtime_error(buildLog("Element not found"));
    }
    _matrix.erase(index);
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  void SparseMatrix<Index, T>::eraseRow(Index index) {
    if (index > _rows - 1) {
      throw std::out_of_range(buildLog("Index out of range"));
    }
    for (Index i = 0; i < _cols; ++i) {
      _matrix.erase(index * _cols + i);
    }
    std::unordered_map<Index, T> new_matrix = {};
    for (auto const& [key, value] : _matrix) {
      if (key / _cols < index) {
        new_matrix.emplace(std::make_pair(key, value));
      } else {
        new_matrix.emplace(std::make_pair(key - _cols, value));
      }
    }
    --_rows;
    _matrix = new_matrix;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  void SparseMatrix<Index, T>::eraseColumn(Index index) {
    if (index > _cols - 1) {
      throw std::out_of_range(buildLog("Index out of range"));
    }
    for (Index i = 0; i < _rows; ++i) {
      _matrix.erase(i * _cols + index);
    }
    std::unordered_map<Index, T> new_matrix = {};
    for (auto const& [key, value] : _matrix) {
      if (key % _cols < index) {
        new_matrix.emplace(std::make_pair(key - key / _cols, value));
      } else {
        new_matrix.emplace(
            std::make_pair(key / _cols * (_cols - 1) + key % _cols - 1, value));
      }
    }
    --_cols;
    _matrix = new_matrix;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  void SparseMatrix<Index, T>::emptyRow(Index index) {
    for (const auto& x : this->getRow(index)) {
      _matrix.erase(index * _cols + x.first);
    }
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  void SparseMatrix<Index, T>::emptyColumn(Index index) {
    for (const auto& x : this->getCol(index)) {
      _matrix.erase(x.first * _cols + index);
    }
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  void SparseMatrix<Index, T>::clear() {
    _matrix.clear();
    _rows = 0;
    _cols = 0;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  bool SparseMatrix<Index, T>::contains(Index i, Index j) const {
    if (i >= _rows || j >= _cols) {
      throw std::out_of_range(buildLog("Index out of range"));
    }
    return _matrix.contains(i * _cols + j);
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  bool SparseMatrix<Index, T>::contains(Index const index) const {
    if (index > _rows * _cols - 1) {
      throw std::out_of_range(buildLog("Index out of range"));
    }
    return _matrix.contains(index);
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  SparseMatrix<Index, int> SparseMatrix<Index, T>::getDegreeVector() const {
    if (_rows != _cols) {
      throw std::runtime_error(buildLog("getDegreeVector only works on square matrices"));
    }
    auto degreeVector = SparseMatrix<Index, int>(_rows, 1);
    for (auto& i : _matrix) {
      degreeVector.insert_or_assign(
          i.first / _cols, 0, degreeVector(i.first / _cols, 0) + 1);
    }
    return degreeVector;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  SparseMatrix<Index, double> SparseMatrix<Index, T>::getStrengthVector() const {
    if (_rows != _cols) {
      throw std::runtime_error(
          buildLog("getStrengthVector only works on square matrices"));
    }
    auto strengthVector = SparseMatrix<Index, double>(_rows, 1);
    for (auto& i : _matrix) {
      strengthVector.insert_or_assign(
          i.first / _cols, 0, strengthVector(i.first / _cols, 0) + i.second);
    }
    return strengthVector;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  SparseMatrix<Index, int> SparseMatrix<Index, T>::getLaplacian() const {
    if (_rows != _cols) {
      throw std::runtime_error(buildLog("getLaplacian only works on square matrices"));
    }
    auto laplacian = SparseMatrix<Index, int>(_rows, _cols);
    for (auto& i : _matrix) {
      laplacian.insert_or_assign(i.first / _cols, i.first % _cols, -1);
    }
    auto degreeVector = this->getDegreeVector();
    for (Index i = 0; i < _rows; ++i) {
      laplacian.insert_or_assign(i, i, degreeVector(i, 0));
    }
    return laplacian;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  SparseMatrix<Index, T> SparseMatrix<Index, T>::getRow(Index index,
                                                        bool keepIndex) const {
    if (index >= _rows) {
      throw std::out_of_range(buildLog("Index out of range"));
    }
    SparseMatrix row(1, _cols);
    if (keepIndex) {
      row.reshape(_rows, _cols);
    }
    for (auto& it : _matrix) {
      if (it.first / _cols == index) {
        keepIndex ? row.insert(it.first, it.second)
                  : row.insert(it.first % _cols, it.second);
      }
    }
    return row;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  SparseMatrix<Index, T> SparseMatrix<Index, T>::getCol(Index index,
                                                        bool keepIndex) const {
    if (index >= _cols) {
      throw std::out_of_range(buildLog("Index out of range"));
    }
    SparseMatrix col(_rows, 1);
    if (keepIndex) {
      col.reshape(_rows, _cols);
    }
    for (auto& it : _matrix) {
      if (it.first % _cols == index) {
        keepIndex ? col.insert(it.first, it.second)
                  : col.insert(it.first / _cols, it.second);
      }
    }
    return col;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  SparseMatrix<Index, double> SparseMatrix<Index, T>::getNormRows() const {
    SparseMatrix<Index, double> normRows(_rows, _cols);
    for (Index index = 0; index < _rows; ++index) {
      auto row = this->getRow(index, true);
      double sum = 0.;
      for (auto& it : row) {
        sum += std::abs(it.second);
      }
      sum < std::numeric_limits<double>::epsilon() ? sum = 1. : sum = sum;
      for (auto& it : row) {
        normRows.insert(it.first, it.second / sum);
      }
    }
    return normRows;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  SparseMatrix<Index, double> SparseMatrix<Index, T>::getNormCols() const {
    SparseMatrix<Index, double> normCols(_rows, _cols);
    for (Index index = 0; index < _cols; ++index) {
      auto col = this->getCol(index, true);
      double sum = 0.;
      for (auto& it : col) {
        sum += std::abs(it.second);
      }
      sum < std::numeric_limits<double>::epsilon() ? sum = 1. : sum = sum;
      for (auto& it : col) {
        normCols.insert(it.first, it.second / sum);
      }
    }
    return normCols;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  void SparseMatrix<Index, T>::symmetrize() {
    *this += this->operator++();
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  void SparseMatrix<Index, T>::reshape(Index rows, Index cols) {
    Index oldCols = this->_cols;
    this->_rows = rows;
    this->_cols = cols;
    auto copy = _matrix;
    for (auto& it : copy) {
      _matrix.erase(it.first);
      if (it.first < rows * cols) {
        this->insert_or_assign(it.first / oldCols, it.first % oldCols, it.second);
      }
    }
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  void SparseMatrix<Index, T>::reshape(Index index) {
    this->_rows = index;
    this->_cols = 1;
    auto copy = _matrix;
    for (auto& it : copy) {
      _matrix.erase(it.first);
      if (it.first < index) {
        this->insert_or_assign(it.first, it.second);
      }
    }
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  const T& SparseMatrix<Index, T>::operator()(Index i, Index j) const {
    if (i >= _rows || j >= _cols) {
      throw std::out_of_range(buildLog("Index out of range"));
    }
    auto const& it = _matrix.find(i * _cols + j);
    return it != _matrix.end() ? it->second : _defaultReturn;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  T& SparseMatrix<Index, T>::operator()(Index i, Index j) {
    if (i >= _rows || j >= _cols) {
      throw std::out_of_range(buildLog("Index out of range"));
    }
    auto const& it = _matrix.find(i * _cols + j);
    return it != _matrix.end() ? it->second : _defaultReturn;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  const T& SparseMatrix<Index, T>::operator()(Index index) const {
    if (index >= _rows * _cols) {
      throw std::out_of_range(buildLog("Index out of range"));
    }
    auto const& it = _matrix.find(index);
    return it != _matrix.end() ? it->second : _defaultReturn;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  T& SparseMatrix<Index, T>::operator()(Index index) {
    if (index >= _rows * _cols) {
      throw std::out_of_range(buildLog("Index out of range"));
    }
    auto const& it = _matrix.find(index);
    return it != _matrix.end() ? it->second : _defaultReturn;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  SparseMatrix<Index, T> SparseMatrix<Index, T>::operator++() {
    auto transpost = SparseMatrix(this->_cols, this->_rows);
    for (auto& it : _matrix) {
      transpost.insert(it.first % _cols, it.first / _cols, it.second);
    }
    return transpost;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  template <typename I, typename U>
    requires std::unsigned_integral<I>
  SparseMatrix<Index, T>& SparseMatrix<Index, T>::operator+=(
      const SparseMatrix<I, U>& other) {
    if (this->_rows != other._rows || this->_cols != other._cols) {
      throw std::runtime_error(buildLog("Dimensions do not match"));
    }
    for (auto& it : other._matrix) {
      this->contains(it.first)
          ? this->insert_or_assign(it.first, this->operator()(it.first) + it.second)
          : this->insert(it.first, it.second);
    }
    return *this;
  }

  template <typename Index, typename T>
    requires(std::unsigned_integral<Index>)
  template <typename I, typename U>
    requires std::unsigned_integral<I>
  SparseMatrix<Index, T>& SparseMatrix<Index, T>::operator-=(
      const SparseMatrix<I, U>& other) {
    if (this->_rows != other._rows || this->_cols != other._cols) {
      throw std::runtime_error(buildLog("Dimensions do not match"));
    }
    for (auto& it : other._matrix) {
      this->contains(it.first)
          ? this->insert_or_assign(it.first, this->operator()(it.first) - it.second)
          : this->insert(it.first, -it.second);
    }
    return *this;
  }
};  // namespace dsm
