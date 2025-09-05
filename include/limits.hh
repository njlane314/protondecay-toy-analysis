#pragma once

#include <Math/ProbFunc.h>

namespace pd {

inline double mu_up_known_b(int nobs, double cl) {
double lo = 0.0;
double hi = (nobs + 10.0 > 5.0 ? nobs + 10.0 : 5.0);
while (ROOT::Math::poisson_cdf(nobs, hi) < cl) {
hi *= 2.0;
}
for (int it = 0; it < 100; ++it) {
double mid = 0.5 * (lo + hi);
double cdf = ROOT::Math::poisson_cdf(nobs, mid);
if (cdf < cl) {
lo = mid;
} else {
hi = mid;
}
}
return 0.5 * (lo + hi);
}

inline double s_up_known_b(int nobs, double b, double cl) {
double mu = mu_up_known_b(nobs, cl);
double bb = b > 0 ? b : 0.0;
double s = mu - bb;
return s > 0 ? s : 0.0;
}

}
