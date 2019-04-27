#include "../include/main.hpp"
#include "../include/amplifier.hpp"
#include "../include/config.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <vector>
#include <chrono>
#include <thread>

// Setting static member variables.
double Amplifier::beta = parameters::beta;  // Ic/Ib
double Amplifier::Rload = parameters::Rload;  // Ohms
double Amplifier::Rsource = parameters::Rsource;  // Ohms
double Amplifier::max_Vcc = parameters::max_Vcc;  // Volts
double Amplifier::max_resistor = parameters::max_resistor; // Ohms
double Amplifier::Vt = parameters::Vt;  // Volts
double Amplifier::VBE = parameters::VBE;  // Volts

int main() {
  // Initialize population.
  std::vector<Amplifier> pop;
  pop.reserve(parameters::population);
  pop.resize(parameters::population);
  std::cout << std::fixed << "Population of " << pop.size() << " Initialized" << std::endl;

    
  // Evolve the population.
  geneticAlgorithm(pop, parameters::generations);

  // Print the best.
  showBest(pop);
}

void geneticAlgorithm(std::vector<Amplifier> (&pop), int generations) {
  // Takes an array of amplifier objecs with some Evaluate() function, and 
  // evolves them according to lossFunction().
  
  // Randomize the population.
  for (unsigned int i = 0; i < parameters::population; i++) {
    pop[i].Randomize();
    std::cout << "\rRandomizing population: ";
    std::cout << i * 100.0 / parameters::population << "%";
  }
  std::cout << std::endl;

  
  for (unsigned int gen = 0; gen < parameters::generations; gen++) {
    
    std::cout << "\rEvolving population: " << gen * 100.0 / parameters::generations << "\%";


    // Evaluate population.
    for (unsigned int j = 0; j < parameters::population; j++) {
      // TODO: Thread this.
      pop[j].Evaluate();
    };

    // Sort the population from worst to best.
    std::sort(pop.begin(), pop.end(), Amplifier::SortByPerformance);
    std::cout << " Loss: " << Amplifier::LossFunction(pop[parameters::population - 1]);
    std::cout.flush();

    // Regenerate the first half from the second half.
    if (parameters::max_mutation != 0) {
      for (unsigned int j = 0; j <= parameters::population / 2; j++) {
        mutate(pop[j + parameters::population / 2], pop[j]);
      }; 
    } else {
      for (unsigned int j = 0; j < parameters::population - 1; j++) {
        pop[j].Randomize();
      };
    };
  };
  std::cout << std::endl;
}

void showBest(std::vector<Amplifier> (&pop)) {
  // Print the components and performance metrics of the best amplifier.

  // Sort the population from worst to best.
  std::sort(pop.begin(), pop.end(), Amplifier::SortByPerformance);
  
  // Get best amplifier.
  Amplifier best_amplifier(pop[parameters::population - 1]);

  // Print its stats.
  std::cout << "Highest Performing Amplifier\n";
  std::cout << "    Components:\n";
  std::cout << "        Vcc: " << best_amplifier.get_Vcc() << "\n";
  std::cout << "        R1: " << best_amplifier.get_R1() << "\n";
  std::cout << "        R2: " << best_amplifier.get_R2() << "\n";
  std::cout << "        R3: " << best_amplifier.get_R3() << "\n";
  std::cout << "        R4: " << best_amplifier.get_R4() << "\n";
  std::cout << "        Rc1: " << best_amplifier.get_Rc1() << "\n";
  std::cout << "        Re1: " << best_amplifier.get_Re1() << "\n";
  std::cout << "        Re2: " << best_amplifier.get_Re2() << "\n";
  std::cout << "    Performance:\n";
  std::cout << "        Rin: " << best_amplifier.get_Rin() << "\n";
  std::cout << "        Rout: " << best_amplifier.get_Rout() << "\n";
  std::cout << "        Av: " << best_amplifier.get_Av() << "\n";
  std::cout << "        Vpp: " << best_amplifier.get_Vpp() << "\n";
  std::cout << "        Power: " << best_amplifier.get_power() << "\n";
  std::cout << "    Verification:\n";
  std::cout << "        Vceq1: " << best_amplifier.get_Vceq1() << "\n";
  std::cout << "        Ib1: " << best_amplifier.get_Ib1() << "\n";
  std::cout << "        Vceq2: " << best_amplifier.get_Vceq2() << "\n";
  std::cout << "        Ib2: " << best_amplifier.get_Ib2() << "\n";
  std::cout << "        Avs: " << best_amplifier.get_Avs() << "\n";
  std::cout << "        Av1: " << best_amplifier.get_Av1() << "\n";
  std::cout << "        Av2: " << best_amplifier.get_Av2() << "\n";
  std::cout << "        Vpp1: " << best_amplifier.get_Vpp1() << "\n";


  std::cout.flush();

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
  double new_Vcc = (1 + (double) mutation_distribution(eng)) * amp.get_Vcc();
  new_Vcc = std::min(new_Vcc, parameters::max_Vcc);
  new_Vcc = std::max(new_Vcc, parameters::min_Vcc);
  new_amp.set_Vcc(new_Vcc);

  new_amp.set_R1(std::min((1 + (double) mutation_distribution(eng)) * amp.get_R1(), 
                                                parameters::max_resistor));
  new_amp.set_R2(std::min((1 + (double) mutation_distribution(eng)) * amp.get_R2(), 
                                                parameters::max_resistor));
  new_amp.set_R3(std::min((1 + (double) mutation_distribution(eng)) * amp.get_R3(), 
                                                parameters::max_resistor));
  new_amp.set_R4(std::min((1 + (double) mutation_distribution(eng)) * amp.get_R4(), 
                                                parameters::max_resistor));
  new_amp.set_Rc1(std::min((1 + (double) mutation_distribution(eng)) * amp.get_Rc1(), 
                                                  parameters::max_resistor));
  new_amp.set_Re1(std::min((1 + (double) mutation_distribution(eng)) * amp.get_Re1(), 
                                                  parameters::max_resistor));
  new_amp.set_Re2(std::min((1 + (double) mutation_distribution(eng)) * amp.get_Re2(), 
                                                  parameters::max_resistor));
}
