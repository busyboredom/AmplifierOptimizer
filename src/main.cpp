#include "../include/main.hpp"
#include "../include/amplifier.hpp"
#include <iostream>
#include <algorithm>
#include <array>
#include <new>

unsigned int Amplifier::beta = parameters::beta;  // Ic/Ib
unsigned int Amplifier::Rload = parameters::Rload;  // Ohms
unsigned int Amplifier::Rsource = parameters::Rsource;  // Ohms
unsigned int Amplifier::max_Vcc = parameters::max_Vcc;  // Volts
unsigned int Amplifier::max_resistor = parameters::max_resistor; // Ohms
float Amplifier::Vt = parameters::Vt;  // Volts
float Amplifier::VBE = parameters::VBE;  // Volts


int main() {
  std::array<Amplifier, parameters::population>  pop;  // Initialize population.
  
  // Evolve the population.
  geneticAlgorithm(pop, parameters::generations);

  // Print the best.
  showBest(pop);
}

void geneticAlgorithm(std::array<Amplifier, parameters::population> (&pop),
                                                         int generations) {
  // Takes an array of amplifier objecs with some Evaluate() function, and 
  // evolves them according to lossFunction().
  
  for (unsigned int i = 0; i < generations; i++) {
    
    std::cout << "\rEvolving population: " << i * 100 / generations << "%";

    // Sort the population from worst to best.
    std::sort(pop.begin(), pop.end(), Amplifier::SortByPerformance);

    // Regenerate the first half from the second half.
    // TODO

    // Evaluate population.
    for (Amplifier amp : pop) {
      // TODO: Thread this.
      amp.Evaluate();
    };
  };
  std::cout << "\nEvolution Complete." << std::endl;
  pop;
}

void showBest(std::array<Amplifier, parameters::population>
                             (&pop)) {
  // TODO
}
