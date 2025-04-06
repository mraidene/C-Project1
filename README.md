# Phase 1

## Part 1



## Part 2

The details of Part 2 are included in report.pdf.

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

Answer:

Compiler optimizations, like inlining, can significantly boost performance by reducing the overhead of function calls. Inlining a function means embedding the function's code directly where the function is called, avoiding the overhead of jumping to another memory location. This is particularly helpful in numerical algorithms that rely on many small functions, such as dot products or matrix multiplications, where the cost of a function call can add up quickly.

In our case, inlining the dot product function resulted in a major performance boost. The baseline implementation, where the dot product was a separate function, introduced unnecessary function call overhead and data copying, which slowed down execution. After inlining the logic and removing the redundant memory allocations, we observed significant improvements across all dimensions.

However, aggressive optimization comes with some trade-offs. While inlining reduces overhead, it can also increase the size of the binary code, especially if the inlined functions are large or called frequently. This could lead to increased memory usage or even cache misses if the code size becomes too large to fit in cache. In some cases, too many inlines may result in code bloat, which negatively affects the performance due to increased instruction cache misses.

- Based on your profiling experience, what were the main performance bottlenecks in your initial implementations? How did your profiling results guide your optimization efforts?

Answer:

From the profiling, the primary performance bottleneck in the initial implementation was the dotproduct() function, which was consuming about 25% of the total runtime. Additionally, there was unnecessary overhead due to copying rows and columns of matrices into contiguous memory before performing dot products, as well as memory deallocation using free().

The profiling results helped guide our optimization efforts in two key areas. First, we focused on inlining the dot product function. By removing the function call and directly embedding the dot product logic inside the main function loops, we eliminated the overhead and unnecessary memory copying. Second, we optimized memory usage by directly accessing the matrix data without copying it into contiguous blocks. This eliminated the need for costly free() operations and reduced memory fragmentation.

After these optimizations, we saw a significant reduction in runtime, especially for larger matrix dimensions.
  
- Reflect on the teamwork aspect of this assignment. How did dividing the initial implementation tasks and then collaborating on analysis and optimization work? What were the challenges and benefits of this approach?

  Answer:

Dividing the initial implementation tasks allowed us to efficiently distribute the workload and tackle different components of the matrix operations concurrently. Each team member could focus on writing specific functions or implementing particular matrix algorithms, which made the initial phase much faster. We could leverage individual strengths, such as expertise in certain algorithms or coding techniques.

The collaboration during the analysis and optimization phase proved to be very beneficial. By profiling the code as a team, we were able to identify key bottlenecks and areas for improvement. For example, one team member focused on understanding the impact of memory alignment, while another focused on compiler optimizations. By pooling our insights, we developed a comprehensive optimization strategy.

One challenge was coordinating the changes to ensure that the optimizations did not break the overall code structure. Since we were working on separate sections, some optimizations (like memory handling) had to be carefully integrated to avoid errors. Another challenge was ensuring that all team members understood the profiling results and how to act on them. In the end, these challenges were overcome through communication and shared learning, which enhanced our overall approach.

The main benefit was that this collaborative approach helped us optimize the code in a more targeted manner, significantly improving performance without overhauling the entire implementation. The synergy of the team's diverse skills and knowledge was key to achieving a highly optimized solution.
