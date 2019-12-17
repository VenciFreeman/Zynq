#include "xparameters.h"  // It contains the address map for peripherals in the system. Find #define XPAR_SWITCHES_DEVICE_ID.
#include "xgpio.h"
#include "led_ip.h"
#include "xscutimer.h"

XScuTimer Timer;  // Cortex A9 SCU Private Timer Instance

#define ONE_TENTH 32500000 // half of the CPU clock speed/10

int main (void) {

   XGpio dip, push;
   int psb_check, dip_check, dip_check_prev, count, Status;

   // PS Timer related definitions
   XScuTimer_Config *ConfigPtr;
   XScuTimer *TimerInstancePtr = &Timer;

   xil_printf("-- Start of the Program --\r\n");

   /*
    * ======= Function prototype variable interpretation =======
    * 
    * XGpio *InstancePtr
    * is a pointer to an XGpio instance.
    * The memory the pointer references must be pre-allocated by the caller.
    * Further calls to manipulate the component through the XGpio API must be made with this pointer.
    *
    * u16 DeviceId
    * is the unique id of the device controlled by this XGpio component.
    * Passing in a device id associates the generic XGpio instance to a specific device,
    * as chosen by the caller or application developer.
    * 
    * unsigned Channel
    * contains the channel of the GPIO (1 or 2) to operate on.
    * 
    * u32 DirectionMask
    * is a bitmask specifying which bits are inputs and which are outputs.
    * Bits set to 0 are output and bits set to 1 are input.
    * 
    * XScuTimer_Config * ConfigPtr
    * points to the XScuTimer configuration structure.
    * 
    * u32 EffectiveAddress
    * is the base address for the device.
    * It could be a virtual address if address translation is supported in the system,
    * otherwise it is the physical address.
    * 
    * u32 Value
    * is the count to be loaded in to the load register.
    * 
    * ======= variable interpretation end =======
    * 
    */
 
   XGpio_Initialize(&dip, XPAR_SWITCHES_DEVICE_ID);
   // XGpio_Initialize (XGpio *InstancePtr, u16 DeviceId)
   XGpio_SetDataDirection(&dip, 1, 0xffffffff);
   // XGpio_SetDataDirection (XGpio * InstancePtr, unsigned Channel, u32 DirectionMask)
	
   XGpio_Initialize(&push, XPAR_BUTTONS_DEVICE_ID);
   // XGpio_Initialize (XGpio *InstancePtr, u16 DeviceId)
   XGpio_SetDataDirection(&push, 1, 0xffffffff);
   // XGpio_SetDataDirection (XGpio * InstancePtr, unsigned Channel, u32 DirectionMask)

   count = 0;

   // Initialize the timer
   ConfigPtr = XScuTimer_LookupConfig (XPAR_PS7_SCUTIMER_0_DEVICE_ID);
   // XScuTimer_Config * XScuTimer_LookupConfig	(u16 DeviceId)	


   Status = XScuTimer_CfgInitialize	(TimerInstancePtr, ConfigPtr, ConfigPtr->BaseAddr);
   // s32 XScuTimer_CfgInitialize	(XScuTimer * InstancePtr, XScuTimer_Config * ConfigPtr, u32 EffectiveAddress)	

   if (Status != XST_SUCCESS) {
	  xil_printf("Timer init() failed\r\n");
	  return XST_FAILURE;
   }

   dip_check_prev = XGpio_DiscreteRead(&dip, 1);  // Read dip switch values
   // XGpio_DiscreteRead(XGpio *InstancePtr, unsigned channel)
   
   XScuTimer_LoadTimer(TimerInstancePtr, ONE_TENTH*dip_check_prev);  // Load timer with delay in multiple of ONE_TENTH
   // XScuTimer_LoadTimer(XScuTimer *InstancePtr, u32 Value)

   XScuTimer_EnableAutoReload(TimerInstancePtr);  // Set AutoLoad mode
   // XScuTimer_EnableAutoReload(XScuTimer *InstancePtr)
   
   XScuTimer_Start(TimerInstancePtr);  // Start the timer
   // XScuTimer_Start(XScuTimer * InstancePtr)	

   while (1) {
	  psb_check = XGpio_DiscreteRead(&push, 1);  // Read push buttons and break the loop if Center button pressed
     // XGpio_DiscreteRead(XGpio *InstancePtr, unsigned channel)

	  if (psb_check > 0) {
		  xil_printf("Push button pressed: Exiting\r\n");
		  XScuTimer_Stop(TimerInstancePtr);
        // XScuTimer_Stop(XScuTimer * InstancePtr)	
		  break;
	  }

	  dip_check = XGpio_DiscreteRead(&dip, 1);
     // XGpio_DiscreteRead(XGpio *InstancePtr, unsigned channel)

	  if (dip_check != dip_check_prev) {
		  xil_printf("DIP Switch Status %x, %x\r\n", dip_check_prev, dip_check);
		  dip_check_prev = dip_check;
		  XScuTimer_LoadTimer(TimerInstancePtr, ONE_TENTH*dip_check);  // load timer with the new switch settings
        // XScuTimer_LoadTimer(XScuTimer *InstancePtr, u32 Value)
		  count = 0;
	  }

	  if (XScuTimer_IsExpired(TimerInstancePtr)) {
         // XScuTimer_IsExpired(XScuTimer *InstancePtr)
		  	XScuTimer_ClearInterruptStatus(TimerInstancePtr);  // clear status bit
         // XScuTimer_ClearInterruptStatus(XScuTimer *InstancePtr)
		  	LED_IP_mWriteReg(XPAR_LED_IP_S_AXI_BASEADDR, 0, count);  // output the count to LED and increment the count
         // LED_IP_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
		  	count++;
	   }
   }
   return 0;
}
