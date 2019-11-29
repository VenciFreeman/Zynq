`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Shanghai Jiao Tong University
// Engineer: Venci Freeman
// 
// Create Date: 2019/10/25
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
module ctrl(clk, rst, data, led);
  input clk, rst;
  input data;
  output [3:0] led;

/////////////////////////////////////////////////////////////////////////////////////////
//
// Parameter definitions
//
/////////////////////////////////////////////////////////////////////////////////////////
parameter IDLE = 4'b0000;

parameter state_0 = 4'b0001;
parameter state_1 = 4'b0010;
parameter state_2 = 4'b0100;
parameter state_3 = 4'b1000;
parameter state_4 = 4'b0000;

/////////////////////////////////////////////////////////////////////////////////////////
//
// Reg definitions
//
/////////////////////////////////////////////////////////////////////////////////////////
  reg [3:0] led, next_state;

/////////////////////////////////////////////////////////////////////////////////////////
//
// Code
//
/////////////////////////////////////////////////////////////////////////////////////////
always @(posedge clk or posedge rst)
  if(rst)
    led <= IDLE;
  else
    led <= next_state;

always @ (data or clk or next_state or led)
  begin
    next_state = 4'bx;
    case(led)
      state_0: if(!data) next_state = state_0;    // LED0 (0)    + 0 = LED0 (0)
               else next_state = state_1;    // LED0 (0)    + 1 = LED1 (01)
      state_1: if(!data) next_state = state_2;    // LED1 (01)   + 0 = LED2 (010)
               else next_state = state_4;    // LED1 (01)   + 1 = OFF  (1)
      state_2: if(!data) next_state = state_3;    // LED2 (010)  + 0 = LED3 (0100)
               else next_state = state_1;    // LED2 (010)  + 1 = LED1 (01)
      state_3: if(!data) next_state = state_0;    // LED3 (0100) + 0 = LED0 (0)
               else next_state = state_1;    // LED3 (0100) + 1 = LED1 (01)
      state_4: if(!data) next_state = state_0;    // OFF  (1)    + 0 = LED0 (0)
               else next_state = state_4;    // OFF  (1)    + 1 = OFF  (1)
      default: next_state = IDLE;
    endcase
  end


endmodule