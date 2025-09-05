#pragma once

namespace pd {

struct Results {
  double s_up_obs = 0.0;
  double tau_obs = 0.0;
  double s_up_exp_median = 0.0;
  double s_up_exp_p16 = 0.0;
  double s_up_exp_p84 = 0.0;
  double tau_exp_median = 0.0;
  double tau_exp_p16 = 0.0;
  double tau_exp_p84 = 0.0;
};

}