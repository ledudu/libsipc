#include <stdlib.h>
#include <stdio.h>

#include "sipc.h"

#include "s_message.h"
#include "s_sign_in.h"
#include "s_user.h"


int main(int argc, char *argv[])
{
	char *account_id;
	char *password;
	char *to_account_id;
	char *message;

	User *user;

	if (4 != argc) {
		printf("Usage: %s <account_id> <password> <to_account_id> <message> \n", argv[0]);
		exit(1);
	}

	user = s_init_user(account_id, password);
	rc = s_sign_in(user);

	if (SIPC_OK != rc) {
		s_log_debug("sign in failed");
		goto failed;
	}

	rc = s_send_msg(user, to_account_id);
	if (SPIC_OK != rc) {
		s_log_debug("send message failed");
		goto failed;
	}

failed:
	s_free_user(user);

	return 0;
}
