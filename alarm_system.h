#include "stm32f4xx.h"
#include "sensor.h"
#include "alarm.h"
#include "user.h"
#include "super_user.h"

#ifndef __ALARM_SYS_H__
#define __ALARM_SYS_H__

typedef enum {UNARMED, WAITING_TO_ARM, ARMED, ALARMED} system_state_e; 

typedef struct alarm_system_s {
  sensor_t sensor_list[64];
  alarm_t alarm_list[64];
  user_t user_list[64];
  super_user_t super_list[8];
  uint32_t fsm_coverage[4][4];
  system_state_e state;
  system_state_e target_state;
  system_state_e prev_state;
} alarm_system_t;

void alarm_system_init (alarm_system_t *system);
user_t *system_get_user(alarm_system_t *system, char* passcode);
void system_user_req_arm(alarm_system_t *system, user_t *user);
void system_update_state(alarm_system_t *system);
void system_user_login_event(alarm_system_t *system, user_t *user);
void system_fsm_coverage_update (alarm_system_t *system);
void system_fsm_coverage_display (alarm_system_t *system);
void system_alarm_set (alarm_system_t *system);
void system_alarm_reset (alarm_system_t *system);

#endif // __ALARM_SYS_H__
