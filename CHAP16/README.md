
# Segmentation

If the entire address space is loaded into memory using the base and bound registers, a large unused space between the stack and the heap is wasted. The idea that emerged to solve this problem is Segmentation. Instead of having a single base bound value for each process, a base and bound value exist for each segment. Here, a segment is a contiguous address space with a specific length. As an example of a segment, four segments can be considered in the address space of a process: code, data, heap, and stack. The advantage of segmentation is that it is easy to share between multiple processes. When the same program is executed by different processes, the code part can be shared. Another advantage is that protection can be supported in units of segments. It is possible to set different permissions for each segment, such as making the code segment part read execure, and the heap part enabling read and write.  

When setting the size of a segment, it can be set to a large size or a small size. They are called coarse grained segment size and fine grained segment size, respectively. If it is set to coarse grained, the amount of segments to be allocated for each process becomes smaller. (Give small chunks to large chunks. Usually, 4 segments are allocated for code, data, heap, and stack.) If fine grained is set, the number of segments increases. If the number of segments increases in this way, it cannot be managed with registers, but is managed with a segment table.  


## Notice

Source code `segmentation.py` is from https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/vm-segmentation  
See more details about this program in https://github.com/remzi-arpacidusseau/ostep-homework/blob/master/vm-segmentation/README.md  


## Homework

**1. First let’s use a tiny address space to translate some addresses. Here’s a simple set of parameters with a few different random seeds; can you translate the addresses?**
  ```
  segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0
  segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1
  segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2
  ```

A : 
  first : 
  ```
  $ python3 segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0
  ARG seed 0
  ARG address space size 128
  ARG phys mem size 512

  Segment register information:

    Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
    Segment 0 limit                  : 20

    Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
    Segment 1 limit                  : 20

  Virtual Address Trace
    VA  0: 0x0000006c (decimal:  108) --> PA or segmentation violation?
    VA  1: 0x00000061 (decimal:   97) --> PA or segmentation violation?
    VA  2: 0x00000035 (decimal:   53) --> PA or segmentation violation?
    VA  3: 0x00000021 (decimal:   33) --> PA or segmentation violation?
    VA  4: 0x00000041 (decimal:   65) --> PA or segmentation violation?

  For each virtual address, either write down the physical address it translates to
  OR write down that it is an out-of-bounds address (a segmentation violation). For
  this problem, you should assume a simple address space with two segments: the top
  bit of the virtual address can thus be used to check whether the virtual address
  is in segment 0 (topbit=0) or segment 1 (topbit=1). Note that the base/limit pairs
  given to you grow in different directions, depending on the segment, i.e., segment 0
  grows in the positive direction, whereas segment 1 in the negative.
  ```
  
  second : 
  ```
  $ python3 segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1
  ARG seed 1
  ARG address space size 128
  ARG phys mem size 512

  Segment register information:

    Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
    Segment 0 limit                  : 20

    Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
    Segment 1 limit                  : 20

  Virtual Address Trace
    VA  0: 0x00000011 (decimal:   17) --> PA or segmentation violation?
    VA  1: 0x0000006c (decimal:  108) --> PA or segmentation violation?
    VA  2: 0x00000061 (decimal:   97) --> PA or segmentation violation?
    VA  3: 0x00000020 (decimal:   32) --> PA or segmentation violation?
    VA  4: 0x0000003f (decimal:   63) --> PA or segmentation violation?
  ```
  third : 
  ```
  $ python3 segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2
  ARG seed 2
  ARG address space size 128
  ARG phys mem size 512

  Segment register information:

    Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
    Segment 0 limit                  : 20

    Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
    Segment 1 limit                  : 20

  Virtual Address Trace
    VA  0: 0x0000007a (decimal:  122) --> PA or segmentation violation?
    VA  1: 0x00000079 (decimal:  121) --> PA or segmentation violation?
    VA  2: 0x00000007 (decimal:    7) --> PA or segmentation violation?
    VA  3: 0x0000000a (decimal:   10) --> PA or segmentation violation?
    VA  4: 0x0000006a (decimal:  106) --> PA or segmentation violation?
  ```
<br><br><br>

**2. Now, let’s see if we understand this tiny address space we’ve constructed (using the parameters from the question above). What is the highest legal virtual address in segment 0? What about the lowest legal virtual address in segment 1? What are the lowest and highest illegal addresses in this entire address space? Finally, how would you run segmentation.py with the -A flag to test if you are right?**

A:

<br><br><br>

**3. Let’s say we have a tiny 16-byte address space in a 128-byte physical memory. What base and bounds would you set up so as to get the simulator to generate the following translation results for the specified address stream: valid, valid, violation, ..., violation, valid, valid? Assume the following parameters:**
`segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 ? --l0 ? --b1 ? --l1 ?`

A:

<br><br><br>


**4. Assume we want to generate a problem where roughly 90% of the randomly-generated virtual addresses are valid (not segmentation violations). How should you configure the simulator to do so? Which parameters are important to getting this outcome?**

A:

<br><br><br>


**5. Can you run the simulator such that no virtual addresses are valid? How?**

A: 
