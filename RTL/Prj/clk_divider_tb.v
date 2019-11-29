module testbench();
    reg clk_125;
    reg rst;
    wire clk;

    clk_divider TEST (
      .clk_125(clk_125),
      .rst(rst),
      .clk(clk)
    );
    
initial
  begin
    clk_125 = 0;
    rst = 1;
  end
    
always
  begin
    #4 clk_125 = ~clk_125;
    rst = 0;
  end
    
endmodule
