#pragma once

//---------------Set These According to Your Needs-----------------------------
namespace parameters {
  const unsigned int beta = 250;  // Ic/Ib
  const unsigned int Rload = 1000;  // Ohms
  const unsigned int Rsource = 1000;  // Ohms
  const unsigned int max_Vcc = 20;  // Volts
  const unsigned int max_resistor = 1000000; // Ogms
  const float Vt = 0.026;  // Volts
  const float VBE = 0.7;  // Volts

  const unsigned int generations = 10000;
  const unsigned int population = 10000;
}
//-----------------------------------------------------------------------------

