#pragma once

#include "counting_analysis.hh"
#include "inputs.hh"

#include <getopt.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
pd::Inputs in;
std::string out = "limit.root";

static struct option longopts[] = {
{"nobs", 1, 0, 'n'},
{"b", 1, 0, 'b'},
{"b-err", 1, 0, 1},
{"eff", 1, 0, 'e'},
{"eff-err", 1, 0, 2},
{"exposure", 1, 0, 'x'},
{"cl", 1, 0, 'c'},
{"toys", 1, 0, 't'},
{"seed", 1, 0, 's'},
{"out", 1, 0, 'o'},
{0, 0, 0, 0}
};

int opt;
int idx = 0;
while ((opt = getopt_long(argc, argv, "", longopts, &idx)) != -1) {
switch (opt) {
case 'n': in.nobs = std::stoi(optarg); break;
case 'b': in.b = std::stod(optarg); break;
case 1: in.b_err = std::stod(optarg); break;
case 'e': in.eff = std::stod(optarg); break;
case 2: in.eff_err = std::stod(optarg); break;
case 'x': in.exposure_ktyr = std::stod(optarg); break;
case 'c': in.cl = std::stod(optarg); break;
case 't': in.ntoys = std::stoi(optarg); break;
case 's': in.seed = (unsigned) std::stoul(optarg); break;
case 'o': out = optarg; break;
default: return 1;
}
}

pd::CountingAnalysis A;
auto R = A.run(in, out);

std::cout.setf(std::ios::scientific);
std::cout.precision(3);

std::cout << "s_up_obs " << R.s_up_obs << "
";
std::cout << "tau_obs " << R.tau_obs << "
";

if (in.ntoys > 0) {
std::cout << "s_up_exp_med "
<< R.s_up_exp_median << " "
<< R.s_up_exp_p16 << " "
<< R.s_up_exp_p84 << "
";

std::cout << "tau_exp_med "
<< R.tau_exp_median << " "
<< R.tau_exp_p16 << " "
<< R.tau_exp_p84 << "
";
}

return 0;
}
