
# Notice
P

# Homework (simulation)

**1. Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?**

A: `fork1.c` is for question 1. After fork() system call , values are independent between parant and child process. Child process cannot see parent process's value x and Parent process neither.

<br><br><br>

**2. Write a program that opens a file (with the open() system call) and then calls fork() to create a new process. Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?**

A: `fork2.c` is for question 2. Both parent and Child process can access the file descripter. The file descripter they access is the same. Child process duplicates parant process' file descriptor. But they share file table connected to inode. The process scheduler determines which of the parent or child processes to run first.

<br><br><br>

**3. Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?**

A: ??

<br><br><br>

**4. Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls. See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe(). Why do you think there are so many variants of the same basic call?**

A: ??

<br><br><br>

**5. Now write a program that uses wait() to wait for the child process to finish in the parent. What does wait() return? What happens if you use wait() in the child?**

A: `fork5.c` and `fork5_1.c` is for question 5. If child process uses wait(), it returns error -1. If parent process uses wait(), it returns child process's pid. (wait() system call is made for parant process waiting for child process to be terminated. So when child process uses wait() it returns -1)

<br><br><br>

**6. Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be useful?**

A: 

<br><br><br>

**7. Write a program that creates a child process, and then in the child closes standard output (STDOUT_FILENO). What happens if the child calls printf() to print some output after closing the descriptor?**

A: `fork7.c` is for question 7. If child process closes standard output(STDOUT_FILENO), result of printf() in child process will not show on terminal. However, the stdout of the file descriptor table of the parent process is independent of the stdout of the file descriptor table of the child process.

file descripter table  
parant      child  
 ___         ___  
| 0 |       | 0 |  
| 1 |     ~~| 1 |~~  
| 2 |       | 2 |  
| 3 |       | 3 |  
| ~ |       | ~ |  


<br><br><br>

**8. Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the pipe() system call**

A: 

<br><br><br>

# Conclusion

3. After pipe() two file descriptors are returned.
Because of 2 and 3, for IPC (Inter Process Communication), pipe() should be called before fork().
