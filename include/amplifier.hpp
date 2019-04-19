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
    int Vcc;
    int R1;
    int R2;
    int R3;
    int R4;
    int Rc1;
    int Re1;
    int Re2;
  
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

};
