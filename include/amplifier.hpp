// A cascaded BJT amplifier.

#pragma once

class Amplifier {
  static unsigned int beta;
  static unsigned int Rload;  // Ohms
  static unsigned int Rsource;  // Ohms
  static unsigned int max_Vcc;  // Volts
  static unsigned int max_resistor; // Ogms
  static float Vt;  // Volts
  static float VBE;  // Volts

  private:
    // Design variables:
    int Vcc;
    int R1;
    int R2;
    int R3;
    int R4;
    int Rc1;
    int Re1;
    int Re2;
  
    // Performance Metrics:
    float Rin;
    float Rout;
    float Vpp;
    float power;
    float gain;
    float Icq;
    float Vceq;

  public:
    explicit Amplifier();
      // Sets initial Vcc and resistor values to random values.

};
