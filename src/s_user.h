#ifndef _S_USER_H_
#define _S_USER_H_ 

struct _User {
	char *account_id;	
	char *passwd_hashed;
	char *sid;
	char *uri;
	char *mobile_no;
};
typedef struct _User User;

User *s_user_init(const char *account_id, const char *passwd);
void s_user_free(User *user);


#endif
