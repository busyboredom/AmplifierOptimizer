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

    void randomize();
      // Randomizes the amplifier.

    void Evaluate();
    //TODO: Should calculate all the performance metrics. 

    static bool SortByPerformance(const Amplifier &amp1, const Amplifier &amp2);
    // TODO: Write a loss function that can be used to compare two amplifiers.
    
    //-----------------------------Accessors-----------------------------------
    unsigned int get_Vcc();
    unsigned int get_R1();
    unsigned int get_R2();
    unsigned int get_R3();
    unsigned int get_R4();
    unsigned int get_Rc1();
    unsigned int get_Re1();
    unsigned int get_Re2();

    float get_Rin();
    float get_Rout();
    float get_Vpp();
    float get_power();
    float get_gain();
    float get_Icq();
    float get_Vceq();

    void set_Vcc(int new_Vcc);
    void set_R1(int new_R1);
    void set_R2(int new_R2);
    void set_R3(int new_R3);
    void set_R4(int new_R4);
    void set_Rc1(int new_Rc1);
    void set_Re1(int new_Re1);
    void set_Re2(int new_Re2);
    //-------------------------------------------------------------------------
};
