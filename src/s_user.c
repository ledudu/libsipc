#include <stdlib.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

/*
 * See also: 
 *  - https://www.ruby-forum.com/topic/2193556
 *  - http://stackoverflow.com/questions/7475914/libcrypto-deprecated-on-mac-os-x-10-7-lion
 */
#if defined(__APPLE__)
#  define COMMON_DIGEST_FOR_OPENSSL
#  include <CommonCrypto/CommonDigest.h>
#  define SHA1 CC_SHA1
#else
#  include <openssl/sha.h>
#endif

#include "s_user.h"


void sha1_in_hex(char *digest, const char *s, size_t len)
{
	SHA_CTX ctx;
	unsigned char *hashed;
	int i;

	hashed = malloc( sizeof( char ) * SHA_DIGEST_LENGTH + 1 );

	SHA1_Init(&ctx);
	SHA1_Update(&ctx, s, len);
	SHA1_Final(hashed, &ctx);

	for (i = 0; i < SHA_DIGEST_LENGTH; i++) {
		snprintf(digest + i * 2, SHA_DIGEST_LENGTH * 2, "%.2x", hashed[i]);	
	}
}

static char *passwd_v4digest(const char *passwd)
{	
	size_t len_prefix;
	char *buf;

	char *digest;

	digest = malloc(sizeof(char) * (SHA_DIGEST_LENGTH * 2) + 1);
	memset(digest, '\0', SHA_DIGEST_LENGTH);
	digest[SHA_DIGEST_LENGTH] = '\0';

	len_prefix = strlen("fetion.com.cn:") + strlen(passwd);
	buf = malloc(sizeof(char) * (len_prefix + 1));
	memset(buf, '\0', len_prefix);
	buf[len_prefix] = '\0';

	memcpy(buf, "fetion.com.cn:", strlen("fetion.com.cn:"));
	memcpy(buf + strlen("fetion.com.cn:"), passwd, strlen(passwd));

	sha1_in_hex(digest, buf, strlen(buf));		
	return digest;
}


User *s_user_init(const char *account_id, const char *passwd) 
{
	User *u;	

	u = malloc(sizeof(User));	
	if (NULL == u)
		goto failed;

	u->account_id = strdup(account_id);
	u->passwd_hashed = passwd_v4digest(passwd);

	if (NULL == u->passwd_hashed)
		goto failed;
		
	return u;

failed:
	s_user_free(u);
	return NULL;
}

void s_user_free(User *u) 
{	
	if (NULL != u) {
		if (NULL != u->account_id)
			free(u->account_id);
		
		if (NULL != u->passwd_hashed)
			free(u->passwd_hashed);

		free(u);
	}
}
