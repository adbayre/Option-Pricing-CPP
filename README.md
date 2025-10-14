# C++ for Finance — Semester 7

**Authors:** BAYRE Adrien | GRUEZ Maxime | JONDEAU Martin | KEREDAN Sacha | SOARES Lucas

**Teacher:** PU Jiang

---

## Project Overview

This project implements a modular C++ framework for pricing financial derivatives under various models:

* **Black-Scholes model** (analytical and Monte Carlo methods)
* **Cox-Ross-Rubinstein (CRR) binomial model** (including American options)
* **Path-dependent options** (e.g., Asian options)

It emphasizes object-oriented design, numerical computation, and compliance with financial theory.

---

## Architecture

The project is divided into **four main parts**, each corresponding to a section of the assignment:

### 1. Black-Scholes Model

* Abstract base class `Option` with:

  * Virtual methods `payo(double)` and `payoPath(std::vector<double>)`
  * Getter `getExpiry()`
* Derived classes:

  * `EuropeanVanillaOption` (abstract)
  * `CallOption` and `PutOption`
  * `EuropeanDigitalCallOption` and `EuropeanDigitalPutOption`
* `BlackScholesPricer`: Analytical pricer using the Black-Scholes closed-form formulas for both vanilla and digital options.
* Methods:

  * `operator()` → returns option price
  * `delta()` → returns option Delta

---

### 2. Cox-Ross-Rubinstein Model

* **Template class `BinaryTree<T>`**

  * Manages a tree structure of depth `N` for the binomial model.
  * Methods: `setDepth`, `setNode`, `getNode`, `display`.

* **Class `CRRPricer`**

  * Constructor: `CRRPricer(Option*, int depth, double S0, double up, double down, double rate)`
  * Implements both **backward induction** and **closed-form** pricing.
  * Supports **European** and **American** options.
  * Handles **arbitrage condition** checks.
  * Provides optional constructor for **Black-Scholes limit initialization**:

    ```cpp
    CRRPricer(Option* option, int depth, double S0, double r, double volatility);
    ```
  * For American options, stores the **early exercise policy** in a `BinaryTree<bool>`.

---

### 3. Path-Dependent and Monte Carlo Pricing

* Derived class `AsianOption` extending `Option`

  * Holds time steps and overrides `payoPath()`.
  * Subclasses: `AsianCallOption`, `AsianPutOption`.

* **Singleton class `MT`**

  * Encapsulates a single instance of `std::mt19937`.
  * Static methods:

    * `rand_unif()` — uniform [0,1]
    * `rand_norm()` — normal(0,1)

* **Class `BlackScholesMCPricer`**

  * Monte Carlo pricing under the Black-Scholes model.
  * Incrementally updates mean and variance with each call to `generate(nb_paths)`.
  * Provides:

    * `operator()` — current price estimate
    * `getNbPaths()` — number of simulated paths
    * `confidenceInterval()` — 95% CI of the estimate

---

### 4. American Options in CRR

* Additional classes:

  * `AmericanOption` (derived from `Option`)
  * `AmericanCallOption`, `AmericanPutOption`
* CRR algorithm extended to compute:

  * **Continuation value vs. intrinsic value**
  * **Exercise decision tree** (`BinaryTree<bool>`)

---

## Compilation

To compile all files:

```bash
g++ -std=c++17 -O2 *.cpp -o finance_project
```

All `.cpp` and `.h` files should be included in the zip archive, **without any `main()` function**.
Test programs are provided separately by the instructor.

---

## Repository Structure

```
C++_Finance_Project/
│
├── Option.h / Option.cpp
├── EuropeanVanillaOption.h / .cpp
├── CallOption.h / .cpp
├── PutOption.h / .cpp
├── DigitalOptions.h / .cpp
├── AsianOption.h / .cpp
├── AmericanOption.h / .cpp
│
├── BlackScholesPricer.h / .cpp
├── BlackScholesMCPricer.h / .cpp
├── CRRPricer.h / .cpp
│
├── BinaryTree.h
├── MT.h / MT.cpp
│
└── README.md
```

---

## License

Educational use only — reproduction or redistribution without permission is prohibited.
