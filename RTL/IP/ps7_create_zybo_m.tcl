set dir D:/course/lab1-2
set proj_name "lab4"

set p1 $proj_name.srcs/sources_1/bd/system/system.bd
set p2 $proj_name.ip_user_files/sim_scripts
# set p3 $proj_name.srcs/sources_1/bd/system/hdl/system_wrapper.v


create_bd_design "system"
update_compile_order -fileset sources_1
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.5 processing_system7_0
endgroup
apply_bd_automation -rule xilinx.com:bd_rule:processing_system7 -config {make_external "FIXED_IO, DDR" apply_board_preset "1" Master "Disable" Slave "Disable" }  [get_bd_cells processing_system7_0]
startgroup
set_property -dict [list CONFIG.PCW_USE_M_AXI_GP0 {0} CONFIG.PCW_EN_CLK0_PORT {0} CONFIG.PCW_EN_RST0_PORT {0} CONFIG.PCW_QSPI_PERIPHERAL_ENABLE {0} CONFIG.PCW_QSPI_GRP_SINGLE_SS_ENABLE {1} CONFIG.PCW_ENET0_PERIPHERAL_ENABLE {0} CONFIG.PCW_SD0_PERIPHERAL_ENABLE {0} CONFIG.PCW_UART1_PERIPHERAL_ENABLE {0} CONFIG.PCW_TTC0_PERIPHERAL_ENABLE {0} CONFIG.PCW_USB0_PERIPHERAL_ENABLE {0} CONFIG.PCW_USB_RESET_ENABLE {0} CONFIG.PCW_I2C_RESET_ENABLE {0} CONFIG.PCW_GPIO_EMIO_GPIO_ENABLE {1} CONFIG.PCW_GPIO_EMIO_GPIO_IO {2}] [get_bd_cells processing_system7_0]
endgroup
startgroup
create_bd_intf_port -mode Master -vlnv xilinx.com:interface:gpio_rtl:1.0 GPIO_0
connect_bd_intf_net [get_bd_intf_pins processing_system7_0/GPIO_0] [get_bd_intf_ports GPIO_0]
endgroup
regenerate_bd_layout
validate_bd_design
generate_target all [get_files  $dir/$proj_name/$p1]
export_ip_user_files -of_objects [get_files  $dir/$proj_name/$p1] -no_script -force -quiet
export_simulation -of_objects [get_files  $dir/$proj_name/$p1] -directory  $dir/$proj_name/$p2 -force -quiet
























