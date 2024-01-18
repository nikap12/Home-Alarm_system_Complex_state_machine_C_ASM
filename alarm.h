#include "stdio.h"
#include "stm32f4xx.h"

#ifndef __ALARM_h__
#define __ALARM_h__

typedef enum {ALARM_OFF, ALARM_ON} alarm_state_e; 

typedef struct alarm_s {
  uint16_t  id;
  alarm_state_e state;
  char location[28];
} alarm_t;

void alarm_init (alarm_t* alarm, uint16_t id, char* location);
void alarm_set (alarm_t* alarm);
void alarm_reset (alarm_t* alarm);

#endif // __ALARM_h__
