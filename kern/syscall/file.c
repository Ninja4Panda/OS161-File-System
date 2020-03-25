#include <types.h>
#include <kern/errno.h>
#include <kern/fcntl.h>
#include <kern/limits.h>
#include <kern/stat.h>
#include <kern/seek.h>
#include <lib.h>
#include <uio.h>
#include <thread.h>
#include <current.h>
#include <synch.h>
#include <vfs.h>
#include <vnode.h>
#include <file.h>
#include <syscall.h>
#include <copyinout.h>

// /* global open file table */
// OP openFileTbl[128];
// int n_openFile = 0;             //index for the open file table
// struct semaphore *array_mutex;  //global mutex only one process can modify 
//                                 //the table at a time

// /* Create a new file pointer */
// FP *newFP(char *filename, int flag) {
//     FP *fp = kmalloc(sizeof *fp);
//     KASSERT(fp != NULL);
//     fp->pos = 0;
//     fp->flag = flag;
//     return fp;
// }

int sys_open(const char *filename, int flags, mode_t mode) {
    // //create a new file pointer
    // FP *fp = newFP(filename, flags);
    // //call vfs_open with the &vnode
    kprintf("This is test for open\n");
    kprintf("flags: %d\n", flags);
    kprintf("filename: %s\n", filename);
    kprintf("mode: %u\n", mode);
    // //create a new open file struct 
    // OP new = {1, fp, };
    // //critical region need some way to control the access to the array 
    // //The following doesn't work right now
    // array_mutex = sem_create("array_mutex", 1);
    // P(array_mutex);
    // openFileTbl[n_openFile] = new;     //store the new struct in openfiletable
    // OP *pt = &openFileTbl[n_openFile]; //create a new open file pointer
    // n_openFile++; 
    // V(array_mutex);
    //point it to the struct
    //store it into current process array
    return 1;
    //return the file descriptor
}

int sys_close(int fd) {
    kprintf("This is test for close\n");
    kprintf("%d\n", fd);
    //decrease the ref count in openfile
        //if openfile ref_count == 0  
            //decrease vnode ref count
            //if the vnode ref count==1
                //call vfs_close 
    return fd;
}

//read into a buffer and advance the file pointer by buflen
ssize_t sys_read(int fd, void *buf, size_t buflen) {
    kprintf("This is test for read\n");
    kprintf("fd: %d\n", fd);
    kprintf("buflen: %d\n", buflen);
    kprintf("buf: %s\n", (char*)buf);
    return 1;
}

ssize_t sys_write(int fd, const void *buf, size_t nbytes) {
    kprintf("This is test for write\n");
    kprintf("fd: %d\n", fd);
    kprintf("bytes: %d\n", nbytes);
    kprintf("buf: %p\n", buf);
    return 1;
}

off_t sys_lseek(int fd, off_t pos, int whence) {
    kprintf("This is test for lseek\n");
    kprintf("lfd: %d\n", fd);
    kprintf("pos: %lld\n", pos);
    kprintf("whence: %d\n", whence);
    return 1;
}

int sys_dup2(int oldfd, int newfd) {
    kprintf("This is test for dup2\n");
    kprintf("oldfd: %d\n", oldfd);
    kprintf("newfd: %d\n", newfd);
    return 1;
}
