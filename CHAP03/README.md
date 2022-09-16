
# Notice
Program `process-run.py` is from https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/cpu-intro  
see more details in https://github.com/remzi-arpacidusseau/ostep-homework/blob/master/cpu-intro/README.md  


# Homework (simulation)
With process-run.py , you can see the process state as it runs on the CPU. 
Process can have four different states(RUNNING, READY, WAITING, DONE) in this code.


**1. Run `process-run.py` with the following flags: `-l 5:100,5:100`. What should the CPU utilization be (e.g., the percent of time the CPU is in use?) 
Why do you know this? Use the -c and -p flags to see if you were right.**

Flag `-l 5:100` means that process has 5 instructions and all instructions are 100% CPU instructions

  ```
  $ python3 process-run.py -l 5:100,5:100
  Produce a trace of what would happen when you run these processes:
  Process 0
    cpu
    cpu
    cpu
    cpu
    cpu

  Process 1
    cpu
    cpu
    cpu
    cpu
    cpu

  Important behaviors:
    System will switch when the current process is FINISHED or ISSUES AN IO
    After IOs, the process issuing the IO will run LATER (when it is its turn)
  ```
  
**A : CPU utilization should be 100% because there is no i/o operation**  

Let's make sure it's right

  ```
  Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2        RUN:cpu         READY             1          
  3        RUN:cpu         READY             1          
  4        RUN:cpu         READY             1          
  5        RUN:cpu         READY             1          
  6           DONE       RUN:cpu             1          
  7           DONE       RUN:cpu             1          
  8           DONE       RUN:cpu             1          
  9           DONE       RUN:cpu             1          
  10          DONE       RUN:cpu             1          

Stats: Total Time 10
Stats: CPU Busy 10 (100.00%)
Stats: IO Busy  0 (0.00%)
```

<br>
**2. Now run with these flags: ./process-run.py ``-l 4:100,1:0``. These flags specify one process with 4 instructions (all to use the CPU), and one that simply issues an I/O and waits for it to be done. How long does it take to complete both processes? Use -c and -p to find out if you were right.**

If no value is given through the -L option, the default time required for I/O is 5.  

  ```
  $ python3 process-run.py -l 4:100,1:0
  Produce a trace of what would happen when you run these processes:
  Process 0
    cpu
    cpu
    cpu
    cpu

  Process 1
    io
    io_done

  Important behaviors:
    System will switch when the current process is FINISHED or ISSUES AN IO
    After IOs, the process issuing the IO will run LATER (when it is its turn)
  ```
  
  **A : 4(Process 0 doing CPU busy works) + 1(Process 1 before I/O operation) + 5(Process 1 doing I/O) + 1(Process 1 after I/O operation) = 11 (I/O operation must be started from cpu operation)**

<br>
**3. Switch the order of the processes: ``-l 1:0,4:100``. What happens now? Does switching the order matter? Why? (As always, use -c and -p to see if you were right)**


**A : **

**4. We’ll now explore some of the other flags. One important flag is -S, which determines how the system reacts when a process issues an I/O. With the flag set to SWITCH ON END, the system will NOT switch to another process while one is doing I/O, instead waiting until the process is completely finished. What happens when you run the following two processes (-l 1:0,4:100 -c -S SWITCH ON END), one doing I/O and the other doing CPU work?**

**A : **

**5. Now, run the same processes, but with the switching behavior set to switch to another process whenever one is WAITING for I/O (-l 1:0,4:100 -c -S SWITCH ON IO). What happens now? Use -c and -p to confirm that you are right.**

**A : **

**6. One other important behavior is what to do when an I/O completes. With -I IO RUN LATER, when an I/O completes, the process that issued it is not necessarily run right away; rather, whatever was running at the time keeps running. What happens when you run this combination of processes? (Run ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH ON IO -I IO RUN LATER -c -p) Are system resources being effectively utilized?**

**A : **

**7. Now run the same processes, but with -I IO RUN IMMEDIATE set, which immediately runs the process that issued the I/O. How does this behavior differ? Why might running a process that just completed an I/O again be a good idea?**

**A : **

**8. Now run with some randomly generated processes: -s 1 -l 3:50,3:50 or -s 2 -l 3:50,3:50 or -s 3 -l 3:50,3:50. See if you can predict how the trace will turn out. What happens when you use the flag -I IO RUN IMMEDIATE vs. -I IO RUN LATER? What happens when you use -S SWITCH ON IO vs. -S SWITCH ON END**

**A : **
