
/*
 * Copyright (C) Ding Peilong
 */


#ifndef _NGX_POSIX_CONFIG_H_INCLUDED_
#define _NGX_POSIX_CONFIG_H_INCLUDED_


#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>             /* offsetof() */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>

#include <sys/uio.h>
#include <sys/filio.h>          /* FIONBIO */
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sched.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <ngx_auto_config.h>


#endif /* _NGX_POSIX_CONFIG_H_INCLUDED_ */
