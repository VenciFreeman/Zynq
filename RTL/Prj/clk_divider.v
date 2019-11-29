`timescale 1ns / 1ps
/////////////////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////////////////
module clk_divider(clk_125, rst, clk);
  input rst, clk_125;
  output clk;
  
  parameter DIV_CNT = 23'b11111110010100000010101; // Decimal: 8,333,333
  
  reg clk;
  reg[22:0] cnt;

/////////////////////////////////////////////////////////////////////////////////////////
//
// The always part controls signal cnt.
//
/////////////////////////////////////////////////////////////////////////////////////////
always @(posedge clk_125 or posedge rst) 
  if(rst)
    cnt <= 23'b0;
  else if(cnt == DIV_CNT)
    cnt <= 23'b0;
  else
    cnt <= cnt + 1'b1;

/////////////////////////////////////////////////////////////////////////////////////////
//
// The always part controls signal clk.
//
/////////////////////////////////////////////////////////////////////////////////////////
always @(posedge clk_125 or posedge rst)
  if(rst)
    clk <= 0;
  else if(cnt == DIV_CNT)
    clk <= !clk;

endmodule