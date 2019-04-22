AmplifierOptimizer generates simple cascaded amplifiers according to a
user-defined loss function using a genetic algorithm. 

The amplifier consistes of two cascaded BJT amplifiers. The first is a
common emitter BJT amplifier with voltage diviter biasing and an emitter 
resistor with bipass capacitor. 

The second amplifier, isolated from the first by a coupling capacitor, is a 
identical to the first but with a common collector, no collector resistor,
and no bipass capacitor on the emitter resistor.

Your loss function and some hardware parameters, as well as some algorithm
parameters (population, generations, etc.) can be set in config.hpp.

Build with Cmake and run with ./src/AmplifierOptimizer.
