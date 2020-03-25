/*
 * Declarations for file handle and file table management.
 */

#ifndef _FILE_H_
#define _FILE_H_


/*
 * Contains some file-related maximum length constants
 */
#include <limits.h>

/* Open File structure */
typedef struct openfile {
    int          ref_count; //count how many open file pointers refer to this struct
    FP           *fp;       //Pointer to a file pointer
    struct vnode *vnode;    //Pointer to a vnode
} OP;

/* File pointer structure */
typedef struct filePointer{
    off_t         pos;    //position of the file pointer
    int flag;
} FP;


/**
 * User-level File functions.
 * 
 * open     - Open or create a file 
 * close    - Close a file
 * 
 * read     - Read data from a file
 * write    - Write data to a file
 * 
 * lseek    - seek to a position in a file
 * dup2     - clone file handles
 */

int open(const char *filename, int flags, ...); //The last argument is permission 
int close(int fd);

ssize_t read(int fd, void *buf, size_t buflen);
ssize_t write(int fd, const void *buf, size_t nbytes);

off_t lseek(int fd, off_t pos, int whence); //whence is where you start
int dup2(int oldfd, int newfd);


#endif /* _FILE_H_ */
