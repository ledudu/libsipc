#ifndef _S_LOG_H_
#define _S_LOG_H_ 

void s_log_debug(const char *fmt, ...);
void s_log_info(const char *fmt, ...);
void s_log_warning(const char *fmt, ...);
void s_log_error(const char *fmt, ...);
void s_log_critical(const char *fmt, ...);

#endif
