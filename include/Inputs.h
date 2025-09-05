#pragma once

namespace pd {

struct Inputs {
  int nobs = 0;
  double b = 0.0;
  double b_err = 0.0;
  double eff = 0.5;
  double eff_err = 0.0;
  double exposure_ktyr = 10.0;
  double cl = 0.90;
  int ntoys = 0;
  unsigned seed = 12345;
};

}