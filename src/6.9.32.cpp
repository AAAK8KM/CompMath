#include "interp.hpp"
#include <cstdio>

int main() {
  std::vector<point> data = {
      {1910, 92228496},  {1920, 106021537}, {1930, 123202624},
      {1940, 132164569}, {1950, 151325798}, {1960, 179323175},
      {1970, 203211926}, {1980, 226545805}, {1990, 248709873},
      {2000, 281421906},
  };

  auto nc = newton_interp_coeff(data);
  std::printf("Коэффициенты Ньютона a_k = f[x_0..x_k]:\n");
  for (std::size_t k = 0; k < nc.size(); k++)
    std::printf("  k=%zu  x_k=%.0f  a_k=%.10e\n", k, nc[k].x, nc[k].f);

  auto sc = spline_coeff(data);
  std::printf("\nКоэффициенты сплайна (s_i по степеням (x - x_i)):\n");
  std::printf("  %-6s %-16s %-16s %-16s %-16s\n", "x_i", "a", "b", "c", "d");
  for (const auto &s : sc)
    std::printf("  %-6.0f %-16.8e %-16.8e %-16.8e %-16.8e\n", s.x, s.a, s.b,
                s.c, s.d);

  double t = 2010;
  std::printf("\nНаселение в 2010:\n");
  std::printf("  Ньютон: %.0f\n", newton_interp_eval(nc, t));
  std::printf("  Сплайн: %.0f\n", spline_eval(sc, t));
  return 0;
}
