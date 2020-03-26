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

/**
 * Create a pointer to a new file pointer
 * 
 * Initialising the pos to 0 because it is
 * always read from the start of file
 * 
 * This funciton has to be called in a protected way
 * as in caller has to guarantee that flag is valid
*/
FP *newFP(int flags) {
    FP *fp = kmalloc(sizeof *fp);
    KASSERT(fp != NULL);
    fp->pos = 0;

    //setting the flags
    flags = flags & O_ACCMODE;
    fp->read = 1;
    fp->write = 1;
    if (flags == O_RDONLY) {
        fp->write = 0;
    } else if(flags == O_WRONLY) {
        fp->read = 0;
    }

    return fp;
}

/**
 * Create a new open file pointer
 * 
 * ref_count is initialised to 1
 * as there is only 1 pointer refer to
 * it at first, as more pointer refers
 * to it (from dup2() or fork()) it will go up
 * 
 * Note there might be concurrency issue with ref_count
*/
OP *newOP(FP *fp, struct vnode *vnode) {
    OP *op = kmalloc(sizeof *op);
    KASSERT(op != NULL);
    op->ref_count = 1;
    op->fp = fp;
    op->vnode = vnode;
    return op;
}

/**
 * Open 
*/
int sys_open(char *filename, int flags, mode_t mode) {
    kprintf("This is test for open\n");
    kprintf("flags: %d\n", flags);
    kprintf("filename: %s\n", filename);
    kprintf("mode: %u\n", mode);
    //create a vnode struct
    struct vnode *vnode = NULL;
    //call vfs_open with the vnode
    int err = vfs_open(filename, flags, mode, &vnode);
    //open file successed
    if (err == 0) {

    }
    //create a new file pointer
    //FP *fp = newFP(flags);
    /**
     * Get the current working directory basing on the flag
     * if the flag O_EXCL is on then it should fail if the file 
     * already exists
     * 
    */
    //create a new openfile pointer
    //OP *op = newOP(fp, );
    //store the new open file pointer to current process
    //curproc->openFileTable[curproc->lowestIndex] = op; 


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
