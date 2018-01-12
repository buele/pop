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
![Class diagram](https://raw.githubusercontent.com/buele/pop/master/docs/class-diagram.png)


# Output example
```
*** Artificial Intelligence Fundamentals - UNIPI 2017/2018 ***
Partial Order Planning - 4th assignment

Example of Block World
- start computation
Implement/run Partial order planning algorithms 3
[POP Algorithm] - ALGORITHM STEP ----
[POP Algorithm] - get an open precondition
ON(AB)
[POP Algorithm] - the action of open precondition is :
FINISH()
[POP Algorithm] - Look for an action that solves the precondition
explore actions
for action with name: STACK
explore effects
COMPARE PRECONDITION : ON(A,B)
WITH effect: !CLEAR(y)
COMPARE PRECONDITION : ON(A,B)
WITH effect: !TABLE(x)
COMPARE PRECONDITION : ON(A,B)
WITH effect: ON(x,y)
ON(A,B)
the action: STACK(A,B)  solves the open precondition ON(A,B)
PRECONDITION WITH SAME PARAMETERS CASE
Mapping
map[x] :A
map[y] :B
[POP Algorithm] - Found an action
STACK(A,B)
STACK(A,B)
[POP Algorithm] - Update edges
get the link: START --> FINISH
if FINISH() is equal to FINISH()
[POP Algorithm] - found an edge with the action of open precondition
START() --> FINISH()
!! change destination for this edge:
START() --> STACK(A,B)
[POP Algorithm] - Create new edge, locating the new action between the old one
STACK(A,B) --> FINISH()
[POP Algorithm] - Resolve Threats
---STEP PLAN----
PRINT PLAN:
START() -> STACK(A,B) -> FINISH()
START() -> FINISH()
FINISH()
-----------------
---STEP LINKS----
START() --> STACK(A,B)
START() --> FINISH()
STACK(A,B) --> FINISH()
-----------------
--- STEP OPEN PRECONDITIONS----
ON(BC)(FINISH()) CLEAR(A)(STACK(A,B))
-----------------
[POP Algorithm] - ALGORITHM STEP ----
[POP Algorithm] - get an open precondition
ON(BC)
[POP Algorithm] - the action of open precondition is :
FINISH()
[POP Algorithm] - Look for an action that solves the precondition
explore actions
for action with name: STACK
explore effects
COMPARE PRECONDITION : ON(B,C)
WITH effect: !CLEAR(y)
COMPARE PRECONDITION : ON(B,C)
WITH effect: !TABLE(x)
COMPARE PRECONDITION : ON(B,C)
WITH effect: ON(x,y)
ON(B,C)
the action: STACK(B,C)  solves the open precondition ON(B,C)
PRECONDITION WITH SAME PARAMETERS CASE
Mapping
map[x] :B
map[y] :C
[POP Algorithm] - Found an action
STACK(B,C)
STACK(B,C)
[POP Algorithm] - Update edges
get the link: START --> STACK
if STACK(A,B) is equal to FINISH()
get the link: START --> FINISH
if FINISH() is equal to FINISH()
[POP Algorithm] - found an edge with the action of open precondition
START() --> FINISH()
!! change destination for this edge:
START() --> STACK(B,C)
[POP Algorithm] - Create new edge, locating the new action between the old one
STACK(B,C) --> FINISH()
[POP Algorithm] - Resolve Threats
Implement/run Partial order planning algorithms 5
---STEP PLAN----
PRINT PLAN:
START() -> STACK(A,B) -> FINISH()
START() -> STACK(B,C) -> FINISH()
FINISH()
-----------------
---STEP LINKS----
START() --> STACK(A,B)
START() --> STACK(B,C)
STACK(A,B) --> FINISH()
STACK(B,C) --> FINISH()
-----------------
--- STEP OPEN PRECONDITIONS----
CLEAR(A)(STACK(A,B))
-----------------
[POP Algorithm] - ALGORITHM STEP ----
[POP Algorithm] - get an open precondition
CLEAR(A)
[POP Algorithm] - the action of open precondition is :
STACK(A,B)
[POP Algorithm] - Look for an action that solves the precondition
explore actions
for action with name: STACK
explore effects
COMPARE PRECONDITION : CLEAR(A)
WITH effect: !CLEAR(y)
COMPARE PRECONDITION : CLEAR(A)
WITH effect: !TABLE(x)
COMPARE PRECONDITION : CLEAR(A)
WITH effect: ON(x,y)
for action with name: UNSTACK
explore effects
COMPARE PRECONDITION : CLEAR(A)
WITH effect: CLEAR(y)
CLEAR(A)
the action: UNSTACK(A)  solves the open precondition CLEAR(A)
print map
map[x]: C
map[y]: A
PRECONDITION WITH DIFFERENT PARAMETERS CASE
[POP Algorithm] - Found an action
UNSTACK(C,A)
UNSTACK(C,A)
[POP Algorithm] - Update edges
get the link: START --> STACK
if STACK(A,B) is equal to STACK(A,B)
[POP Algorithm] - found an edge with the action of open precondition
START() --> STACK(A,B)
!! change destination for this edge:
START() --> UNSTACK(C,A)
[POP Algorithm] - Create new edge, locating the new action between the old one
UNSTACK(C,A) --> STACK(A,B)
[POP Algorithm] - Resolve Threats
---STEP PLAN----
PRINT PLAN:
START() -> UNSTACK(C,A) -> STACK(A,B) -> FINISH()
START() -> STACK(B,C) -> FINISH()
FINISH()
-----------------
---STEP LINKS----
START() --> UNSTACK(C,A)
START() --> STACK(B,C)
STACK(A,B) --> FINISH()
STACK(B,C) --> FINISH()
UNSTACK(C,A) --> STACK(A,B)
-----------------
--- STEP OPEN PRECONDITIONS----
-----------------
[POP Algorithm] - Computation Finished
PRINT PLAN:
START() -> UNSTACK(C,A) -> STACK(A,B) -> FINISH()
START() -> STACK(B,C) -> FINISH()
FINISH()
[DONE]
```


# Known bugs
- To fix the threats resolution because is not stable
- To add the possibility to load a new problem via file
- To fix some memory leaks

# License
Copyright © 2018 Raffaele Bua

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


# References

 [1] Stuart Russell and Peter Norvig *Artificial Intelligence: A Modern Approach.* Pearson 2016  
 [2] David Barber *Bayesian Reasoning and Machine Learning.* Cambridge University Press 2012   
  [3] [Artificial Intelligence Fundamentals](https://elearning.di.unipi.it/course/view.php?id=96)
