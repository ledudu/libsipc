#include <stdlib.h>

#include "s_sys_config.h"


SysConfig *s_sys_config_init()
{
	SysConfig *sc = malloc(sizeof(SysConfig));
	return sc;
}

void s_sys_config_free(SysConfig *sys_config)
{
	if (sys_config)
		free(sys_config);
}
