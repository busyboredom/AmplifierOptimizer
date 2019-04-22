#pragma once

//---------------Set These According to Your Needs-----------------------------
namespace parameters {
  // Hardware Constraints.
  const float beta = 250;  // Ic/Ib
  const float Rload = 1000;  // Ohms
  const float Rsource = 1000;  // Ohms
  const float max_Vcc = 20;  // Volts
  const float min_Vcc = 1; // Volts
  const float max_resistor = 1000000; // Ohms
  const float Vt = 0.026;  // Volts
  const float VBE = 0.7;  // Volts

  // Algorithm Parameters.
  const unsigned int generations = 1000;
  const unsigned int population = 1000;
  const float max_mutation = 1;  // Set mutation = 0 for constant 100% mutation.
                                 // Do not set above 1.
  const float max_loss = 1000000000;

  // Loss Function Parameters. The loss function will be the sum of all
  // weighted values. Values beyone their min or max will be heavily penalized.
  const float Rin_coefficient = 0;
  const float Rout_coefficient = 0;
  const float Vpp_coefficient = 0;
  const float power_coefficient = 0;
  const float Av_coefficient = 0;
  const float min_Rin = 10000;  // Ohms
  const float max_Rout = 100;  // Ohms
  const float min_Vpp = 5;  //  Volts
  const float max_power = 0.15;  // Watts
  const float min_Av = 10;
  const float min_max_failure = 1000000;  // Punishment for failing min or max.

}
//-----------------------------------------------------------------------------

