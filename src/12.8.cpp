#include <cmath>
#include <iomanip>
#include <iostream>
double fs(double x) { return x * std::exp(-x * x); }

double fp(double x) { return std::exp(-x * x) - 2 * x * x * std::exp(-x * x); }

double fpp(double x) {
  return -6 * x * std::exp(-x * x) + 4 * x * x * x * std::exp(-x * x);
}

double fi1(double x, double y) { return y / std::exp(-x * x); }

double fi2(double x, double y) { return std::sqrt(-std::log(y / x)); }

double mpi(double y, double x0, double f(double, double), double eps = 1e-6) {
  double x = x0, r = eps + 1;
  while (r > eps) {
    x = f(x, y);
    r = std::abs(f(x, y) - x);
  }
  return x;
}

double newton(double y, double x0, double f(double), double fp(double),
              double eps = 1e-6) {
  double x = x0, r = eps + 1;
  while (r > eps) {
    x = x - (f(x) - y) / fp(x);
    r = std::abs(f(x) - y);
  }
  return x;
}

int main() {
  double xmax = 1;
  xmax = newton(0, 1, fp, fpp);
  std::cout << "Точка x максимума f: " << std::setprecision(8) << xmax << "\n";
  double h2 = fs(xmax) / 2;

  std::cout << "Методом простой итерации: \n";
  std::cout << mpi(h2, xmax - 0.5, fi1) << " " << mpi(h2, xmax + 0.5, fi2)
            << "\n";

  std::cout << "Методом Ньютона: \n";
  std::cout << std::setprecision(8) << newton(h2, xmax - 0.5, fs, fp) << " "
            << std::setprecision(8) << newton(h2, xmax + 0.5, fs, fp) << "\n";
}
