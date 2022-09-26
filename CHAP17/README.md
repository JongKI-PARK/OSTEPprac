
# Notice

Source code `malloc.py` is from https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/vm-freespace.  
See more details about this program in https://github.com/remzi-arpacidusseau/ostep-homework/blob/master/vm-freespace/README.md.  

  ```
  $ python3 malloc.py --help
  Usage: malloc.py [options]

  Options:
    -h, --help            show this help message and exit
    -s SEED, --seed=SEED  the random seed
    -S HEAPSIZE, --size=HEAPSIZE
                          size of the heap
    -b BASEADDR, --baseAddr=BASEADDR
                          base address of heap
    -H HEADERSIZE, --headerSize=HEADERSIZE
                          size of the header
    -a ALIGNMENT, --alignment=ALIGNMENT
                          align allocated units to size; -1->no align
    -p POLICY, --policy=POLICY
                          list search (BEST, WORST, FIRST)
    -l ORDER, --listOrder=ORDER
                          list order (ADDRSORT, SIZESORT+, SIZESORT-, INSERT-
                          FRONT, INSERT-BACK)
    -C, --coalesce        coalesce the free list?
    -n OPSNUM, --numOps=OPSNUM
                          number of random ops to generate
    -r OPSRANGE, --range=OPSRANGE
                          max alloc size
    -P OPSPALLOC, --percentAlloc=OPSPALLOC
                          percent of ops that are allocs
    -A OPSLIST, --allocList=OPSLIST
                          instead of random, list of ops (+10,-0,etc)
    -c, --compute         compute answers for me
    ```
      
# Homework

**1. First run with the flags `-n 10 -H 0 -p BEST -s 0` to generate a few random allocations and frees. Can you predict what alloc()/free() will return? Can you guess the state of the free list after each request? What do you notice about the free list over time?**

**2. How are the results different when using a WORST fit policy to search the free list (-p WORST)? What changes?**

**3. What about when using FIRST fit (-p FIRST)? What speeds up when you use first fit?**

**4. For the above questions, how the list is kept ordered can affect the time it takes to find a free location for some of the policies. Use the different free list orderings (-l ADDRSORT, -l SIZESORT+, -l SIZESORT-) to see how the policies and the list orderings interact.**

**5. Coalescing of a free list can be quite important. Increase the number of random allocations (say to -n 1000). What happens to larger allocation requests over time? Run with and without coalescing (i.e., without and with the -C flag). What differences in outcome do you see? How big is the free list over time in each case? Does the ordering of the list matter in this case?**

**6. What happens when you change the percent allocated fraction -P to higher than 50? What happens to allocations as it nears 100? What about as the percent nears 0?**

**7. What kind of specific requests can you make to generate a highly fragmented free space? Use the -A flag to create fragmented free lists, and see how different policies and options change the organization of the free list.**
