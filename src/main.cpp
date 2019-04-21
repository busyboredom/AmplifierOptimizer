#include "../include/main.hpp"
#include "../include/amplifier.hpp"
#include "../include/config.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <array>
#include <new>

// Setting static member variables.
float Amplifier::beta = parameters::beta;  // Ic/Ib
float Amplifier::Rload = parameters::Rload;  // Ohms
float Amplifier::Rsource = parameters::Rsource;  // Ohms
float Amplifier::max_Vcc = parameters::max_Vcc;  // Volts
float Amplifier::max_resistor = parameters::max_resistor; // Ohms
float Amplifier::Vt = parameters::Vt;  // Volts
float Amplifier::VBE = parameters::VBE;  // Volts

int main() {
  // Initialize population.
  std::array<Amplifier, parameters::population> pop;
  std::cout << "Population Initialized" << std::endl;

    
  // Evolve the population.
  geneticAlgorithm(pop, parameters::generations);

  // Print the best.
  showBest(pop);
}

void geneticAlgorithm(std::array<Amplifier, parameters::population> (&pop),
                                                         int generations) {
  // Takes an array of amplifier objecs with some Evaluate() function, and 
  // evolves them according to lossFunction().
  
  // Randomize the population.
  for (unsigned int i = 0; i < parameters::population; i++) {
    pop[i].randomize();
    std::cout << "\rRandomizing population: ";
    std::cout << i * 100 / parameters::population + 1 << "%";
  }
  std::cout << std::endl;

  
  for (unsigned int i = 0; i < generations; i++) {
    
    std::cout << "\rEvolving population: " << i * 100 / generations + 1 << "%";

    // Sort the population from worst to best.
    std::sort(pop.begin(), pop.end(), Amplifier::SortByPerformance);
    std::cout << " Loss: " << Amplifier::LossFunction(pop[parameters::population - 1]);

    // Regenerate the first half from the second half.
    for (unsigned int i = 0; i <= parameters::population / 2; i++) {
      mutate(pop[i + parameters::population / 2], pop[i]);
    };

    // Evaluate population.
    for (unsigned int i = 0; i < parameters::population; i++) {
      // TODO: Thread this.
      pop[i].Evaluate();
    };
  };
  std::cout << std::endl;
}

void showBest(std::array<Amplifier, parameters::population>(&pop)) {
  // Print the components and performance metrics of the best amplifier.

  // Sort the population from worst to best.
  std::sort(pop.begin(), pop.end(), Amplifier::SortByPerformance);
  
  // Get best amplifier.
  Amplifier best_amplifier(pop[parameters::population - 1]);

  // Print its stats.
  std::cout << "Highest Performing Amplifier\n";
  std::cout << "  Components:\n";
  std::cout << "    Vcc: " << best_amplifier.get_Vcc() << "\n";
  std::cout << "    R1: " << best_amplifier.get_R1() << "\n";
  std::cout << "    R2: " << best_amplifier.get_R2() << "\n";
  std::cout << "    R3: " << best_amplifier.get_R3() << "\n";
  std::cout << "    R4: " << best_amplifier.get_R4() << "\n";
  std::cout << "    Rc1: " << best_amplifier.get_Rc1() << "\n";
  std::cout << "    Re1: " << best_amplifier.get_Re1() << "\n";
  std::cout << "    Re2: " << best_amplifier.get_Re2() << "\n";
  std::cout << "  Performance:\n";
  std::cout << "    Rin: " << best_amplifier.get_Rin() << "\n";

}

void mutate(const Amplifier &amp, Amplifier &new_amp) {
  // Takes an Amplifier and returns a new amplifier modified from the one
  // provided.
  std::random_device rd;  // Get random number from hardware.
  std::mt19937 eng(rd());  // Seed the generator.
    
  std::uniform_real_distribution<>  // Define Distribution.
    mutation_distribution((-1)*parameters::max_mutation, 
                               parameters::max_mutation);
  
  // Set new Vcc and resistor values.
  new_amp.set_Vcc(std::min((1 + (float) mutation_distribution(eng)) * amp.get_Vcc(), 
                                                       parameters::max_Vcc));
  new_amp.set_R1(std::min((1 + (float) mutation_distribution(eng)) * amp.get_R1(), 
                                                parameters::max_resistor));
  new_amp.set_R2(std::min((1 + (float) mutation_distribution(eng)) * amp.get_R2(), 
                                                parameters::max_resistor));
  new_amp.set_R3(std::min((1 + (float) mutation_distribution(eng)) * amp.get_R3(), 
                                                parameters::max_resistor));
  new_amp.set_R4(std::min((1 + (float) mutation_distribution(eng)) * amp.get_R4(), 
                                                parameters::max_resistor));
  new_amp.set_Rc1(std::min((1 + (float) mutation_distribution(eng)) * amp.get_Rc1(), 
                                                  parameters::max_resistor));
  new_amp.set_Re1(std::min((1 + (float) mutation_distribution(eng)) * amp.get_Re1(), 
                                                  parameters::max_resistor));
  new_amp.set_Re2(std::min((1 + (float) mutation_distribution(eng)) * amp.get_Re2(), 
                                                  parameters::max_resistor));
}
