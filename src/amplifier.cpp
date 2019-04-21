// A cascaded BJT amplifier.

#include "../include/amplifier.hpp"
#include <random>

#include <iostream>

Amplifier::Amplifier()
  : Rin(0), Rout(0), Vpp(0), power(0), gain(0), Icq(0), Vceq(0)
{
}

void Amplifier::randomize() {
  // Randomizes the amplifier.

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
}

bool Amplifier::SortByPerformance(Amplifier const &amp1, Amplifier const &amp2) {
  // TODO: Write a loss function that can be used to compare two amplifiers.
  return amp1.R1 > amp2.R1;
}

void Amplifier::Evaluate() {
  //TODO: Should calculate all the performance metrics.
}

//------------------------------------------Accessors-------------------------------------
// Getters:
unsigned int Amplifier::get_Vcc() {
  return Vcc;
}

unsigned int Amplifier::get_R1() {
  return R1;
}

unsigned int Amplifier::get_R2() {
  return R2;
}

unsigned int Amplifier::get_R3() {
  return R3;
}

unsigned int Amplifier::get_R4() {
  return R4;
}

unsigned int Amplifier::get_Rc1() {
  return Rc1;
}

unsigned int Amplifier::get_Re1() {
  return Re1;
}

unsigned int Amplifier::get_Re2() {
  return Re2;
}

float Amplifier::get_Rin() {
  return Rin;
}

float Amplifier::get_Rout() {
  return Rout;
}

float Amplifier::get_Vpp() {
  return Vpp;
}

float Amplifier::get_power() {
  return power;
}

float Amplifier::get_gain() {
  return gain;
}

float Amplifier::get_Icq() {
  return Icq;
}

float Amplifier::get_Vceq() {
  return Vceq;
}

// Setters:
void Amplifier::set_Vcc(int new_Vcc) {
  Vcc = new_Vcc;
}

void Amplifier::set_R1(int new_R1) {
  R1 = new_R1;
}

void Amplifier::set_R2(int new_R2) {
  R2 = new_R2;
}

void Amplifier::set_R3(int new_R3) {
  R3 = new_R3;
}

void Amplifier::set_R4(int new_R4) {
  R4 = new_R4;
}

void Amplifier::set_Rc1(int new_Rc1) {
  Rc1 = new_Rc1;
}

void Amplifier::set_Re1(int new_Re1) {
  Re1 = new_Re1;
}

void Amplifier::set_Re2(int new_Re2) {
  Re2 = new_Re2;
}
//-----------------------------------------------------------------------------
