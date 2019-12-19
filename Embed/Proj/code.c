/*
 * Ask me anything: vencifreeman16@sjtu.edu.cn.
 * Author: Venci Freeman, copyright 2019.
 * School: Shanghai Jiao Tong University.
 *
 * Description:
 * Embedded System Develop homework.
 *
 * Details:
 * - 4 switches (SW0-3) and 2 buttons (BTN2,3) use the same GPIO port;
 * - Count cycle is ONE_TENTH*(4bit SW + 2bit BTN);
 * - Capture the interrupts from PL BTN0 and BTN1 so when button 0 (1) is 
 *   pressed, there will output “Interrupt valid, Button 0 (1) is pressed” 
 *   through the UART serial port;
 * - Interrupt shielding design. After an interrupt triggers, the second
 *   interrupt won't be responded within 1 second.

 * History:
 * - 19/12/16: Create this file;
 * - 19/12/17: Modify it from xgpio interrupt.
 *
 * Notes:
 * - Remember that the buttons and LEDs are on 2 separate channels of the GPIO
 *   so that interrupts are not caused when the LEDs are turned on and off.
 */

/***************************** Include Files *********************************/
#include "xparameters.h"  // It contains the address map for peripherals in the system.
#include "xgpio.h"
#include "led_ip.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "xil_exception.h"

/************************** Constant Definitions *****************************/
XScuTimer Timer;		/* Cortex A9 SCU Private Timer Instance */

#define ONE_TENTH 32500000 // half of the CPU clock speed/10
#define BTN_SW_CHANNEL	 1  // Channel 1 of the GPIO Device
#define LED_CHANNEL	 2  // Channel 2 of the GPIO Device
#define DirectionMask 0xffffffff
#define LED_DELAY	10

// #define INTR_DELAY 0x00FFFFFF  // 1 second
// #define BUTTON_INTERRUPT XGPIO_IR_CH1_MASK  // Channel 1 Interrupt Mask
// #define INTERRUPT_CONTROL_VALUE 0x7  // To control the interrupt processing

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

/************************** main Function *****************************/
int main (void) {

  XGpio dip, push;

  int flag, temp;
  int count, Status;
  int btn_check, psb_check, dip_check, dip_check_prev;

  // PS Timer related definitions
  XScuTimer_Config *ConfigPtr;
  XScuTimer *TimerInstancePtr = &Timer;

  xil_printf("-- Start of the Program --\r\n");

  XGpio_Initialize(&push, XPAR_SWITCHES_DEVICE_ID);
  // XGpio_Initialize (XGpio *InstancePtr, u16 DeviceId)

  XGpio_SetDataDirection(&push, BTN_SW_CHANNEL, DirectionMask);
  XGpio_SetDataDirection(&push, LED_CHANNEL, DirectionMask);
  // XGpio_SetDataDirection(XGpio * InstancePtr, unsigned Channel, u32 DirectionMask)

  flag = 0;
  count = 0;
   
  ConfigPtr = XScuTimer_LookupConfig(XPAR_PS7_SCUTIMER_0_DEVICE_ID);
  // XScuTimer_Config * XScuTimer_LookupConfig(u16 DeviceId)	

  Status = XScuTimer_CfgInitialize(TimerInstancePtr, ConfigPtr, ConfigPtr->BaseAddr);  // Initialize the timer
  // s32 XScuTimer_CfgInitialize(XScuTimer * InstancePtr, XScuTimer_Config * ConfigPtr, u32 EffectiveAddress)	

  if(Status != XST_SUCCESS) {
	  xil_printf("Timer init() failed\r\n");
	  return XST_FAILURE;
  }

  dip_check_prev = XGpio_DiscreteRead(&push, BTN_SW_CHANNEL);  // Read dip switch values
  // XGpio_DiscreteRead(XGpio *InstancePtr, unsigned channel)

  XScuTimer_LoadTimer(TimerInstancePtr, ONE_TENTH * dip_check_prev);  // Load timer with delay in multiple of ONE_TENTH
  // XScuTimer_LoadTimer(XScuTimer *InstancePtr, u32 Value)

  XScuTimer_EnableAutoReload(TimerInstancePtr);  // Set AutoLoad mode
  // XScuTimer_EnableAutoReload(XScuTimer *InstancePtr)

  XScuTimer_Start(TimerInstancePtr);  // Start the timer
  // XScuTimer_Start(XScuTimer * InstancePtr)

  while (1) {
	  psb_check = XGpio_DiscreteRead(&push, LED_CHANNEL);  // Read push buttons and break the loop if Center button pressed
    // XGpio_DiscreteRead(XGpio *InstancePtr, unsigned channel)

	  if ( (psb_check > 0) && (psb_check < 3) && (flag == 0) ) {
	    xil_printf("Interrupt valid, Button 0(1) is pressed\r\n");
	    flag = 1;
	  }
    temp = psb_check & 3;

    if(flag == 0) {
	    dip_check = XGpio_DiscreteRead(&push, BTN_SW_CHANNEL);

	    if (dip_check != dip_check_prev) {
		    xil_printf("DIP Switch Status %x, %x\r\n", dip_check_prev, dip_check);
		    dip_check_prev = dip_check;
		    XScuTimer_LoadTimer(TimerInstancePtr, ONE_TENTH * (dip_check + temp));  // load timer with the new switch settings
        // XScuTimer_LoadTimer(XScuTimer *InstancePtr, u32 Value)
		    count = 0;
	    }
    }

    if(XScuTimer_IsExpired(TimerInstancePtr)) {
        // XScuTimer_IsExpired(XScuTimer *InstancePtr)

        XScuTimer_ClearInterruptStatus(TimerInstancePtr);  // clear status bit
        // XScuTimer_ClearInterruptStatus(XScuTimer *InstancePtr)
        
        LED_IP_mWriteReg(XPAR_LED_IP_S_AXI_BASEADDR, 0, count);  // output the count to LED and increment the count
        // LED_IP_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
        count++;

        if(count == LED_DELAY)
          flag = 0;
    }
  }
  return 0;
}
