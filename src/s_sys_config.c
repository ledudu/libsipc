#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgen.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wordexp.h>

#include <curl/curl.h>

#include "s_sys_config.h"


#define URL_SYS_CONFIG "http://nav.fetion.com.cn/nav/getsystemconfig.aspx"
#define DEBUG 1


char *expand_vars(const char *s)
{
	wordexp_t p;
	char **w;
	char *s_expaned = NULL;

	wordexp(s, &p, 0);
	w = p.we_wordv;

	if (1 != p.we_wordc)
		return NULL;

	s_expaned = strdup(w[0]);
	wordfree(&p);
	return s_expaned;
}

static char *download_sys_config_post_body = \
	"<?xml version=\"1.0\"?>"
	"<config>"
	"    <user mobile-no=\"13800138000\" />"
	"    <client type=\"PC\" version=\"4.9.0800\" platform=\"W6.1\" />"
	"    <servers version=\"0\" />"
	"    <service-no version=\"0\" />"
	"    <parameters version=\"0\" />"
	"    <hints version=\"0\" />"
	"    <http-applications version=\"0\" />"
	"    <services version=\"0\" />"
	"</config>";

static int s_download_config_updates_from_srv(SysConfig *sc)
{
	return 0;
}

static void s_load_config_from_local_init(SysConfig *sc)
{

}

static int s_download_config_whole_from_srv(SysConfig *sc)
{
	FILE *fp;
        CURL *handle;
        CURLcode res;
	struct curl_slist *slist = NULL;

        handle = curl_easy_init();
        if (!handle)
		goto failed;

        curl_easy_setopt(handle, CURLOPT_URL, URL_SYS_CONFIG);
	curl_easy_setopt(handle, CURLOPT_POST, 1);
        curl_easy_setopt(handle, CURLOPT_VERBOSE, DEBUG);

	slist = curl_slist_append(slist, "Accept: */*");
	slist = curl_slist_append(slist, "Content-Type: application/oct-stream");
	slist = curl_slist_append(slist, "Cache-Control: no-cache");
	slist = curl_slist_append(slist, "User-Agent: IIC2.0/PC 4.9.0800");
	curl_easy_setopt(handle, CURLOPT_HTTPHEADER, slist);

	curl_easy_setopt(handle, CURLOPT_POSTFIELDS, download_sys_config_post_body);
	curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, (long)strlen(download_sys_config_post_body));

        fp = fopen(sc->sys_config_local_path, "w") ;
        if (NULL == fp) {
            goto failed;
        }

	curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);

        res = curl_easy_perform(handle);
	fclose(fp);

	if (CURLE_OK != res) {
		fprintf(stderr,
			"curl_easy_perform() failed: %s \n",
			curl_easy_strerror(res));

		goto failed;
	}

        curl_easy_cleanup(handle);
	curl_slist_free_all(slist);

	return 0;

failed:
        curl_easy_cleanup(handle);
	curl_slist_free_all(slist);

	return -1;
}

static int s_save_config_into_local(SysConfig *sc)
{
	return 0;
}

SysConfig *s_sys_config_init(void)
{
	SysConfig *sc;
	char *buf;
	char *sipc_home;

	sc = malloc(sizeof(sc));
	if (!sc)
		goto failed;

	sc->sys_config_local_path = malloc(sizeof(char *) * (128 + 1));
	if (!sc->sys_config_local_path)
		goto failed;
	memset(sc->sys_config_local_path, '\0', 128);

	sipc_home = getenv("SIPC_CONFIG_HOME");
	if (!sipc_home) {
		buf = expand_vars("$HOME");
		sprintf(sc->sys_config_local_path, "%s/.config/sipc/sys_config.xml", buf);
		free(buf);
	} else {
		sprintf(sc->sys_config_local_path, "%s/.config/sipc/sys_config.xml", sipc_home);
	}

	if (-1 == access(dirname(sc->sys_config_local_path), F_OK | R_OK | W_OK | X_OK))
		if (0 != mkdir(dirname(sc->sys_config_local_path), 0755)) {
			fprintf(stderr, "mkdir %s failed \n", dirname(sipc_home));
			goto failed;
		}

	return sc;

failed:
	s_sys_config_free(sc);
	return NULL;
}


void s_update_sys_config(SysConfig *sc)
{
	int rc;

	rc = access(sc->sys_config_local_path, F_OK | R_OK);
	if (0 == rc) {
		rc = s_download_config_updates_from_srv(sc);
		if (0 != rc)
			s_load_config_from_local_init(sc);
		else
			s_save_config_into_local(sc);
	} else {
		rc = s_download_config_whole_from_srv(sc);
		if (0 != rc)
			s_load_config_from_local_init(sc);
		else
			s_save_config_into_local(sc);
	}
}

void s_sys_config_free(SysConfig *sc)
{
	if (sc) {
		if (sc->sys_config_local_path)
			free(sc->sys_config_local_path);

		free(sc);
	}
}
