// A cascaded BJT amplifier.

#include "../include/amplifier.hpp"
#include <random>

#include <iostream>

Amplifier::Amplifier() {
  // Set up random number generation.
  std::random_device rd;  // Get random number from hardware.
  std::mt19937 eng(rd());  // Seed the generator.
  // Define Distributions.
  std::uniform_int_distribution<> resistor_distribution(0, max_resistor);
  std::uniform_int_distribution<> Vcc_distribution(0, max_Vcc);

  // Set random Vcc and resistor values.
  Vcc = Vcc_distribution(eng);
  R1 = resistor_distribution(eng);
  R2 = resistor_distribution(eng);
  R3 = resistor_distribution(eng);
  R4 = resistor_distribution(eng);
  Rc1 = resistor_distribution(eng);
  Re1 = resistor_distribution(eng);
  Re2 = resistor_distribution(eng);
  
  std::cout << "Amplifier Initialized\n";
}

bool Amplifier::SortByPerformance(Amplifier const &amp1, Amplifier const &amp2) {
  // TODO: Write a loss function that can be used to compare two amplifiers.
  return amp1.R1 > amp2.R1;
}

void Amplifier::Evaluate() {
  //TODO: Should calculate all the performance metrics.
}

