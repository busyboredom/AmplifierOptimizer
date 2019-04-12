#include "../include/amplifier.cpp"

const int beta = 250;
const float Vt = 0.026;  // Volts
const int Rload = 1000;  // Ohms
const float VBE = 0.7;  // Volts
const int Rsource = 1000;  // Ohms

const int generations = 1000;
const int population = 1000;

int main() {

  set_context();
  Amplifier pop[population];
}

void set_context() {
  // Set the appropriate static member variables in the amplifier class.
  Amplifier::beta = beta;
  Amplifier::Vt = Vt;
  Amplifier::Rload = Rload;
  Amplifier::VBE = VBE;
  Amplifier::Rsource = Rsource;
}
