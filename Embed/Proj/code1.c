#include "xparameters.h"  // It contains the address map for peripherals in the system. Find #define XPAR_SWITCHES_DEVICE_ID.
#include "xgpio.h"
#include "led_ip.h"

int main (void) {

   XGpio dip, push;
   int i, psb_check, dip_check;
	
   xil_printf("-- Start of the Program --\r\n");
 
   XGpio_Initialize(&dip, XPAR_SWITCHES_DEVICE_ID);
   // XGpio_Initialize (XGpio *InstancePtr, u16 DeviceId)
   XGpio_SetDataDirection(&dip, 1, 0xffffffff);
   // XGpio_SetDataDirection (XGpio * InstancePtr, unsigned Channel, u32 DirectionMask)
	
   XGpio_Initialize(&push, XPAR_BUTTONS_DEVICE_ID);
   // XGpio_Initialize (XGpio *InstancePtr, u16 DeviceId)
   XGpio_SetDataDirection(&push, 1, 0xffffffff);
   // XGpio_SetDataDirection (XGpio * InstancePtr, unsigned Channel, u32 DirectionMask)
	

   while (1) {
      psb_check = XGpio_DiscreteRead(&push, 1);  // Read dip switch values
      // XGpio_DiscreteRead(XGpio *InstancePtr, unsigned channel)
	   xil_printf("Push Buttons Status %x\r\n", psb_check);

	   dip_check = XGpio_DiscreteRead(&dip, 1);
      // XGpio_DiscreteRead(XGpio *InstancePtr, unsigned channel)
	   xil_printf("DIP Switch Status %x\r\n", dip_check);

	   LED_IP_mWriteReg(XPAR_LED_IP_S_AXI_BASEADDR, 0, dip_check);  // output dip switches value on LED_ip device
      // LED_IP_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
	  
	  for (i=0; i<9999999; i++);
   }
}
