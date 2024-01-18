#include "stm32f4xx.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "alarm.h"

void alarm_display(alarm_t* alarm){
  printf ("Alarm %d at %s state is ", alarm->id, alarm->location);
  switch( alarm->state ) {
    case ALARM_OFF:  printf ("ALARM_OFF");  break;
    case ALARM_ON:   printf ("ALARM_ON");   break;
  }
  printf("\n");
}

void alarm_init (alarm_t* alarm, uint16_t id, char* location){
  memset(alarm, 0, sizeof(alarm_t));
  alarm->id = id;
  memcpy(alarm->location, location, 32);
  alarm->state = ALARM_OFF;
  alarm_display(alarm);
}

void alarm_set (alarm_t* alarm){
  if (alarm->state != ALARM_ON) {
    alarm->state = ALARM_ON;
    alarm_display(alarm);
  }
}
void alarm_reset (alarm_t* alarm){
  if (alarm->state != ALARM_OFF) {
    alarm->state = ALARM_OFF;
    alarm_display(alarm);
  }
}
