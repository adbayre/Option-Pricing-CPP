#pragma once
#include "BinaryTree.h"
#include "EuropeanVanillaOption.h"
#include <stdexcept>
#include <cmath>

class CRRPricer {
private:
    EuropeanVanillaOption* _option;
    int _depth;
    double _up;
    double _down;
    double _rate;
    double _assetPrice;
    mutable BinaryTree<double> _tree;
    mutable bool _computed;

    void checkArbitrage() const;

public:
    // Constructeur
    CRRPricer(EuropeanVanillaOption* option, int depth, double up, double assetPrice, double down, double rate);

    // Méthodes
    void compute() const;                  
    double get(int n, int i) const;        
    double operator()(bool closed_form = false) const;
};
