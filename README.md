# Parallels

## Introduction

In this project, you will learn the basic approaches to parallelism, and implement some algorithms applying it.



## Contents

1. [Chapter I](#chapter-i) \
   1.1. [Building](#building)
2. [Chapter II](#chapter-ii) \
   2.1. [Part 1](#part-1-ant-colony-optimization-algorithm) \
   2.2. [Part 2](#part-2-solving-systems-of-linear-equations-(SLE)) \
   2.3. [Part 3](#part-3-winograd-algorithm)


## Chapter I  


## Building

To builld project `make` and `cmake` must be installed. 

Enter project directory in the terminal and input `make`. It'll start project building in `build` directory with cmake. After that `ant.out, gauss.out, winograd.out` will apeared inside `build` directory, where you can run one of them. You also can run `make ant, make gauss, make winograd` to build files and run relative program.

```
> make ant
...
./build/ant.out
Matrix  rows:
> 
```
If you see the output above - everything is correct and the program works just fine.

## Chapter II

 Examples are proposed to show how to use console input. For more demonstrative results - input sagnificant more number of rows/cols and/or number of iteration.

## Part 1. Ant colony optimization algorithm

Enter `make ant`.
Then enter number of rows and columns (they must be equal due to graph representation, otherwise there will be an error output). You can choose to fill the matrix randomly or manualy. Also you need enter the number of iterations. 
After setting all the initials, the program will proceed in two ways - one- and multithread. 
Output for each way:

- The distance required to pass all nodes
- A list of vertices, in which order the ant traverses the nodes in order to travel the minimum distance
- Obtained time [ms]

Example:
```
> make ant
./build/ant.out
Matrix  rows: 5
Matrix  columns: 5
Enter mode
0 - randomly
* - manually
> 0
Enter number of iterations:
> 2
Distance: 20 
Vertices: 5 4 2 3 1 5 
Single thread execution time: 0[ms]
Distance: 20 
Vertices: 2 3 1 5 4 2 
Multi thread execution time: 0[ms]
```

## Part 2. Solving systems of linear equations (SLE)

Enter `make gauss`.
Then enter number of rows and columns (the number of columns must be grater than the number of rows by 1). You can choose to fill the matrix randomly or manualy. Also you need enter the number of iterations. 
After setting all the initials, the program will proceed in two ways - one- and multithread. 
Output for each way:

- Gauss solution
- Obtained time [ms]

Example:
```
> make gauss
./build/gauss.out
Matrix A rows: 3
Matrix A columns: 4
Enter mode
0 - randomly
* - manually
> 0
Enter number of iterations:
> 2
Answers: -0.363636 -1.63636 2.45455 
Single thread execution time: 0[ms]
Answers: -0.363636 -1.63636 2.45455 
Multi thread execution time: 0[ms]
```

## Part 3. Winograd algorithm

Enter `make winograd`.

Then enter number of rows and columns (the number of columns must be equal than the number of rows). You can choose to fill the matrix randomly or manualy. Also you need enter the number of iterations. 
After setting all the initials, the program will proceed in two ways - one- and multithread. 
Output for each way:

- Matrix A and Matix B (if rows and cols < 10)
- Multiplication result matrix(if rows and cols < 10)
- Obtained time [ms] with one thread, pipeline multithreading and classical parallelism with the number of threads equal to 2, 4, 8, ..., 4 * (number of logical computer processors)

Example:
```
> make winograd
./build/winograd.out
Matrix A rows: 5
Matrix A columns: 5
Enter mode
0 - randomly
* - manually
> 0
Matrix B rows: 5
Matrix B columns: 5
Enter mode
0 - randomly
* - manually
> 0
Enter number of iterations:
> 1
Matrix A:
  1   5   3   3  10 
 10   6   8   3   7 
  9   2   2   6   3 
  2  10   2   1   8 
  7   4   4   2   8 

Matrix B:
  5  10   5   8   2 
  2   3  10   4   8 
  1   7   7   2   1 
  3   4   4   4   6 
 10   9   1  10   5 

Result #1 (single thread):
127 148  98 146 113 
149 249 185 202 129 
 99 161 106 138  87 
115 140 136 144 132 
133 190 119 168 102 

Result #2 (pipeline):
127 148  98 146 113 
149 249 185 202 129 
 99 161 106 138  87 
115 140 136 144 132 
133 190 119 168 102 

Result #3 (multithread):
127 148  98 146 113 
149 249 185 202 129 
 99 161 106 138  87 
115 140 136 144 132 
133 190 119 168 102 

Single thread execution time = 0 [ms]
Pipeline execution time = 0 [ms]
 2 threads execution time = 0 [ms]
 4 threads execution time = 0 [ms]
 6 threads execution time = 0 [ms]
 8 threads execution time = 0 [ms]
10 threads execution time = 0 [ms]
12 threads execution time = 0 [ms]
14 threads execution time = 0 [ms]
16 threads execution time = 0 [ms]
18 threads execution time = 0 [ms]
20 threads execution time = 0 [ms]
22 threads execution time = 0 [ms]
24 threads execution time = 0 [ms]
26 threads execution time = 0 [ms]
28 threads execution time = 0 [ms]
30 threads execution time = 0 [ms]
32 threads execution time = 0 [ms]
34 threads execution time = 0 [ms]
36 threads execution time = 0 [ms]
38 threads execution time = 0 [ms]
40 threads execution time = 0 [ms]
42 threads execution time = 0 [ms]
44 threads execution time = 0 [ms]
46 threads execution time = 0 [ms]
48 threads execution time = 0 [ms]
```
