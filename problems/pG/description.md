Factory
============

You own a special beverage factory producing $N$ kinds of beverages.

There are $K$ machines in your factory, and each machine can produce all $N$ kinds of beverages. All $K$ machines can work in parallel. One machine can only produce one kind of beverage at a time, but machines can switch from producing a kind of beverage to another immediately.

Each machine has different production abilities. Specifically, it takes $r\times t_{ij}$ minutes for the $j$-th machine to produce $r$ liters of the $i$-th beverage. Beverages are produced continuously, so the value of $r$ can be any real number.

Today, you got an order requesting 1 liter of each of all $N$ kinds of beverages. You want to finish the production as soon as possible. Thus, please write a program to calculate the minimum possible time to finish the production.


Input
-----
The first line contains two positive integers $N, K$ ($N\leq 2\times 10^4, K\leq 50$) --- the number of beverages and machines.

The next $N$ lines contain $K$ integers each. The $j$-th number of the $i$-th line contains the number $t_{ij}$ ($1\leq t_{ij}\leq 50$).

Output
------
Output one real number in a line, representing the minimum time to produce 1 liter of each of all $K$ kinds of beverages.

Your answer will be considered correct if the relative error does not exceed $10^{-2}$.

Sample Input 1
--------------
```
3 3
1 2 3
2 1 3
6 6 3
```

Sample Output 1
---------------
```
2.000000
```

Sample Input 2
--------------
```
5 2
1 7
3 9
4 10
5 11
6 12
```

Sample Output 2
---------------
```
12.687500
```
