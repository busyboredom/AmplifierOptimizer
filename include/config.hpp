#pragma once

//---------------Set These According to Your Needs-----------------------------
namespace parameters {
  // Hardware Constraints.
  const float beta = 250;  // Ic/Ib
  const float Rload = 1000;  // Ohms
  const float Rsource = 1000;  // Ohms
  const float max_Vcc = 20;  // Volts
  const float min_Vcc = 1; // Volts
  const float max_resistor = 1000000; // Ogms
  const float Vt = 0.026;  // Volts
  const float VBE = 0.7;  // Volts

  // Algorithm Parameters.
  const unsigned int generations = 1000;
  const unsigned int population = 5000;
  const float max_mutation = 0.5;

  // Loss Function Parameters. The loss function will be the sum of all
  // weighted values. Values beyone their min or max will be heavily penalized.
  const float Rin_coefficient = -0.0001;
  const float Rout_coefficient = 0.001;
  const float Vpp_coefficient = -1;
  const float power_coefficient = 1;
  const float Av_coefficient = -0.1;
  const float min_Rin = 1000;  // Ohms
  const float max_Rout = 10;  // Ohms
  const float min_Vpp = 5;  //  Volts
  const float power_max = 0.15;  // Watts
  const float min_Av = 10;
  const float min_max_failure = 100000;  // Punishment for failing min or max.

}
//-----------------------------------------------------------------------------

