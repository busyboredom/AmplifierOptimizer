// Runs a genetic algorithm to optimize a cascaded BJT amplifier. 

#pragma once

#include "../include/amplifier.hpp"
#include "../include/config.hpp"
#include <vector>


void geneticAlgorithm(std::vector<Amplifier> (&pop), int generations);
  // Takes an array of amplifier objecs with some Evaluate() function, and 
  // evolves them according to Amplifier::SortByPerformance().
  
void showBest(std::vector<Amplifier> (&pop));
  // Print the components and performance metrics of the best amplifier.

void mutate(const Amplifier &amp, Amplifier &new_amp);
  // Takes an Amplifier and returns a new amplifier modified from the one
  // provided.

