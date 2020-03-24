/*
 * Declarations for file handle and file table management.
 */

#ifndef _FILE_H_
#define _FILE_H_

/*
 * Contains some file-related maximum length constants
 */
#include <limits.h>

struct 

/*
 * Put your function declarations and data types here ...
 */

int open(const char *filename, int flags, ...);
int close(int fd);
ssize_t read(int fd, void *buf, size_t buflen);
ssize_t write(int fd, const void *buf, size_t nbytes);
off_t lseek(int fd, off_t pos, int whence); //whence is where you start
int dup2(int oldfd, int newfd);

// dynamic allocation of open file table entries
int table[] = {0};
#endif /* _FILE_H_ */
