`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: LZJ
// 
// Create Date: 2018/09/23 09:58:04
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


module top(
    input clk_125,
    input rst,
    output [3:0] led
    );
    
    wire data;
    wire clk;
    clk_divider clk_divider(
      .clk_125(clk_125),
      .rst(rst),
      .clk(clk)
    );
    
    data_generator data_generator(
      .clk(clk),
      .rst(rst),
      .data(data)
    );
    
    ctrl ctrl(
      .clk(clk),
      .rst(rst),
      .data(data),
      .led(led)
    );
    
    ila_0 ila_i0 (
        .clk(clk_125), // input wire clk
    
    
        .probe0(led) // input wire [3:0] probe0
    );
endmodule
