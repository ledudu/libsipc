#ifndef _S_SYS_CONFIG_H_
#define _S_SYS_CONFIG_H_ 

struct _SysConfig {

};
typedef struct _SysConfig SysConfig;

SysConfig *s_sys_config_init();
void s_sys_config_free(SysConfig *sys_config);


#endif
