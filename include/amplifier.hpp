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
    float Av;
    
    // Verification:
    float Ib1;
    float Ib2;
    float Vceq1;
    float Vceq2;

    // Intermediates:
    float Rpi1;
    float Rpi2;
    float Rth1;
    float Rth2;
    float Icq1;
    float Icq2;
    float Vth1;
    float Vth2;
    float Avs;
    float Av1;
    float Av2;
    float Vo;
    float Vo1;
    float Vpp1;

    //--------------------------Behavior Calculations--------------------------
    void calculate_Rin();
    void calculate_Rth1();
    void calculate_Rpi1();
    void calculate_Icq1();
    void calculate_Ib1();
    void calculate_Vth1();

    void calculate_Rout();
    void calculate_Rpi2();
    void calculate_Icq2();
    void calculate_Ib2();
    void calculate_Vth2();
    void calculate_Rth2();

    void calculate_Av();
    void calculate_Avs();
    void calculate_Av1();
    void calculate_Av2();
    void calculate_Vo1();
    void calculate_Vo();

    void calculate_Vpp();
    void calculate_Vpp1();

    void calculate_Vceq1();
    void calculate_Vceq2();
    void calculate_power();

    //-------------------------------------------------------------------------


  public:
    void Randomize();
      // Randomizes the amplifier.

    bool isActiveMode() const;
      // returns true if the amplifier is in active mode. 

    void Evaluate();
      //TODO: Should calculate all the performance metrics.
    
    static float LossAdd(const float old_loss, const float added_loss);
      // Adds new_loss to loss, as long as the new total loss is not greater 
      // in magnitude than parameters::max_loss.

    static float LossFunction(const Amplifier &amp);
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
    float get_Av() const;
    float get_Icq1() const;
    float get_Vceq1() const;
    float get_Vceq2() const;
    float get_Ib1() const;
    float get_Ib2() const;
    float get_Vth1() const;
    float get_Vth2() const;

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
