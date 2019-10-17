Multiply
============

Alduhmellah and Behlah both like large numbers, lots of numbers and lots of large numbers. They also like to do calculations on those numbers.

One day, Alduhmellah wrote down $N$ positive integers $a_1, a_2,\cdots, a_N$. He decided to make them large by applying factorial to each number, so the numbers became $a_1!, a_2!,\cdots, a_N!$. Finally, he multiplied all $N$ numbers to get a super-large number $Z=a_1!\times a_2!\times\cdots\times a_N!$.

A few days later, Behlah met Alduhmellah, and Behlah told Alduhmellah that he came up with another two numbers $X,Y$. Thus, they started to repeatedly multiply $X$ to $Z$, generating a sequence $b_i=Z\times X^i$, to find out the largest value of $i$ such that $b_i$ is a factor of $Y!$.

You, being a friend with Alduhmellah and Behlah, realized that it is such a time-wasting process. Thus, to save time, you decided to write a program to calculate the answer.

Input
-----
The first line contains one positive integer $T$ ($T\leq 8$) --- the number of tests.

The description of each test contains two lines: the first line contains three positive integers $N, X, Y$ ($N\leq 10^5; 2\leq X,Y\leq 10^{18}$), and the second line contains $N$ positive integers $a_1, a_2,\cdots a_N$ ($a_i \leq 10^{18}; a_1+a_2+\cdots+a_N<Y$). Their meanings are explained above.

Output
------
For each test, output an integer in one line, representing the largest value of $i$ such that $b_i$ is a factor of $Y!$.

Sample Input
--------------
```
2
3 10 10
2 3 4
2 2 10
1 1
```

Sample Output
---------------
```
2
8
```
