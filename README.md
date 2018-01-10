Partial Order Planning algorithm implementation
===========



Simple prototype of Partial
Order Planning algorithm implementation in C++11.
This simple project implements a generic Partial Order Planning algorithm. An example
of Block World solution is provided in the application. The core of application
is designed to be generic, Actions, Preconditions, Effects, Plan classes are generic.
The specific implementation in the Block world is defined in the BWname classes.
The algorithm implementation is located in the Pop class.

# Requirements
- OS: MacOS
- g++: 4.2.1
-  make: 3.81


# How to build
```
cd pop
make
```

# How to run

```
cd pop
cd dist/Debug/GNU-MacOSX
./pop
```
# Class diagram

# Sequence diagram

# Planning algorithm

# Known bugs
- To fix the threats resolution because is not stable
- To add the possibility to load a new problem via file
- To fix some memory leaks


# References

 [1] Stuart Russell and Peter Norvig *Artificial Intelligence: A Modern Approach.* Pearson 2016  
 [2] David Barber *Bayesian Reasoning and Machine Learning.* Cambridge University Press 2012
