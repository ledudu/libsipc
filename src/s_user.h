#ifndef _S_USER_H_
#define _S_USER_H_ 

#include "s_sys_config.h"

struct _User {
	char *account_id;	
	char *passwd_hashed;
	char *sid;
	char *uri;
	char *mobile_no;

	SysConfig *sys_config;
};
typedef struct _User User;

User *s_user_init(char *account_id, char *passwd);
void s_user_free(User *user);


#endif
