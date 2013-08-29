#ifndef _S_SYS_CONFIG_H
#define _S_SYS_CONFIG_H 

struct _SysConfig {
	char *sys_config_local_path;
};
typedef struct _SysConfig SysConfig;

SysConfig *s_sys_config_init(void);
void s_sys_config_free(SysConfig *sys_config);

void s_update_sys_config(SysConfig *sc);

#endif
