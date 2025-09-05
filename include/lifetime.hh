#pragma once

#include <limits>

namespace pd {

inline double tau_from_s_up(
double s_up,
double eff,
double exposure_ktyr,
double NpPerKt
) {
if (s_up <= 0) {
return std::numeric_limits<double>::infinity();
}
double e = eff > 0 ? eff : 0.0;
double num = NpPerKt * exposure_ktyr * e;
return num / s_up;
}

}
