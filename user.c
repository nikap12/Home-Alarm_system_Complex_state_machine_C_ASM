#include "stm32f4xx.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "user.h"

void user_init (user_t* user, uint16_t id, char* pass_code, char* name){
  memset(user, 0, sizeof(user_t));
  user->id = id;
  user->state = LOGGED_OUT;
  memcpy(user->pass_code, pass_code, strlen(pass_code));
  memcpy(user->name, name, strlen(name));
  printf("user %s passcode %s\n", name, pass_code);
}
