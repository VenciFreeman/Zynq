##Zybo Timing

# define clock and period
create_clock -period 8.000 -name clk_125 -waveform {0.000 4.000} [get_ports clk_125]

# Create a virtual clock for IO constraints

#output delay

