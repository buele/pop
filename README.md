Partial Order Planning algorithm implementation
===========



Simple prototype of Partial
Order Planning algorithm implementation in C++11.
This simple project implements a generic Partial Order Planning algorithm. An example
of Block World solution is provided in the application. The core of application
is designed to be generic, Actions, Preconditions, Effects, Plan classes are generic.
The specific implementation in the Block world is defined in the BWname classes.
The algorithm implementation is located in the Pop class.
The project is to consider a prototype to explore and to better understand how planning algorithms work, for educational purposes. This project is the code-part of the fourth assignment of Artificial intelligence Fundamentals course[3] (University of Pisa).

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

# License
Copyright 2018 Raffaele Bua

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


# References

 [1] Stuart Russell and Peter Norvig *Artificial Intelligence: A Modern Approach.* Pearson 2016  
 [2] David Barber *Bayesian Reasoning and Machine Learning.* Cambridge University Press 2012   
  [3] [Artificial Intelligence Fundamentals](https://elearning.di.unipi.it/course/view.php?id=96)
