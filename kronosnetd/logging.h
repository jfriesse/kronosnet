#ifndef __LOGGING_H__
#define __LOGGING_H__

#include <qb/qblog.h>

#define log_debug(fmt, args...) qb_log(LOG_DEBUG, "(%s:%i|%s): " fmt, __FILE__, __LINE__, __FUNCTION__, ##args);

#define log_info(fmt, args...) qb_log(LOG_INFO, fmt, ##args);

#define log_warn(fmt, args...) qb_log(LOG_WARNING, fmt, ##args);

#define log_error(fmt, args...) qb_log(LOG_ERR, fmt, ##args);

void logging_init_defaults(int debug, int daemonize, const char *logfile);

void logging_fini(void);

#endif