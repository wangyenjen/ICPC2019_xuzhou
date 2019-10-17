Polycut
============

You are given a convex polyhedron with $N$ vertices and $M$ edges. The polyhedron is somewhat ugly, thus you want to cut it into a different shape.

You've chosen $K$ planes in the 3-dimensional space. A plane will cut a polyhedron into two polyhedra. If the polyhedron lies completely on one side of the plane, we define one of the polyhedra is an empty set (which has zero volume). Thus, the $K$ planes will cut the polyhedron into $2^K$ polyhedra.

You want to know the volume of each polyhedron after cutting. However, there are too many vertices in the original polyhedron, so you need to write a program to calculate the answer.


Input
-----
The first line contains three positive integers $N, M, K$ ($N\leq M\leq 3\times 10^4, K\leq 3$) --- the number of vertices and edges in the polyhedron, and the number of planes.

Each of the next $N$ lines contains three integers $x_i, y_i, z_i$ ($-10^4\leq x_i,y_i,z_i\leq 10^4$) --- the coordinate of the $i$-th vertex. The vertices are numbered from $0$ to $N-1$.

Each of the next $M$ lines contains two integers $u,v$ ($0\leq u,v<N$), indicating that there is an edge connecting the $u$-th and the $v$-th vertex.

Each of the next $K$ lines contains four integers $a, b, c, d$ ($-10^9\leq a,b,c,d\leq 10^9$), indicating a plane with equation $ax+by+cz=d$.

Output
------
Output $2^K$ real numbers, each in a line, representing the volume of each polyhedron after cutting. **The numbers must be sorted in non-decreasing order.**

Your answer will be considered correct if the relative or absolute error does not exceed $10^{-6}$.

Sample Input 1
--------------
```
8 12 1
0 0 0
0 0 1
0 1 0
0 1 1
1 0 0
1 0 1
1 1 0
1 1 1
0 1
1 3
3 2
2 0
4 5
5 7
7 6
6 4
0 4
1 5
2 6
3 7
3 0 0 1
```

Sample Output 1
---------------
```
0.333333333
0.666666667
```

Sample Input 2
--------------
```
4 6 1
0 0 0
0 0 3
0 2 0
1 0 0
0 1
0 2
0 3
1 2
1 3
2 3
1 1 1 0
```

Sample Output 2
---------------
```
0.000000000
1.000000000
```
