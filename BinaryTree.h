#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T>
class BinaryTree {
private:
    int _depth;
    std::vector<std::vector<T>> _tree;

public:
    BinaryTree() : _depth(0) {}

    void setDepth(int N) {
        if (N < 0)
            throw std::invalid_argument("La taille de la matrice doit être positive !");
        _depth = N;
        _tree.clear();
        _tree.resize(N + 1);
        for (int n = 0; n <= N; ++n) {
            _tree[n].resize(n + 1);
        }
    }

    int getDepth() const {
        return _depth;
    }

    void setNode(int n, int i, const T& value) {
        if (n < 0 || n > _depth || i < 0 || i > n)
            throw std::invalid_argument("Indices hors limites !"); 
        _tree[n][i] = value;
    }

    T getNode(int n, int i) const {
        if (n < 0 || n > _depth || i < 0 || i > n)
            throw std::invalid_argument("Indices hors limites !");
        return _tree[n][i];
    }

    void display(std::ostream& os = std::cout) const {
        for (int n = 0; n <= _depth; ++n) {
            for (int i = 0; i <= n; ++i) {
                os << _tree[n][i] << " ";
            }
            os << std::endl;
        }
    }
};
