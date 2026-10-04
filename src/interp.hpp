#pragma once

#include <vector>

struct point {
  double x;
  double f;
};

struct ppoint {
  double xf, xl;
  double f;
};

std::vector<point> newton_interp_coeff(std::vector<point> data) {
  std::size_t n = data.size();
  std::vector<point> result(n);
  std::vector<ppoint> cmp(n * (n + 1) / 2);
  for (int i = 0; i < data.size(); i++) {
    cmp[i].f = data[i].f;
    cmp[i].xf = data[i].x;
    cmp[i].xl = data[i].x;
  }
  result[0].f = data[0].f;
  result[0].x = data[0].x;
  std::size_t offset = n;
  int ad = n - 1, i = 0, j = 1;
  for (; ad > 0;) {
    if (i == ad) {
      i = 0;
      offset += ad;
      ad--;
      continue;
    }
    cmp[offset + i].f = (cmp[offset + i - ad].f - cmp[offset + i - ad - 1].f) /
                        (cmp[offset + i - ad].xl - cmp[offset + i - ad - 1].xf);
    cmp[offset + i].xf = cmp[offset + i - ad - 1].xf;
    cmp[offset + i].xl = cmp[offset + i - ad].xl;
    if (i == 0) {
      result[j].f = cmp[offset].f;
      result[j].x = data[j].x;
      j++;
    }
    i++;
  }
  return result;
}

double newton_interp_eval(const std::vector<point> &c, double t) {
  double res = c.back().f;
  for (int k = (int)c.size() - 2; k >= 0; k--)
    res = res * (t - c[k].x) + c[k].f;
  return res;
}

struct spline {
  double x;
  double a;
  double b;
  double c;
  double d;
};

std::vector<spline> spline_coeff(std::vector<point> data) {
  if (data.size() < 2)
    return {};
  const std::size_t N = data.size() - 1;

  std::vector<double> h(N + 1), u(N + 1);
  for (std::size_t i = 1; i <= N; i++) {
    h[i] = data[i].x - data[i - 1].x;
    u[i] = (data[i].f - data[i - 1].f) / h[i];
  }

  std::vector<double> c(N + 1, 0.0), p(N + 1, 0.0), q(N + 1, 0.0);
  for (std::size_t j = 1; j + 1 <= N; j++) {
    double lf = h[j] / 6;
    double md = (h[j] + h[j + 1]) / 3;
    double rg = h[j + 1] / 6;
    double rhs = u[j + 1] - u[j];
    double m = md - lf * p[j - 1];
    p[j] = rg / m;
    q[j] = (rhs - lf * q[j - 1]) / m;
  }
  for (std::size_t j = N - 1; j >= 1; j--) {
    c[j] = q[j] - p[j] * c[j + 1];
  }

  std::vector<spline> res(N);
  for (std::size_t i = 1; i <= N; i++) {
    double d = (c[i] - c[i - 1]) / h[i];
    double b = c[i] * h[i] / 3 + c[i - 1] * h[i] / 6 + u[i];
    res[i - 1] = {data[i].x, data[i].f, b, c[i], d};
  }
  return res;
}

double spline_eval(const std::vector<spline> &s, double t) {
  std::size_t k = 0;
  while (k + 1 < s.size() && t < s[k].x)
    k++;
  double dx = t - s[k].x;
  return s[k].a + s[k].b * dx + s[k].c * dx * dx / 2 +
         s[k].d * dx * dx * dx / 6;
}
