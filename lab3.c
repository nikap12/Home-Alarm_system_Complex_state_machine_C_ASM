#include "stm32f4xx.h"
#include "stdio.h"
#include "sensor.h"
#include "alarm.h"
#include "user.h"
#include "super_user.h"
#include "alarm_system.h"
#include <string.h>

uint64_t sensor_states;
uint64_t prev_sensor_states;
char textbuffer[34] = ""; // Text buffer

uint32_t volatile msTicks;                       // Counter for millisecond Interval
alarm_system_t system;
user_t *logged_in_user;

void SysTick_Handler (void) {                    // SysTick Interrupt Handler
  uint64_t  tmp_sensor_states = sensor_states;
  int       i;

  msTicks++;                                     // Increment Counter
  for (i=0; i<64; i++) {
    if (tmp_sensor_states & 1) sensorm_set (&system.sensor_list[i]);
    else                       sensorm_reset (&system.sensor_list[i]);
    tmp_sensor_states >>= 1;  // shift right 1 bit
  }
  tmp_sensor_states = (prev_sensor_states ^ sensor_states) & sensor_states;
  if (tmp_sensor_states) __NVIC_SetPendingIRQ(EXTI0_IRQn);
  prev_sensor_states = sensor_states;
  system_update_state(&system);
  if ((msTicks & 0x7FF) == 0x7FF) __NVIC_SetPendingIRQ(EXTI2_IRQn);
}

void sys_clock_timer_init(int period) {                
  if (SysTick_Config (SystemCoreClock / period)) { // SysTick period in seconds
    printf("\nError SysTick_Config!\n");  // Handle Error 
  }
}
 
void Device_Initialization (void)  {             // Configure & Initialize MCU
  alarm_system_init(&system);
  sys_clock_timer_init (1000);            // setup device-specific timer
	NVIC_EnableIRQ	(	EXTI0_IRQn	);
	NVIC_EnableIRQ	(	EXTI1_IRQn	);
	NVIC_EnableIRQ	(	EXTI2_IRQn	);
}

void EXTI0_IRQHandler (void) {
	printf("EXTI0_IRQHandler clk cnt 0x%x \n", msTicks);
}

void EXTI1_IRQHandler (void) {
	printf("EXTI1_IRQHandler clk cnt 0x%x \n", msTicks);
  system_user_login_event(&system, logged_in_user);
}

void EXTI2_IRQHandler (void) {
  if (system.state == ALARMED) printf ("^beep^"); // alarm indicator
  // printf ("^beep^"); // for debugging
}



int main(void)
{
  SCB->CCR |= SCB_CCR_STKALIGN_Msk; // Enable double word stack alignment 
  //(recommended in Cortex-M3 r1p1, default in Cortex-M3 r2px and Cortex-M4)
  printf("\nHello world!\n");
  printf ("textbuffer address = 0x%x \n", (unsigned int) textbuffer);
  printf ("sensor_states address = 0x%x \n", (unsigned int) &sensor_states);
  printf ("sizeof sensor = 0x%x \n", sizeof(sensor_t));
  printf ("sizeof alarm = 0x%x \n", sizeof(alarm_t));
  printf ("sizeof user = 0x%x \n", sizeof(user_t));
  printf ("sizeof suoer_user = 0x%x \n", sizeof(super_user_t));
  printf ("sizeof system = 0x%x \n", sizeof(alarm_system_t));
	
  Device_Initialization ();
  
  
  while (textbuffer[0] != 'q') {
    printf("Enter passcode to ARM:");
    fgets(textbuffer, (sizeof(textbuffer)-1), stdin);		
    if ((logged_in_user = system_get_user(&system, textbuffer)) == NULL) printf ("invalid user entry\n"); 
    else __NVIC_SetPendingIRQ(EXTI1_IRQn);
  }
	NVIC_DisableIRQ	(	EXTI0_IRQn	);
	NVIC_DisableIRQ	(	EXTI1_IRQn	);
	NVIC_DisableIRQ	(	EXTI2_IRQn	);
  system_fsm_coverage_display (&system);
}
