// A cascaded BJT amplifier.

#pragma once

class Amplifier {
  private:
    static double beta;
    static double Rload;  // Ohms
    static double Rsource;  // Ohms
    static double max_Vcc;  // Volts
    static double max_resistor; // Ogms
    static double Vt;  // Volts
    static double VBE;  // Volts

    // Design variables:
    double Vcc;
    double R1;
    double R2;
    double R3;
    double R4;
    double Rc1;
    double Re1;
    double Re2;
  
    // Behavior Metrics:
    double Rin;
    double Rout;
    double Vpp;
    double power;
    double Av;
    
    // Verification:
    double Ib1;
    double Ib2;
    double Vceq1;
    double Vceq2;

    // Intermediates:
    double Rpi1;
    double Rpi2;
    double Rth1;
    double Rth2;
    double Icq1;
    double Icq2;
    double Vth1;
    double Vth2;
    double Avs;
    double Av1;
    double Av2;
    double Vo;
    double Vo1;
    double Vpp1;

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
    
    static double LossAdd(const double old_loss, const double added_loss);
      // Adds new_loss to loss, as long as the new total loss is not greater 
      // in magnitude than parameters::max_loss.

    static double LossFunction(const Amplifier &amp);
      // A loss function that can be used to compare two amplifiers.

    static bool SortByPerformance(const Amplifier &amp1, const Amplifier &amp2);
      // For use in std::sort. Compared amplifiers according to LossFunction().

    
    //-----------------------------Accessors-----------------------------------
    double get_Vcc() const;
    double get_R1() const;
    double get_R2() const;
    double get_R3() const;
    double get_R4() const;
    double get_Rc1() const;
    double get_Re1() const;
    double get_Re2() const;

    double get_Rin() const;
    double get_Rout() const;
    double get_Vpp() const;
    double get_Vpp1() const;
    double get_power() const;
    double get_Av() const;
    double get_Avs() const;
    double get_Av1() const;
    double get_Av2() const;
    double get_Icq1() const;
    double get_Vceq1() const;
    double get_Vceq2() const;
    double get_Ib1() const;
    double get_Ib2() const;
    double get_Vth1() const;
    double get_Vth2() const;

    void set_Vcc(double new_Vcc);
    void set_R1(double new_R1);
    void set_R2(double new_R2);
    void set_R3(double new_R3);
    void set_R4(double new_R4);
    void set_Rc1(double new_Rc1);
    void set_Re1(double new_Re1);
    void set_Re2(double new_Re2);
    //-------------------------------------------------------------------------
};
