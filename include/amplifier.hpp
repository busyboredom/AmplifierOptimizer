// A cascaded BJT amplifier.

#pragma once

class Amplifier {
  private:
    static unsigned int beta;
    static unsigned int Rload;  // Ohms
    static unsigned int Rsource;  // Ohms
    static unsigned int max_Vcc;  // Volts
    static unsigned int max_resistor; // Ogms
    static float Vt;  // Volts
    static float VBE;  // Volts

    // Design variables:
    // TODO: Getters and setters for these.
    unsigned int Vcc;
    unsigned int R1;
    unsigned int R2;
    unsigned int R3;
    unsigned int R4;
    unsigned int Rc1;
    unsigned int Re1;
    unsigned int Re2;
  
    // Performance Metrics:
    // TODO: Getters (NO setters) for these, and functions to calculate them.
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

    void Evaluate();
    //TODO: Should calculate all the performance metrics. 

    static bool SortByPerformance(const Amplifier &amp1, const Amplifier &amp2);
    // TODO: Write a loss function that can be used to compare two amplifiers.

};
