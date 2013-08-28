#ifndef _S_SYS_CONFIG_H_
#define _S_SYS_CONFIG_H_ 

struct _SysConfig {
	char *sys_config_local_path;
};
typedef struct _SysConfig SysConfig;

SysConfig *s_sys_config_init(void);
void s_update_sys_config(SysConfig *sc);
void s_sys_config_free(SysConfig *sys_config);


#endif
