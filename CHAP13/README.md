
# Notice

# Homework

**1. The first Linux tool you should check out is the very simple tool free. First, type man free and read its entire manual page; it’s short, don’t worry!**

A : `free.txt` is for question 1. By `$ man free > free.txt`, `free.txt` is made. According to this manual, it displays amount of free and used memory in the system with the information gathered from /proc/meminfo.

<br><br><br>

**2. Now, run free, perhaps using some of the arguments that might be useful (e.g., -m, to display memory totals in megabytes). How much memory is in your system? How much is free? Do these numbers match your intuition?**

  ```
  $ free
                total        used        free      shared  buff/cache   available
  Mem:       24487976      543264    22021184       47624     1923528    23521436
  Swap:       8388604           0     8388604

  ```

<br><br><br>

**3. Next, create a little program that uses a certain amount of memory, called memory-user.c. This program should take one command line argument: the number of megabytes of memory it will use. When run, it should allocate an array, and constantly stream through the array, touching each entry. The program should do this indefinitely, or, perhaps, for a certain amount of time also specified at the command line.**

A : `memroy-user.c` is for question 3. 

<br><br><br>

**4. Now, while running your memory-user program, also (in a different terminal window, but on the same machine) run the free tool. How do the memory usage totals change when your program is running? How about when you kill the memory-user program? Do the numbers match your expectations? Try this for different amounts of memory usage. What happens when you use really large amounts of memory?**

A: Command to terminal `$ memory-user 100 0`  
before : 
  ```
  $ free -m
                total        used        free      shared  buff/cache   available
  Mem:          23914         551       20245          46        3117       22923
  Swap:          8191           0        8191
  ```
after : 
  ```
  $ free -m
                total        used        free      shared  buff/cache   available
  Mem:          23914         552       20244          46        3117       22923
  Swap:          8191           0        8191
  ```
  I allocated 100MB memory for this program but `free` shows that system only used 1MB. 
  
<br><br><br>

**5. Let’s try one more tool, known as pmap. Spend some time, and read the pmap manual page in detail.**

A : `man pmap` see `man_pmap.txt`. According to the manual of pmap, 

<br><br><br>

**6. To use pmap, you have to know the process ID of the process you’re interested in. Thus, first run `ps auxw` to see a list of all processes; then, pick an interesting one, such as a browser. You can also use your memory-user program in this case (indeed, you can even have that program call getpid() and print out its PID for your convenience).**

A : I used `ps auxw | grep memory-user` to find out pid.

  ```
  $ ps auxw | grep memory-user
  kipark    166078 68.8  0.0 104892  1412 pts/0    R+   14:11   0:38 ./memory-user 100 0
  kipark    166087  0.0  0.0   6432   720 pts/1    S+   14:12   0:00 grep --color=auto memory-user
  $ pmap 166078
  166078:   ./memory-user 100 0
  000055ce91b2f000      4K r---- memory-user
  000055ce91b30000      4K r-x-- memory-user
  000055ce91b31000      4K r---- memory-user
  000055ce91b32000      4K r---- memory-user
  000055ce91b33000      4K rw--- memory-user
  000055ce93032000    132K rw---   [ anon ]
  00007f3df954c000 102404K rw---   [ anon ]
  00007f3dff94d000    136K r---- libc-2.31.so
  00007f3dff96f000   1504K r-x-- libc-2.31.so
  00007f3dffae7000    312K r---- libc-2.31.so
  00007f3dffb35000     16K r---- libc-2.31.so
  00007f3dffb39000      8K rw--- libc-2.31.so
  00007f3dffb3b000     24K rw---   [ anon ]
  00007f3dffb56000      4K r---- ld-2.31.so
  00007f3dffb57000    140K r-x-- ld-2.31.so
  00007f3dffb7a000     32K r---- ld-2.31.so
  00007f3dffb83000      4K r---- ld-2.31.so
  00007f3dffb84000      4K rw--- ld-2.31.so
  00007f3dffb85000      4K rw---   [ anon ]
  00007ffcf73a4000    132K rw---   [ stack ]
  00007ffcf73ec000     12K r----   [ anon ]
  00007ffcf73ef000      4K r-x--   [ anon ]
  ffffffffff600000      4K --x--   [ anon ]
  total           104896K
  ```
The result shows  

<br><br><br>

**7. Now run pmap on some of these processes, using various flags (like -X) to reveal many details about the process. What do you see? How many different entities make up a modern address space, as opposed to our simple conception of code/stack/heap?**

A : 
  
<br><br><br>

**8. Finally, let’s run pmap on your memory-user program, with different amounts of used memory. What do you see here? Does the output from pmap match your expectations?**

A : More details are shown by `pmap -x option`. See below.
  ```
  $ ps auxw | grep memory-user
  kipark    166168 66.2  0.0 104892  1448 pts/0    R+   14:24   0:02 ./memory-user 100 0
  kipark    166172  0.0  0.0   6432   724 pts/1    S+   14:24   0:00 grep --color=auto memory-user
  $ pmap -x 166168
  166168:   ./memory-user 100 0
  Address           Kbytes     RSS   Dirty Mode  Mapping
  00005613f6192000       4       4       0 r---- memory-user
  00005613f6193000       4       4       0 r-x-- memory-user
  00005613f6194000       4       4       0 r---- memory-user
  00005613f6195000       4       4       4 r---- memory-user
  00005613f6196000       4       4       4 rw--- memory-user
  00005613f7316000     132       4       4 rw---   [ anon ]
  00007f23b0a60000  102404       4       4 rw---   [ anon ]
  00007f23b6e61000     136     136       0 r---- libc-2.31.so
  00007f23b6e83000    1504     884       0 r-x-- libc-2.31.so
  00007f23b6ffb000     312     148       0 r---- libc-2.31.so
  00007f23b7049000      16      16      16 r---- libc-2.31.so
  00007f23b704d000       8       8       8 rw--- libc-2.31.so
  00007f23b704f000      24      20      20 rw---   [ anon ]
  00007f23b706a000       4       4       0 r---- ld-2.31.so
  00007f23b706b000     140     140       0 r-x-- ld-2.31.so
  00007f23b708e000      32      32       0 r---- ld-2.31.so
  00007f23b7097000       4       4       4 r---- ld-2.31.so
  00007f23b7098000       4       4       4 rw--- ld-2.31.so
  00007f23b7099000       4       4       4 rw---   [ anon ]
  00007fffcc2f6000     132      16      16 rw---   [ stack ]
  00007fffcc3f7000      12       0       0 r----   [ anon ]
  00007fffcc3fa000       4       4       0 r-x--   [ anon ]
  ffffffffff600000       4       0       0 --x--   [ anon ]
  ---------------- ------- ------- -------
  total kB          104896    1448      88
  ```
  More detailed result to pmap ./memory-user 100 0 shows that 
  
<br><br><br>

# Furthermore

# References
[1] https://unix.stackexchange.com/questions/105604/the-meaning-of-output-of-pmap  
[2] https://stackoverflow.com/questions/28461302/malloc-anonymous-mapping-and-magic-area  
[3] https://man7.org/linux/man-pages/man1/pmap.1.html  
[4] https://docs.oracle.com/cd/E19683-01/816-0210/6m6nb7mhj/index.html  
