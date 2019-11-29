`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: LZJ
// 
// Create Date: 2018/09/23 09:31:16
// Design Name: ME FPGA Project
// Module Name: data_generator
// Project Name: project_1
// Target Devices: zybo
// Tool Versions: 2016.4
// Description: generate data from ROM, 1 bit data per clk
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module data_generator(
    input clk,
    input rst,
    output data
    );
    
    reg [3:0] addr;
    always@(posedge clk or posedge rst)
    begin
    if (rst) addr <= 4'b0;
    else
    begin
      if (addr == 4'b1111) addr <= 4'b1111;
      else addr <= addr + 1;
    end
    end
    
    blk_mem blk_mem (
      .clka(clk),    // input wire clka
      .addra(addr),  // input wire [3 : 0] addra
      .douta(data)  // output wire [0 : 0] douta
    );
endmodule
