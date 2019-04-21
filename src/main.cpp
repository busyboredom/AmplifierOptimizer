#include "../include/main.hpp"
#include "../include/amplifier.hpp"
#include "../include/config.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <array>
#include <new>

// Setting static member variables.
unsigned int Amplifier::beta = parameters::beta;  // Ic/Ib
unsigned int Amplifier::Rload = parameters::Rload;  // Ohms
unsigned int Amplifier::Rsource = parameters::Rsource;  // Ohms
unsigned int Amplifier::max_Vcc = parameters::max_Vcc;  // Volts
unsigned int Amplifier::max_resistor = parameters::max_resistor; // Ohms
float Amplifier::Vt = parameters::Vt;  // Volts
float Amplifier::VBE = parameters::VBE;  // Volts

int main() {
  // Initialize population.
  std::array<Amplifier, parameters::population> pop;
  std::cout << "Population Initialized" << std::endl;

  // Randomize the population.
  for (unsigned int i = 0; i < parameters::population; i++) {
    pop[i].randomize();
    std::cout << "\rRandomizing population: ";
    std::cout << i * 100 / parameters::population + 1 << "%";
  }
  std::cout << std::endl;
  
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
    
    std::cout << "\rEvolving population: " << i * 100 / generations + 1 << "%";

    // Sort the population from worst to best.
    std::sort(pop.begin(), pop.end(), Amplifier::SortByPerformance);

    // Regenerate the first half from the second half.
    for (unsigned int i = 0; i < parameters::population / 2; i++) {
      pop[i] = mutate(pop[i + parameters::population / 2]);
    };

    // Evaluate population.
    for (Amplifier amp : pop) {
      // TODO: Thread this.
      amp.Evaluate();
    };
  };
  std::cout << std::endl;
}

void showBest(std::array<Amplifier, parameters::population>
                             (&pop)) {
  // TODO
}

Amplifier mutate(Amplifier amp) {
  // Takes an Amplifier and returns a new amplifier modified from the one
  // provided.
  std::random_device rd;  // Get random number from hardware.
  std::mt19937 eng(rd());  // Seed the generator.
    
  std::uniform_int_distribution<>  // Define Distribution.
    mutation_distribution((-1)*parameters::max_mutation, 
                               parameters::max_mutation);
  
  Amplifier new_amp;  // New amplifier to be mutated from old amp.

  // Set new Vcc and resistor values.
  new_amp.set_Vcc(std::min((1 + mutation_distribution(eng)) * amp.get_Vcc(), 
                                                       parameters::max_Vcc));
  new_amp.set_R1(std::min((1 + mutation_distribution(eng)) * amp.get_R1(), 
                                                parameters::max_resistor));
  new_amp.set_R2(std::min((1 + mutation_distribution(eng)) * amp.get_R2(), 
                                                parameters::max_resistor));
  new_amp.set_R3(std::min((1 + mutation_distribution(eng)) * amp.get_R3(), 
                                                parameters::max_resistor));
  new_amp.set_R4(std::min((1 + mutation_distribution(eng)) * amp.get_R4(), 
                                                parameters::max_resistor));
  new_amp.set_Rc1(std::min((1 + mutation_distribution(eng)) * amp.get_Rc1(), 
                                                  parameters::max_resistor));
  new_amp.set_Re1(std::min((1 + mutation_distribution(eng)) * amp.get_Re1(), 
                                                  parameters::max_resistor));
  new_amp.set_Re2(std::min((1 + mutation_distribution(eng)) * amp.get_Re2(), 
                                                  parameters::max_resistor));

  return new_amp;
}
