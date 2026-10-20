#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>

std::array<double, 2> f1(const std::array<double, 2> &x) {
  return {std::sqrt(1 - x[1] * x[1]), std::tan(x[0])};
}

std::array<double, 2> f2(const std::array<double, 2> &x) {
  return {-std::sqrt(1 - x[1] * x[1]), std::tan(x[0])};
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

std::array<double, 2>
simple_rel(std::array<double, 2> x,
           std::array<double, 2> f(const std::array<double, 2> &)) {
  std::array<double, 2> xn;
  double err = 0.1, eps = 1e-6;
  while (err > eps) {
    xn = x + 0.1 * (f(x) - x);
    err = ln(x - xn);
    x = xn;
    if (std::abs(x[1]) > 1)
      x[1] = 0.99;
    // std::cout << std::setprecision(7) << x[0] << " " << x[1] << " " << err
    //           << "\n";
  }
  return x;
}

int main() {
  std::array<double, 2> x1 = {1. / 2., 1. / 2}, x2 = {-1. / 2., -1. / 2}, res;
  res = simple_rel(x1, f1);
  std::cout << "Первая точка(корень с плюсом): " << res[0] << " " << res[1]
            << "\n";
  res = simple_rel(x2, f2);
  std::cout << "Вторая точка(корень с минусом): " << res[0] << " " << res[1]
            << "\n";
}
