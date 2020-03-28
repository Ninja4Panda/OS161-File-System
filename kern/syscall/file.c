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

#include <proc.h>
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
 * There should be only one process accessing the 
 * open file at a time 
*/
OP *newOP(FP *fp, struct vnode *vnode) {
    OP *op = kmalloc(sizeof *op);
    KASSERT(op != NULL);
    op->count_mutex = sem_create("countMutex", 1);
    op->ref_count = 1;
    op->fp = fp;
    op->vnode = vnode;
    return op;
}

/**
 * Open 
 * 
 * Mode is the permission which we pass in for vfs to
 * handle it. 
 */
int sys_open(const char *filename, int flags, mode_t mode) {
    kprintf("This is test for open\n");
    kprintf("flags: %d\n", flags);
    kprintf("filename: %s\n", filename);
    kprintf("mode: %u\n", mode);
    int result;

    /* handling the copy */
    char path[NAME_MAX];
    size_t size;
    result = copyinstr((userptr_t)filename, path, NAME_MAX, &size);
    kprintf("%s\n", path);
    if (result) {
        return result;
    }
    
    /* pass the arguments to vfs_open */
    struct vnode *vnode = NULL;
    result = vfs_open(path, flags, mode, &vnode);
    kprintf("%p", vnode);
    kprintf("%d\n", vnode->vn_refcount);

    /*open file succcesful*/
    if (result == 0) {
        FP *fp = newFP(flags);
        OP *op = newOP(fp, vnode);
        int fd = curproc->lowestIndex;
        curproc->openFileTable[fd] = op;
        kprintf("%d ", curproc->openFileTable[3]->fp->read);
        kprintf("%p ", curproc->openFileTable[0]);
        kprintf("%d ", curproc->openFileTable[1]->fp->read);
        kprintf("%d ", curproc->openFileTable[2]->fp->write);
        kprintf("%d ", curproc->openFileTable[3]->fp->write);
        //return the file descriptor
        return fd;
    }
    //vfs_open can return something else???
    KASSERT(1==0);
    return 0;
}


/**
 * Close 
 * 
 * Check the ref_count in vnode, only call vfs_close when ref_count = 1
 * and now it is safe to free all the pointers and reset the lowest value.
 * If not, check ref_count of openfile. Free the pointers in the process array
 * if ref_count = 1
 * if not, reset the lowest value to indiciate that it is free.
 *  
*/
int sys_close(int fd) {
    kprintf("This is test for close\n");
    kprintf("%d\n", fd);
    /* check if the fd is valid */
    if(curproc->openFileTable[fd] == NULL) return ;

    //decrease the ref count in openfile
        //if openfile ref_count == 0  
            //decrease vnode ref count
            //if the vnode ref count==1
                //call vfs_close 
    return 0;
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

/**
 * 
 * Remember to check
 * Don't create new open file pointer 
 * simply check things and make the opFileTbl[newfd] = opFileTbl[oldfd] 
 * and ref_count++
 * 
*/
int sys_dup2(int oldfd, int newfd) {
    kprintf("This is test for dup2\n");
    kprintf("oldfd: %d\n", oldfd);
    kprintf("newfd: %d\n", newfd);
    return 1;
}
