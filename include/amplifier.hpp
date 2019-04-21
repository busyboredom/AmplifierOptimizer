// A cascaded BJT amplifier.

#pragma once

class Amplifier {
  private:
    static float beta;
    static float Rload;  // Ohms
    static float Rsource;  // Ohms
    static float max_Vcc;  // Volts
    static float max_resistor; // Ogms
    static float Vt;  // Volts
    static float VBE;  // Volts

    // Design variables:
    float Vcc;
    float R1;
    float R2;
    float R3;
    float R4;
    float Rc1;
    float Re1;
    float Re2;
  
    // Behavior Metrics:
    float Rin;
    float Rout;
    float Vpp;
    float power;
    float gain;
    
    //Intermediates:
    float Rpi1;
    float Rpi2;
    float Rth1;
    float Rth2;
    float Icq1;
    float Icq2;
    float Ib1;
    float Ib2;
    float Vceq1;
    float Vceq2;
    float Vth1;
    float Vth2;

    //--------------------------Behavior Calculations--------------------------
    void calculate_Rin();
    
    void calculate_Rth1();

    void calculate_Rpi1();

    void calculate_Icq1();

    void calculate_Ib1();

    void calculate_Vth1();
    //-------------------------------------------------------------------------


  public:
    explicit Amplifier();

    Amplifier(const Amplifier &amp);
      // Sets initial Vcc and resistor values to random values.

    void randomize();
      // Randomizes the amplifier.

    void Evaluate();
      //TODO: Should calculate all the performance metrics.

    static float LossFunction(Amplifier const &amp);
      // A loss function that can be used to compare two amplifiers.

    static bool SortByPerformance(const Amplifier &amp1, const Amplifier &amp2);
      // For use in std::sort. Compared amplifiers according to LossFunction().

    
    //-----------------------------Accessors-----------------------------------
    float get_Vcc() const;
    float get_R1() const;
    float get_R2() const;
    float get_R3() const;
    float get_R4() const;
    float get_Rc1() const;
    float get_Re1() const;
    float get_Re2() const;

    float get_Rin() const;
    float get_Rout() const;
    float get_Vpp() const;
    float get_power() const;
    float get_gain() const;
    float get_Icq1() const;
    float get_Vceq1() const;

    void set_Vcc(float new_Vcc);
    void set_R1(float new_R1);
    void set_R2(float new_R2);
    void set_R3(float new_R3);
    void set_R4(float new_R4);
    void set_Rc1(float new_Rc1);
    void set_Re1(float new_Re1);
    void set_Re2(float new_Re2);
    //-------------------------------------------------------------------------
};
