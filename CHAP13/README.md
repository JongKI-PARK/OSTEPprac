
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

**6. To use pmap, you have to know the process ID of the process you’re interested in. Thus, first run ps auxw to see a list of all processes; then, pick an interesting one, such as a browser. You can also use your memory-user program in this case (indeed, you can even have that program call getpid() and print out its PID for your convenience).**

<br><br><br>

**7. Now run pmap on some of these processes, using various flags (like -X) to reveal many details about the process. What do you see? How many different entities make up a modern address space, as opposed to our simple conception of code/stack/heap?**

<br><br><br>

**8. Finally, let’s run pmap on your memory-user program, with different amounts of used memory. What do you see here? Does the output from pmap match your expectations?**

# Furthermore

# References
