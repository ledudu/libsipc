#include <stdlib.h>
#include <stdio.h>

#include "sipc.h"

#include "s_msg.h"
#include "s_sign_in.h"
#include "s_user.h"
#include "s_log.h"
#include "s_sys_config.h"


int send_sms(const char *account_id, 
	const char *passwd, 
	const char *to_account_id, 
	const char *msg)
{
	SysConfig *sys_config;
	User *user;
	int rc;

	user = s_user_init(account_id, passwd);

	sys_config = s_sys_config_init();
	if (NULL == sys_config) {
		goto failed;
	}

	s_update_sys_config(sys_config);

	rc = s_sign_in(user);
	if (SIPC_OK != rc) {
		s_log_debug("sign in failed");
		goto failed;
	}

	rc = s_send_msg(user, to_account_id);
	if (SIPC_OK != rc) {
		s_log_debug("send message failed");
		goto failed;
	}

	s_sys_config_free(sys_config);
	s_user_free(user);
	return 0;

failed:
	s_sys_config_free(sys_config);
	s_user_free(user);
	return 1;
}

int main(int argc, char *argv[])
{
	const char *account_id;
	const char *passwd;
	const char *to_account_id;
	const char *msg;

	if (5 != argc) {
		printf("Usage: %s <account_id> <password> <to_account_id> <message> \n", argv[0]);
		exit(1);
	}

	account_id = argv[1];
	passwd = argv[2];
	to_account_id = argv[3];
	msg = argv[4];

	return send_sms(account_id, passwd, to_account_id, msg);
}
