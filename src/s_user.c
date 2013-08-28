#include <stdlib.h>

#include "s_user.h"

User *s_user_init(const char *account_id, const char *passwd) 
{
	User *u = malloc(sizeof(User));
	return u;
}

void s_user_free(User *user) 
{
	if (user)
		free(user);
}
