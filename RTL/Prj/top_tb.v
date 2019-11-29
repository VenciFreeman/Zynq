`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Shanghai Jiao Tong University
// Engineer: Venci Freeman
// 
// Create Date: 2019/10/24
// Design Name: ME FPGA Project
// Module Name: top
// Project Name: project_1
// Target Devices: zybo
// Tool Versions: 2016.4
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////
module testbench();
  reg clk_125;
  reg rst;
  wire[3:0] led;

  top top(.clk_125(clk_125),
          .rst(rst),
          .led(led));

initial
  begin
    clk_125 = 0;
    rst = 1;
  end
    
always
  begin
    #4 clk_125 <= ~clk_125;
    rst <= 0;
  end
endmodule