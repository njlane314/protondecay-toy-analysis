#pragma once

#include "inputs.hh"
#include "results.hh"
#include "poisson_upper_limit.hh"
#include "lifetime.hh"
#include "constants.hh"

#include <random>
#include <algorithm>
#include <vector>
#include <cmath>

namespace pd {

namespace detail {

inline double trunc_gauss(
  std::mt19937& rng,
  double mean,
  double sigma,
  double lo,
  double hi
) {
  if (sigma <= 0) {
    if (mean < lo) return lo;
    if (mean > hi) return hi;
    return mean;
  }
  std::normal_distribution<double> N(mean, sigma);
  for (int i = 0; i < 100000; ++i) {
    double x = N(rng);
    if (x >= lo && x <= hi) return x;
  }
  if (mean < lo) return lo;
  if (mean > hi) return hi;
  return mean;
}

inline double quantile(std::vector<double>& v, double p) {
  size_t k = static_cast<size_t>(llround(p * (v.size() - 1)));
  if (k >= v.size()) k = v.size() - 1;
  std::nth_element(v.begin(), v.begin() + k, v.end());
  return v[k];
}

}

inline void expected_bands(const Inputs& in, Results& out) {
  if (in.ntoys <= 0) return;

  std::mt19937 rng(in.seed);
  std::poisson_distribution<int> Pois;

  std::vector<double> sv;
  sv.reserve(in.ntoys);
  std::vector<double> tv;
  tv.reserve(in.ntoys);

  for (int i = 0; i < in.ntoys; ++i) {
    double btoy = detail::trunc_gauss(rng, in.b, in.b_err, 0.0, 1e12);
    double etoy = detail::trunc_gauss(rng, in.eff, in.eff_err, 0.0, 1.0);

    Pois = std::poisson_distribution<int>(btoy > 0 ? btoy : 0.0);
    int ntoy = Pois(rng);

    double sup = s_up_known_b(ntoy, btoy, in.cl);
    double tau = tau_from_s_up(sup, etoy, in.exposure_ktyr, NpPerKtArgon);

    sv.push_back(sup);
    tv.push_back(tau);
  }

  auto sv2 = sv;
  auto tv2 = tv;

  out.s_up_exp_median = detail::quantile(sv2, 0.50);
  out.s_up_exp_p16 = detail::quantile(sv, 0.16);
  out.s_up_exp_p84 = detail::quantile(sv, 0.84);
  out.tau_exp_median = detail::quantile(tv2, 0.50);
  out.tau_exp_p16 = detail::quantile(tv, 0.16);
  out.tau_exp_p84 = detail::quantile(tv, 0.84);
}

inline void observed_with_systematics(const Inputs& in, Results& out) {
  if (in.b_err <= 0 && in.eff_err <= 0) return;

  std::mt19937 rng(in.seed + 1);

  double btoy = detail::trunc_gauss(rng, in.b, in.b_err, 0.0, 1e12);
  double etoy = detail::trunc_gauss(rng, in.eff, in.eff_err, 0.0, 1.0);

  double sup = s_up_known_b(in.nobs, btoy, in.cl);

  out.s_up_obs = sup;
  out.tau_obs = tau_from_s_up(sup, etoy, in.exposure_ktyr, NpPerKtArgon);
}

}