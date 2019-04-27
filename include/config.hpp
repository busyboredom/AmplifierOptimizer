#pragma once

//---------------Set These According to Your Needs-----------------------------
namespace parameters {
  // Hardware Constraints.
  const double beta = 250;  // Ic/Ib
  const double Rload = 1000;  // Ohms
  const double Rsource = 1000;  // Ohms
  const double max_Vcc = 20;  // Volts
  const double min_Vcc = 1; // Volts
  const double max_resistor = 1000000; // Ohms
  const double Vt = 0.026;  // Volts
  const double VBE = 0.7;  // Volts
  const double min_Vceq = 0.2;  // Volts

  // Algorithm Parameters.
  const unsigned int generations = 1000;
  const unsigned int population = 10000;
  const double max_mutation = 1;  // Set mutation = 0 for constant 100% mutation.
                                 // Do not set above 1.
  const double max_loss = 10000000000;

  // Loss Function Parameters. The loss function will be the sum of all
  // weighted values. Values beyone their min or max will be heavily penalized.
  const double Rin_coefficient = 0;
  const double Rout_coefficient = 0;
  const double Vpp_coefficient = -10000;
  const double power_coefficient = 0;
  const double Av_coefficient = 0;
  const double min_Rin = 10000;  // Ohms
  const double max_Rout = 100;  // Ohms
  const double min_Vpp = 5;  //  Volts
  const double max_power = 0.15;  // Watts
  const double min_Av = 10;
  const double min_max_failure = 10000000;  // Punishment for failing min or max.

}
//-----------------------------------------------------------------------------

