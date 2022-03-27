
1. After fork() system call , values are independent between parant and child process.

2. Child process duplicates parant process' file descriptor. But they share file table connected to inode.

3. After pipe() two file descriptors are returned.
Because of 2 and 3, for IPC (Inter Process Communication), pipe() should be called before fork().

4. Wait system call is made for parant process waiting for child process to be terminated.
So when child process uses wait() it returns -1
