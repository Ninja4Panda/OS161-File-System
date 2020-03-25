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

/* global open file table */
OP openFileTbl[128];
int n_openFile = 0;             //index for the open file table
struct semaphore *array_mutex;  //global mutex only one process can modify 
                                //the table at a time

/* Create a new file pointer */
FP *newFP(char *filename, int flag) {
    FP *fp = kmalloc(sizeof *fp);
    KASSERT(fp != NULL);
    fp->pos = 0;
    fp->flag = flag;
    return fp;
}

int open(const char *filename, int flags, ...) {
    //create a new file pointer
    FP *fp = newFP(filename, flags);
    //call vfs_open with the &vnode

    //create a new open file struct 
    OP new = {1, fp, };
    //critical region need some way to control the access to the array 
    //The following doesn't work right now
    array_mutex = sem_create("array_mutex", 1);
    P(array_mutex);
    openFileTbl[n_openFile] = new;     //store the new struct in openfiletable
    OP *pt = &openFileTbl[n_openFile]; //create a new open file pointer
    n_openFile++; 
    V(array_mutex);
    
    //point it to the struct
    //store it into current process array

    //return the file descriptor
}

int close(int fd) {
    //decrease the ref count in openfile
        //if openfile ref_count == 0  
            //decrease vnode ref count
            //if the vnode ref count==1
                //call vfs_close 
}

//read into a buffer and advance the file pointer by buflen
int read() 