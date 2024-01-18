#include "stdio.h"
#include "stm32f4xx.h"

#ifndef __SENSOR_H__
#define __SENSOR_H__

typedef enum {INACTIVE, IDLE, TRIGGERED, MALFUNCTION} sensor_state_e; 

typedef struct sensor_s {
  uint16_t  id;
  sensor_state_e state;
  char location[28];
} sensor_t;

void sensor_init (sensor_t* sensor, uint16_t id, char* location);
void sensorm_set (sensor_t* sensor);
void sensorm_reset (sensor_t* sensor);
void sensorm_set_malfunction (sensor_t* sensor);

#endif // __SENSOR_H__
