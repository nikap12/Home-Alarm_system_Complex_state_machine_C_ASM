#include "stm32f4xx.h"
#include "user.h"

#ifndef __SUPER_USER_H__
#define __SUPER_USER_H__

typedef struct super_user_s {
  user_t usr;
} super_user_t;

void super_user_init (super_user_t* user, uint16_t id, char* pass_code, char* name);

#endif // __SUPER_USER_H__
