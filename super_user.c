#include "stm32f4xx.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "super_user.h"

void super_user_init (super_user_t* user, uint16_t id, char* pass_code, char* name){
  user_init (&user->usr, id, pass_code, name);
  user->usr.is_super_user = 1;
}
