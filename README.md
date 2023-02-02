# Parallels

## Introduction

In this project, you will learn the basic approaches to parallelism, and implement some algorithms applying it.



## Contents

1. [Chapter I](#chapter-i) \
   1.1. [Introduction](#introduction)
2. [Chapter II](#chapter-ii) \
   2.1. [Multithreading](#multithreading) \
   2.2. [Mutexes](#mutexes) \
   2.3. [Pipeline parallelism](#pipeline-parallelism)
3. [Chapter III](#chapter-iii) \
   3.1. [Part 1](#part-1-ant-colony-optimization-algorithm-(ACO))  \
   3.2. [Part 2](#part-2-solving-systems-of-linear-equations-(SLE))  \
   3.3. [Part 3](#part-3-winograd-algorithm)


## Chapter I  


## Building

To builld project `make` and `cmake` must be installed. 

Enter project directory in the terminal and input `make`. It'll start project building in `build` directory with cmake. After that `ant.out, gauss.out, winograd.out` apeared inside `build` directory, where you can run one of them. You also can run `make ant, make gauss, make winograd` to build files and run relative program.

```
> make ant
...
./build/ant.out
Matrix  rows:
> 
```
If you see the output below - everything is correct and the program works just fine.

## Chapter II





## Chapter III

## Part 1. Ant colony optimization algorithm (ACO)

You need to implement an ACO algorithm to solve the traveling salesman problem from the *A2_SimpleNavigator* project with and without parallel computing:
- The program must be developed in C++ language of C++17 standard
- The program code must be located in the src folder
- When writing code it is necessary to follow the Google style
- Do not use outdated language constructs and libraries
- Provide a Makefile for building the program (with targets all, clean, ant)
- The program must have a console interface
- The user sets the matrix for the traveling salesman problem
- The user sets the number of executions *N*
- Display the results of each of the algorithms for the specified matrix
- Measure the time it takes to execute *N* times an ACO algorithm applying parallelism for a user-defined matrix
- Measure the time it takes to execute *N* times the usual ant algorithm for a user-defined matrix
- Display the obtained time
- Use mutexes to lock access to data for parallel implementation

## Part 2. Solving systems of linear equations (SLE)

You need to implement the usual and parallel algorithms to solve the SLE using the Gaussian elimination method:
- The program must be developed in C++ language of C++17 standard
- The program code must be located in the src folder
- When writing code it is necessary to follow the Google style
- Do not use outdated language constructs and libraries
- Add to an existing Makefile target called "gauss" for building the program
- The program must have a console interface
- The user sets the matrix describing the SLE
- The user sets the number of executions *N*
- Display the results of each of the algorithms for the specified SLE
- Measure the time it takes to execute *N* times a parallel algorithm for solving a user-defined SLE
- Measure the time it takes to execute *N* times the usual algorithm for solving a user-defined SLE
- Display the obtained time
- Use mutexes to lock access to data for parallel implementation

## Part 3. Winograd algorithm

You need to implement the Winograd algorithm of matrix multiplication without using parallelism, as well as using pipeline and classical methods of parallelism:
- The program must be developed in C++ language of C++17 standard
- The program code must be located in the src folder
- When writing code it is necessary to follow the Google style
- Do not use outdated language constructs and libraries
- Add to an existing Makefile target called "winograd" for building the program
- There should be four stages of the pipeline work
- The program must have a console interface
- There should be two ways of entering:
    - The user sets both matrices for multiplication
    - The user sets dimensions of the matrices, which are then filled into the program randomly
- The user sets the number of executions *N*
- Display the results of each of the algorithms as well as the generated matrices
- Measure the time it takes to execute *N* times matrix multiplication without using parallelism
- Measure the time it takes to execute *N* times matrix multiplication using classical parallelism with the number of threads equal to 2, 4, 8, ..., 4 * (number of logical computer processors)
- Measure the time it takes to execute *N* times matrix multiplication using pipeline parallelism
- Display the obtained time
- Use mutexes to lock access to data for parallel implementation


💡 [Tap here](https://forms.yandex.ru/u/635aa91ac769f120b3a81f17/) **to leave your feedback on the project**. Pedago Team really tries to make your educational experience better.
