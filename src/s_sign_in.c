#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "s_sign_in.h"

#define DEBUG 1

#define MOBILE_NO_LENGTH 11


static int is_mobile_no(const char *s)
{
	if (MOBILE_NO_LENGTH != strlen(s))
		return 0;

	for (int i = 0; i < MOBILE_NO_LENGTH; i++)
		if (0 == isnumber(s[i]))
			return 0;

	return 1;
}

static int is_email(const char *s)
{
}

static int is_sid(const char *s)
{
	for (int i = 0; i < strlen(s); i++)
		if (0 == isnumber(s[i]))
			return 0;
	return 1;
}


int s_sign_in(User *user, const char *uri)
{
	char *uri_full;
	FILE *fp;

	CURL *handle;
        CURLcode res;
	struct curl_slist *slist = NULL;

        handle = curl_easy_init();
        if (!handle)
		goto failed;

	uri_full = malloc(sizeof(char) * (128 + 1));
	if (NULL == uri_full)
		goto failed;
	memset(uri_full, '\0', 128);
	uri_full[128] = '\0';

        fp = fopen("resp_ssi.xml", "w") ;
        if (NULL == fp)
            goto failed;

	char *account_kv = malloc(sizeof(char) * (64 + 1));
	memset(account_kv, '\0', 64);
	account_kv[64] = '\0';

	if (is_mobile_no(user->account_id)) {
		sprintf(buf, "mobileno=%s", user->account_id);
	} else if (is_email(user->account_id)) {
		sprintf(buf, "email=%s", user->account_id);
	} else if (is_sid(user_>account_id)) {
		sprintf(buf, "sid=%s", user->account_id);
	}

	sprintf(uri_full,
		"%s?"
		"domains=fetion.com.cn&"
		"v4digest-type=1&"
		"%s&"
		"v4digest=%s",
		uri,
		account_kv,
		user->passwd_hashed);

	free(account_kv);

        curl_easy_setopt(handle, CURLOPT_URL, uri_full);
        curl_easy_setopt(handle, CURLOPT_VERBOSE, DEBUG);

	slist = curl_slist_append(slist, "Accept-Encoding: identity");
	slist = curl_slist_append(slist, "User-Agent: IIC2.0/PC 4.9.0800");
	curl_easy_setopt(handle, CURLOPT_HTTPHEADER, slist);

	curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);

        res = curl_easy_perform(handle);
	if (CURLE_OK != res) {
		fprintf(stderr,
			"curl_easy_perform() failed: %s \n",
			curl_easy_strerror(res));

		goto failed;
	}

	curl_slist_free_all(slist);
	fclose(fp);
	free(uri_full);

        curl_easy_cleanup(handle);
	return 0;

failed:
	curl_slist_free_all(slist);
	fclose(fp);
	free(uri_full);

        curl_easy_cleanup(handle);
	return -1;
}
