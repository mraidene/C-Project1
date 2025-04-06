# Phase 1

## Part 1



## Part 2

### Benchmarking

### Cache Locality Analysis

### Memory Alignment

### Inlining

### Profiling

### Optimization Strategies

## Discussion Questions(Part 3)
- Explain the key differences between pointers and references in C++. When would you choose to use a pointer over a reference, and vice versa, in the context of implementing numerical algorithms?

Answer:

Citations: [Microsoft](https://learn.microsoft.com/en-us/cpp/cpp/references-cpp?view=msvc-170),
[Stack Overflow](https://stackoverflow.com/questions/46969031/when-is-a-reference-variable-appropriate-and-why-can-you-explain-the-actual-syn),
[C++ creator](https://www.stroustrup.com/bs_faq2.html#pointers-and-references),
[Reddit](https://www.reddit.com/r/cpp/comments/ezwij0/when_to_use_a_reference_type_versus_a_pointer/)

Pointers are variables that store a memory address. References are similar to 
pointers but they can't be made to point elsewhere once they store an address.

References are primarily used for two reasons:-

1) When you want to change a variable directly in a function and make it 
less verbose inside the function
2) When you want to pass a big object(more than two words)

Use pointers if you want to allocate memory or change where the pointer is pointing.

- How does the row-major and column-major storage order of matrices affect memory access patterns and cache locality during matrix-vector and matrix-matrix multiplication? Provide specific examples from your implementations and benchmarking results.

Answer:

When we store in row major and we are multiplying two matrices, the left matrix 
has contiguous memory access because it needs to keep incrementing the pointer by one
to access the next element. However, the matrix on the right will see jumps
to access the next element. Hence storing in row-major is good for the left but not for
the right. Vice versa for the column-major order where it is good for the right
and not optimal for the left.

When we discuss cache-locality, row-major leads to spatial locality for the left
and column-major leads to spatial locality for the right. Higher spatial locality
leads to better cache optimization due to the fundamental principle of cache being
based on recent and contiguous accesses being expected more than accesses in parts of
the memory which is further away.

- Describe how CPU caches work (L1, L2, L3) and explain the concepts of temporal and spatial locality. How did you try to exploit these concepts in your optimizations?

Answer:

Citation: [How To Geek](https://www.howtogeek.com/891526/l1-vs-l2-vs-l3-cache/)

When the CPU performs an operations on data, it can only store an extremely small
amount of information in its registers. However, we can't access the DRAM everytime
because that is too slow. So we use caches which are memory units located
physically closer to the cores. These allow the computer to access frequently used or
spatially close data. L1, L2, L3 refer to the varying levels of caches with L1 being 
the closest to the cores, the smallest in size and the fastest, and as we move to L3,
it becomes bigger in size, further away and slower.

Temporal: Data accessed recently is more likely to be accessed again
Spatial: Data stored closer to recently accessed data is more likely to be accessed

A cache utilizes both of these by storing recently accessed data and a chunk of the
data present after it in contiguous memory.

- What is memory alignment, and why is it important for performance? Did you observe a significant performance difference between aligned and unaligned memory in your experiments? Explain your findings.

Answer:

Citation: [Microsoft](https://learn.microsoft.com/en-us/cpp/cpp/alignment-cpp-declarations?view=msvc-170),
[Stack Overflow 1](https://stackoverflow.com/questions/41719845/memory-alignment-in-c-c),
[Stack Overflow 2](https://softwareengineering.stackexchange.com/questions/328775/how-important-is-memory-alignment-does-it-still-matter)

Different variables have different sizes, for example int(32) is 4 bytes, char is 1 byte, and so on.
Memory addresses inside a computer are usually byte-aligned and the CPU is word-aligned.
When we try to store variables, if they are unaligned, the compiler will store them
with no padding which would mean that a lot of shifting operations need to be done in order to use the data.
When the data is aligned, accessing information is straightforward although it is not optimal
in terms of memory storage.

- Discuss the role of compiler optimizations (like inlining) in achieving high performance. How did the optimization level affect the performance of your baseline and optimized implementations? What are the potential drawbacks of aggressive optimization?
- Based on your profiling experience, what were the main performance bottlenecks in your initial implementations? How did your profiling results guide your optimization efforts?
- Reflect on the teamwork aspect of this assignment. How did dividing the initial implementation tasks and then collaborating on analysis and optimization work? What were the challenges and benefits of this approach?