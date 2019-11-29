# ZYBO Pin Assignments
############################
# On-board Slide Switches  #
############################
set_property -dict { PACKAGE_PIN G15   IOSTANDARD LVCMOS33 } [get_ports { swt[0] }];
set_property -dict { PACKAGE_PIN P15   IOSTANDARD LVCMOS33 } [get_ports { swt[1] }];
set_property -dict { PACKAGE_PIN W13   IOSTANDARD LVCMOS33 } [get_ports { swt[2] }];
set_property -dict { PACKAGE_PIN T16   IOSTANDARD LVCMOS33 } [get_ports { swt[3] }];

############################
# On-board PMOD  JB        #
############################
set_property -dict { PACKAGE_PIN T20   IOSTANDARD LVCMOS33 } [get_ports { swt[4] }];
set_property -dict { PACKAGE_PIN U20   IOSTANDARD LVCMOS33 } [get_ports { swt[5] }];
set_property -dict { PACKAGE_PIN V20   IOSTANDARD LVCMOS33 } [get_ports { swt[6] }];
set_property -dict { PACKAGE_PIN W20   IOSTANDARD LVCMOS33 } [get_ports { swt[7] }];

############################
# On-board led             #
############################
set_property -dict { PACKAGE_PIN M14   IOSTANDARD LVCMOS33 } [get_ports { led[0] }];
set_property -dict { PACKAGE_PIN M15   IOSTANDARD LVCMOS33 } [get_ports { led[1] }];
set_property -dict { PACKAGE_PIN G14   IOSTANDARD LVCMOS33 } [get_ports { led[2] }];
set_property -dict { PACKAGE_PIN D18   IOSTANDARD LVCMOS33 } [get_ports { led[3] }];

############################
# On-board PMOD  JC        #
############################
set_property -dict { PACKAGE_PIN V15   IOSTANDARD LVCMOS33 } [get_ports { led[4] }];
set_property -dict { PACKAGE_PIN W15   IOSTANDARD LVCMOS33 } [get_ports { led[5] }];
set_property -dict { PACKAGE_PIN T11   IOSTANDARD LVCMOS33 } [get_ports { led[6] }];
set_property -dict { PACKAGE_PIN T10   IOSTANDARD LVCMOS33 } [get_ports { led[7] }];