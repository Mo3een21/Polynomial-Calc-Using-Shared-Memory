# Polynomial-Calc-Using-Shared-Memory
This is a code that does basic polynomial operations (addition, subtraction, multiplication) using shared memory.
Polynomial Calculator
Authored by Abu Katish Moeen

==Description==
This project has 2 tasks.The first task is to do a polynomial calculator by any means necessary. It included 3 operations: multiplication, subtraction and addition.
The second task is to do the polynomial calculator but by using the shared memory and semaphores.
The first part contained the creation of the shared memory and getting the input from the user. The second part is getting the input from the shared memory and perfroming the operationss there.


Functions:
The extra functions for tasks 1 and 2 are the same, which are:

--check operation: a function that takes in a string as a parameter and check what is the operation that should be done by returning an enum.

--sendToOperatoin: it is a functtion that takes in 2 strings and an enum as parameters and sends them to their specified operation method using a switch case.

--getNum: turns numbers that are characters into integer numbers.

--addition: does the addition operation and prints the resultant polynomial.

--subtraction: does the subtraction operation and prints the resultant polynomial.

--multiplication: does the multiplication operation and prints the resultant polynomial.

==Program Files==
Ex3q1.c -- first task
Ex3q2a.c -- second task a(write)
Ex3q2b.c -- second task b(read)




==How to compile?==
(on 2 seperate terminals)
compile: gcc Ex3q2a.c -o Ex3q2a
run: ./a.out

compile: gcc Ex3q2b.c -o Ex3q2b
run: ./a.out

==Input:==(On the first terminal)
(2:3,2,1)MUL(3:2,4,0,-1)

(on the second terminal)
==Output==
6x^5  + 16x^4  + 10x^3  + 1x^2 - 2x^1 - 1



