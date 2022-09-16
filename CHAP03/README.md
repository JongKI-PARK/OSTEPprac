
# Notice
Program `process-run.py` is from https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/cpu-intro  
see more details in https://github.com/remzi-arpacidusseau/ostep-homework/blob/master/cpu-intro/README.md  


# Homework (simulation)
With process-run.py , you can see the process state as it runs on the CPU. 
Process can have four different states(RUNNING, READY, WAITING, DONE) in this code.

1. Run `process-run.py` with the following flags: `-l 5:100,5:100`. What should the CPU utilization be (e.g., the percent of time the CPU is in use?) Why do you know  this? Use the -c and -p flags to see if you were right.

Flag `5:100` means that process has 5 instructions and all instructions are 100% CPU instructions

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
