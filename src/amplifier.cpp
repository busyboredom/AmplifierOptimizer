// A cascaded BJT amplifier.

#include "../include/amplifier.hpp"
#include "../include/config.hpp"
#include <random>

#include <iostream>

void Amplifier::Randomize() {
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

bool Amplifier::isActiveMode() const {
  // returns true if the amplifier is in active mode. 
  if (Vceq1 < parameters::min_Vceq || 
      Vceq2 < parameters::min_Vceq || 
      Vceq1 > Vcc || Vceq2 > Vcc || 
      Ib1 < 0 || Ib2 < 0) {

    return false;
  } else {
    return true;
  }
}

float Amplifier::LossAdd(const float old_loss, const float added_loss) {
  // Adds new_loss to loss, as long as the new total loss is not greater 
  // in magnitude than parameters::max_loss.

  float new_loss;
  // Check too big
  if (old_loss + added_loss > 0) {
    new_loss = std::min(old_loss + added_loss, parameters::max_loss);
    return new_loss;
  };
  // Check too small
  return new_loss = std::max(old_loss, (-1) * parameters::max_loss);
}

float Amplifier::LossFunction(const Amplifier &amp) {
  // A loss function that can be used to compare two amplifiers.

  float loss = 0;

  // Rin loss
  loss = LossAdd(loss, amp.get_Rin() * parameters::Rin_coefficient);
  if (amp.get_Rin() < parameters::min_Rin) {
    loss = LossAdd(loss, parameters::min_max_failure);
  }

  // Rout loss
  loss = LossAdd(loss, amp.get_Rout() * parameters::Rout_coefficient);
  if (amp.get_Rout() > parameters::max_Rout || amp.get_Rout() < 0) {
    loss = LossAdd(loss, parameters::min_max_failure);
  }

  // Av loss
  loss = LossAdd(loss, amp.get_Av() * parameters::Av_coefficient);
  if (amp.get_Av() < parameters::min_Av) {
    loss = LossAdd(loss, parameters::min_max_failure);
  }

  // Vpp loss
  loss = LossAdd(loss, amp.get_Vpp() * parameters::Vpp_coefficient);
  if (amp.get_Vpp() < parameters::min_Vpp) {
    loss = LossAdd( loss, parameters::min_max_failure);
  }

  // power loss
  loss = LossAdd(loss, amp.get_power() * parameters::power_coefficient);
  if (amp.get_power() > parameters::max_power || amp.get_power() < 0) {
    loss = LossAdd(loss, parameters::min_max_failure);
  }

  // Inactive loss / Realism
  if (!amp.isActiveMode() || 
        amp.get_Ib1() > 1 || 
        amp.get_Ib2() > 1 || 
        amp.get_Ib1() < 0.000000001 || 
        amp.get_Ib2() < 0.000000001) {

    loss = LossAdd(0, parameters::max_loss);
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
  calculate_Vth1();  // No requirements.
  calculate_Rth1();  // No requirements.
  calculate_Ib1();  // Needs Vth1, Rth1.
  calculate_Icq1();  // Needs Ib1.
  calculate_Rpi1();  // Needs Icq1. 
  calculate_Rin();  // Needs Rth1, Rpi1.

  calculate_Vth2();  // No requirements.
  calculate_Rth2();  // No requirements.
  calculate_Ib2();  // Needs Vth2, Rth2.
  calculate_Icq2();  // Needs Ib2.
  calculate_Rpi2();  // Needs Icq2.
  calculate_Rout();  // Needs Rpi2, Rth2.

  calculate_Vo();  // Needs Ib2.
  calculate_Vo1();  // Needs Ib2, Rpi2.
  calculate_Av2();  // Needs Vo, Vo1.
  calculate_Av1();  // Needs Vo1, Ib1, Rpi1.
  calculate_Avs();  // Needs Rin.
  calculate_Av();  // Needs Avs, Av1, Av2.

  calculate_Vpp1();  // Needs Icq1, Rth2, Rpi2.
  calculate_Vpp();  // Needs Vpp1, Av2.

  calculate_Vceq1();  // Needs Icq1, Ib1.
  calculate_Vceq2();  // Needs Ib2.
  calculate_power();  // Needs Ib1, Ib2, Vceq1, Icq1, Vceq2, Icq2.

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

//Vpp----------------------------------

void Amplifier::calculate_Vpp() {
  Vpp = Vpp1 * Av2;
}

void Amplifier::calculate_Vpp1() {
  Vpp1 = 2 * Icq1 * 1 / (1/Rc1 + 1/Rth2 + 1/Rpi2);
}

//power--------------------------------

void Amplifier::calculate_power() {
  power = parameters::VBE * (Ib1 + Ib2) + Vceq1 * Icq1 + Vceq2 * Icq2;
}

void Amplifier::calculate_Vceq1() {
  Vceq1 = Vcc - Icq1 * Rc1 - (parameters::beta + 1) * Ib1 * Re1;
}

void Amplifier::calculate_Vceq2() {
  Vceq2 = Vcc - (parameters::beta + 1) * Ib2 * Re2;
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

float Amplifier::get_Ib1() const{
  return Icq1;
}

float Amplifier::get_Vceq1() const{
  return Vceq1;
}

float Amplifier::get_Ib2() const{
  return Icq2;
}

float Amplifier::get_Vceq2() const{
  return Vceq2;
}

float Amplifier::get_Vth1() const{
  return Vth1;
}

float Amplifier::get_Vth2() const{
  return Vth2;
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
