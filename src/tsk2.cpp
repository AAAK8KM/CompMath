#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>

double f(double x) {
  return std::sin(100 * x) * std::exp(-x * x) * std::cos(2 * x);
}

struct root {
  double r;
  double w;
};

int main() {
  double l = 0, r = 3;
  std::array<root, 3> roots = {{{-std::sqrt(3. / 5), 5. / 9},
                                {0., 8. / 9},
                                {std::sqrt(3. / 5), 5. / 9}}};
  double h = 0.001;

  double x = l, I = 0;
  while (x < r) {
    double a = x, b = std::min(x + h, r), Ih = 0;
    for (auto rt : roots)
      Ih += rt.w * f(((a + b) + (b - a) * rt.r) / 2);
    I += Ih * (b - a) / 2;
    x = b;
  }

  std::cout << "Значение интеграла: " << std::setprecision(8) << I << '\n';
}
