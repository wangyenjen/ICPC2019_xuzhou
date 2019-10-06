Factory
============

The original problem can be formulated as a linear programming problem:

$\begin{align}
\text{Minimize }\ &T\\
\text{s.t.}\ &x_{ij}\geq 0&\forall i,j\\
&\sum_i x_{ij}=T&\forall j\\
&\sum_j \frac{x_{ij}}{t_{ij}}=1&\forall i
\end{align}$

One can solve the dual problem instead:

$\begin{align}
\text{Maximize }\ &\sum_i y_i\\
\text{s.t.}\ &y_i\leq z_jt_{ij}&\forall i,j\\
&\sum_j z_j\leq 1&\forall i
\end{align}$

Since $t_{ij}$'s are positive, the maximum points must have $\sum_j z_j=1$. Moreover, $y_i$ is only bounded by $z_jt_{ij}$'s, so $y_i=\min_j{z_jt_{ij}}$:

$\begin{align}
\text{Maximize }\ &\sum_i \min_j{z_jt_{ij}}\\
\text{s.t.}\ &\sum_j z_j= 1&\forall i
\end{align}$

One can substitute $z_{K-1}$ by $1-\sum_{j=0}^{K-2}z_j$. Note that $\min_j{z_jt_{ij}}$ is convex, so this is a unconstrained convex optimization problem with $K-1$ variables. Since the error tolerance is as large as $10^{-2}$ (in fact, $2\times 10^{-2}$ since one can multiply its answer by $1+10^{-2}$), one can use some gradient-based iterative optimization technique such as stochastic subgradient method.

There are a few implementation issues. First, since the variance of gradient would be very large (due to the summation and the $\left(1-\sum_{j=0}^{K-2} z_j\right)t_{i,K-1}$ term), one may need to normalize the gradient. Second, to get a tolerable result, one may need decrease the step size when iterating.
