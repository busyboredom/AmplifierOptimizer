// Runs a genetic algorithm to optimize a cascaded BJT amplifier. 

#pragma once

#include "../include/amplifier.hpp"
#include <array>

//---------------Set These According to Your Needs-----------------------------
namespace parameters {
  const unsigned int beta = 250;  // Ic/Ib
  const unsigned int Rload = 1000;  // Ohms
  const unsigned int Rsource = 1000;  // Ohms
  const unsigned int max_Vcc = 20;  // Volts
  const unsigned int max_resistor = 1000000; // Ogms
  const float Vt = 0.026;  // Volts
  const float VBE = 0.7;  // Volts

  const unsigned int generations = 1000;
  const unsigned int population = 1000;
}
//-----------------------------------------------------------------------------

void geneticAlgorithm(std::array<Amplifier, parameters::population> (&pop), int generations);
  // Takes an array of amplifier objecs with some Evaluate() function, and 
  // evolves them according to lossFunction().
  
bool sortByPerformance();
  // Comparison of two amplifiers for sorting with std::sort.

float lossFunction(Amplifier amp);
  // User defined loss function for evaluation of amplifier performance.

void showBest(std::array<Amplifier, parameters::population> (&pop));
  // Print the components and performance metrics of the best amplifier.
