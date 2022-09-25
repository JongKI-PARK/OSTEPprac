
# Notice

Chapter 14 aims to become familiar with memory allocation and tools such as gdb and valgrind related to memory allocation  

# Homework

**1. First, write a simple program called null.c that creates a pointer to an integer, sets it to NULL, and then tries to dereference it. Compile this into an executable called null. What happens when you run this program?**  

A : `null.c` is for question 1. When i execute this, a segmentation fault is generated.  

<br><br>  

**2. Next, compile this program with symbol information included (with the -g flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information about variable names and the like. Run the program under the debugger by typing gdb null and then, once gdb is running, typing
run. What does gdb show you?**  

A : gdb shows 
  ```
    Program recieved signal SIGSEGV, Segmentation fault.
    0x000055555555513d in main () at null.c:10
    10    int i = *pointer;
    (gdb)
  ```
  
<br><br>  

**3. Finally, use the valgrind tool on this program. We’ll use the memcheck tool that is a part of valgrind to analyze what happens. Run this by typing in the following: valgrind --leak-check=yes null. What happens when you run this? Can you interpret the output from the tool?**  

A : Using the valgrind tool `valgrind --leak-check=yes ./null` gives the following results:  
  It says that there was no memory leakage but there was "Invalid read of size 4" (invalid access)  
  
  ```
  ==63270== Memcheck, a memory error detector
  ==63270== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
  ==63270== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
  ==63270== Command: ./null
  ==63270== Parent PID: 61832
  ==63270== 
  ==63270== Invalid read of size 4
  ==63270==    at 0x10913D: main (null.c:10)
  ==63270==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
  ==63270== 
  ==63270== 
  ==63270== Process terminating with default action of signal 11 (SIGSEGV)
  ==63270==  Access not within mapped region at address 0x0
  ==63270==    at 0x10913D: main (null.c:10)
  ==63270==  If you believe this happened as a result of a stack
  ==63270==  overflow in your program's main thread (unlikely but
  ==63270==  possible), you can try to increase the size of the
  ==63270==  main thread stack using the --main-stacksize= flag.
  ==63270==  The main thread stack size used in this run was 8388608.
  ==63270== 
  ==63270== HEAP SUMMARY:
  ==63270==     in use at exit: 0 bytes in 0 blocks
  ==63270==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
  ==63270== 
  ==63270== All heap blocks were freed -- no leaks are possible
  ==63270== 
  ==63270== For lists of detected and suppressed errors, rerun with: -s
  ==63270== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
  ```  

<br><br>  

**4. Write a simple program that allocates memory using malloc() but forgets to free it before exiting. What happens when this program runs? Can you use gdb to find any problems with it? How about valgrind (again with the --leak-check=yes flag)?**  

A :  `nofree.c` is for question 4. When running gdb, it didn't seem to find any errors.
  ```
  (gdb) run
  Starting program: /home/kipark/OSTEPprac/CHAP14/nofree
  [Inferior 1 (process 137494) exited normally]
  (gdb)
  ```
  
  but in valgrind, it gives the following results. It shows that there was a memory leakage which was allocated but not freed 4bytes.  
  ```
  ==137756== Memcheck, a memory error detector
  ==137756== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
  ==137756== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
  ==137756== Command: ./nofree
  ==137756==
  ==137756==
  ==137756== HEAP SUMMARY:
  ==137756==     in use at exit: 4 bytes in 1 blocks
  ==137756==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
  ==137756==
  ==137756== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
  ==137756==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
  ==137756==    by 0x10915E: main (nofree.c:9)
  ==137756==
  ==137756== LEAK SUMMARY:
  ==137756==    definitely lost: 4 bytes in 1 blocks
  ==137756==    indirectly lost: 0 bytes in 0 blocks
  ==137756==      possibly lost: 0 bytes in 0 blocks
  ==137756==    still reachable: 0 bytes in 0 blocks
  ==137756==         suppressed: 0 bytes in 0 blocks
  ==137756==
  ==137756== For lists of detected and suppressed errors, rerun with: -s
  ==137756== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
  ```
  
<br><br>  

**5. Write a program that creates an array of integers called data of size 100 using malloc; then, set data[100] to zero. What happens when you run this program? What happens when you run this program using valgrind? Is the program correct?**  

A : `malloc100.c` is for question 5. malloc100.c tries to access inaccessable memory location. Nothing happens when i run this program.
    valgrind shows that there is an invalid write of size 4. See the result of valgrind below.  
  
  ```
  ==147002== Memcheck, a memory error detector
  ==147002== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
  ==147002== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
  ==147002== Command: ./a.out
  ==147002==
  ==147002== Invalid write of size 4
  ==147002==    at 0x10918D: main (in /home/kipark/OST/CHAP15/a.out)
  ==147002==  Address 0x4a541d0 is 0 bytes after a block of size 400 alloc'd
  ==147002==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
  ==147002==    by 0x10917E: main (in /home/kipark/OST/CHAP15/a.out)
  ==147002==
  ==147002==
  ==147002== HEAP SUMMARY:
  ==147002==     in use at exit: 0 bytes in 0 blocks
  ==147002==   total heap usage: 1 allocs, 1 frees, 400 bytes allocated
  ==147002==
  ==147002== All heap blocks were freed -- no leaks are possible
  ==147002==
  ==147002== For lists of detected and suppressed errors, rerun with: -s
  ==147002== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
  ```
  
<br><br>  

**6. Create a program that allocates an array of integers (as above), frees them, and then tries to print the value of one of the elements of the array. Does the program run? What happens when you use valgrind on it?**  

A :  `malloc2.c` is for question 6. It tries to access which is inaccessable(already freed memory space which is invalid access).
  When running this program, it shows normal result `The data in pointer[10] is 100` as if it was valid access.
  Using valgrind shows more precise results.
  
  ```
  ==147243== Memcheck, a memory error detector
  ==147243== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
  ==147243== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
  ==147243== Command: ./a.out
  ==147243==
  ==147243== Invalid read of size 4
  ==147243==    at 0x1091E0: main (in /home/kipark/OST/CHAP15/a.out)
  ==147243==  Address 0x4a54068 is 40 bytes inside a block of size 400 free'd
  ==147243==    at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
  ==147243==    by 0x1091DB: main (in /home/kipark/OST/CHAP15/a.out)
  ==147243==  Block was alloc'd at
  ==147243==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
  ==147243==    by 0x10919E: main (in /home/kipark/OST/CHAP15/a.out)
  ==147243==
  The data in pointer[10] is 100
  ==147243==
  ==147243== HEAP SUMMARY:
  ==147243==     in use at exit: 0 bytes in 0 blocks
  ==147243==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
  ==147243==
  ==147243== All heap blocks were freed -- no leaks are possible
  ==147243==
  ==147243== For lists of detected and suppressed errors, rerun with: -s
  ==147243== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
  ```

<br><br>  

**7. Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?**  

A :  
  
<br><br>  

**8. Try out some of the other interfaces to memory allocation. For example, create a simple vector-like data structure and related routines that use realloc() to manage the vector. Use an array to store the vectors elements; when a user adds an entry to the vector, use realloc() to allocate more space for it. How well does such a vector perform? How does it compare to a linked list? Use valgrind to help you find bugs.**  

A :  
  
<br><br>  

**9. Spend more time and read about using gdb and valgrind. Knowing your tools is critical; spend the time and learn how to become an expert debugger in the UNIX and C environment.**  

A :  
