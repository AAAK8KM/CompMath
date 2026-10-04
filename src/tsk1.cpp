#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>

std::array<double, 2> f1(const std::array<double, 2> &x) {
  return {std::sqrt(1 - x[1] * x[1]), std::tan(x[0])};
}

double ln(const std::array<double, 2> &x) {
  return std::sqrt(x[0] * x[0] + x[1] * x[1]);
}

std::array<double, 2> operator+(const std::array<double, 2> &lhs,
                                const std::array<double, 2> &rhs) {
  return {lhs[0] + rhs[0], lhs[1] + rhs[1]};
}

std::array<double, 2> operator-(const std::array<double, 2> &lhs,
                                const std::array<double, 2> &rhs) {
  return {lhs[0] - rhs[0], lhs[1] - rhs[1]};
}

std::array<double, 2> operator*(double lhs, const std::array<double, 2> &rhs) {
  return {lhs * rhs[0], lhs * rhs[1]};
}

int main() {
  std::array<double, 2> x = {0.6, 0.8}, xn;
  double err = 0.1, eps = 1e-6;
  while (err > eps) {
    xn = x + 0.1 * (f1(x) - x);
    err = ln(x - xn);
    x = xn;
    if (x[1] > 1)
      x[1] = 0.99;
    std::cout << std::setprecision(7) << x[0] << " " << x[1] << " " << err
              << "\n";
  }
}
