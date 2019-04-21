// A cascaded BJT amplifier.

#include "../include/amplifier.hpp"
#include "../include/config.hpp"
#include <random>

#include <iostream>

Amplifier::Amplifier() {};

Amplifier::Amplifier(const Amplifier &amp) {
    // Design variables:
    Vcc = amp.Vcc;
    R1 = amp.R1;
    R2 = amp.R2;
    R3 = amp.R3;
    R4 = amp.R4;
    Rc1 = amp.Rc1;
    Re1 = amp.Re1;
    Re2 = amp.Re2;
  
    // Behavior Metrics:
    Rin = amp.Rin;
    Rout = amp.Rout;
    Vpp = amp.Vpp;
    power = amp.power;
    Av = amp.Av;

};

void Amplifier::randomize() {
  // Randomizes the amplifier.

  // Set up random number generation.
  std::random_device rd;  // Get random number from hardware.
  std::mt19937 eng(rd());  // Seed the generator.
  // Define Distributions.
  std::uniform_int_distribution<> resistor_distribution(0, max_resistor);
  std::uniform_int_distribution<> Vcc_distribution(1, max_Vcc);

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

float Amplifier::LossFunction(Amplifier const &amp) {
  // A loss function that can be used to compare two amplifiers.

  float loss = 0;
  // Rin loss
  loss += amp.Rin * parameters::Rin_coefficient;
  if (amp.Rin < parameters::min_Rin || amp.Rin < 0) {
    loss += parameters::min_max_failure;
  }

  // Rout loss
  loss += amp.Rout * parameters::Rout_coefficient;
  if (amp.Rout > parameters::max_Rout || amp.Rout < 0) {
    loss += parameters::min_max_failure;
  }

  // Vth1 loss
  if (amp.Vth1 < parameters::VBE) {
    loss += parameters::min_max_failure;
  }

  // Vth2 loss
  if (amp.Vth2 < parameters::VBE) {
    loss += parameters::min_max_failure;
  }

  // Av loss
  loss += amp.Av * parameters::Av_coefficient;
  if (amp.Av < parameters::min_Av) {
    loss += parameters::min_max_failure;
  }


  return loss;
}

bool Amplifier::SortByPerformance(Amplifier const &amp1, Amplifier const &amp2) {
  // For use in std::sort. Compared amplifiers according to LossFunction().
  float loss1 = LossFunction(amp1);
  float loss2 = LossFunction(amp2);
  return loss1 > loss2;
}

void Amplifier::Evaluate() {
  // Calculates all the behavior metrics.
  calculate_Vth1();
  calculate_Ib1();
  calculate_Icq1();
  calculate_Rpi1();
  calculate_Rth1();
  calculate_Rin();

  calculate_Vth2();
  calculate_Rth2();
  calculate_Ib2();
  calculate_Icq2();
  calculate_Rpi2();
  calculate_Rout();

  calculate_Vo();
  calculate_Vo1();
  calculate_Av2();
  calculate_Av1();
  calculate_Avs();
  calculate_Av();
  //std::cout << Rpi1 << std:: endl;
} 

//--------------------------Behavior Calculations------------------------------

// Rin --------------------------------
void Amplifier::calculate_Rin() {
  Rin = 1 / (1/Rth1 + 1/Rpi1);
}
    
void Amplifier::calculate_Rth1() {
  Rth1 = 1 / (1/R1 + 1/R2);
}

void Amplifier::calculate_Rpi1() {
  Rpi1 = parameters::beta * parameters::Vt / Icq1;
}

void Amplifier::calculate_Icq1() {
  Icq1 = parameters::beta * Ib1;
}

void Amplifier::calculate_Ib1() {
  float numerator = Vth1 - parameters::VBE;
  float denominator = Rth1 + (parameters::beta + 1) * Re1;
  Ib1 = numerator / denominator;
}

void Amplifier::calculate_Vth1() {
  Vth1 = Vcc * R2 / (R1 + R2);
}

//Rout --------------------------------

void Amplifier::calculate_Rout() {
  Rout = 1 / (1/Re2 + 1/((Rpi2 + 1 / (1/Rc1 + 1/Rth2)) / (parameters::beta + 1)));
}

void Amplifier::calculate_Rpi2() {
  Rpi2 = parameters::beta * parameters::Vt / Icq2;
}

void Amplifier::calculate_Icq2() {
  Icq2 = parameters::beta * Ib2;
}

void Amplifier::calculate_Ib2() {
  float numerator = Vth2 - parameters::VBE;
  float denominator = Rth2 + (parameters::beta + 1) * Re2;
  Ib2 = numerator / denominator;
}

void Amplifier::calculate_Vth2() {
  Vth2 = Vcc * R4 / (R3 + R4);
}

void Amplifier::calculate_Rth2() {
  Rth2 = 1 / (1/R3 + 1/R4);
}

//Av-----------------------------------

void Amplifier::calculate_Av() {
  Av = Avs * Av1 * Av2;
}

void Amplifier::calculate_Avs() {
  Avs = Rin / (parameters::Rsource + Rin);
}

void Amplifier::calculate_Av1() {
  Av1 = Vo1 / (Ib1 * Rpi1);
}

void Amplifier::calculate_Av2() {
  Av2 = Vo / Vo1;
}

void Amplifier::calculate_Vo1() {
  float beta = parameters::beta;
  float Rload = parameters::Rload;
  Vo1 = Ib2 * (Rpi2 + (beta + 1) * 1 / (1/Re2 + 1/Rload));
}

void Amplifier::calculate_Vo() {
  float beta = parameters::beta;
  float Rload = parameters::Rload;
  Vo = (beta + 1) * Ib2 * 1 / (1/Re2 + 1/Rload);
}
//-----------------------------------------------------------------------------

//--------------------------------Accessors------------------------------------
// Getters:
float Amplifier::get_Vcc() const {
  return Vcc;
}

float Amplifier::get_R1() const{
  return R1;
}

float Amplifier::get_R2() const{
  return R2;
}

float Amplifier::get_R3() const{
  return R3;
}

float Amplifier::get_R4() const{
  return R4;
}

float Amplifier::get_Rc1() const{
  return Rc1;
}

float Amplifier::get_Re1() const{
  return Re1;
}

float Amplifier::get_Re2() const{
  return Re2;
}

float Amplifier::get_Rin() const{
  return Rin;
}

float Amplifier::get_Rout() const{
  return Rout;
}

float Amplifier::get_Vpp() const{
  return Vpp;
}

float Amplifier::get_power() const{
  return power;
}

float Amplifier::get_Av() const{
  return Av;
}

float Amplifier::get_Icq1() const{
  return Icq1;
}

float Amplifier::get_Vceq1() const{
  return Vceq1;
}

// Setters:
void Amplifier::set_Vcc(float new_Vcc) {
  Vcc = new_Vcc;
}

void Amplifier::set_R1(float new_R1) {
  R1 = new_R1;
}

void Amplifier::set_R2(float new_R2) {
  R2 = new_R2;
}

void Amplifier::set_R3(float new_R3) {
  R3 = new_R3;
}

void Amplifier::set_R4(float new_R4) {
  R4 = new_R4;
}

void Amplifier::set_Rc1(float new_Rc1) {
  Rc1 = new_Rc1;
}

void Amplifier::set_Re1(float new_Re1) {
  Re1 = new_Re1;
}

void Amplifier::set_Re2(float new_Re2) {
  Re2 = new_Re2;
}
//-----------------------------------------------------------------------------
