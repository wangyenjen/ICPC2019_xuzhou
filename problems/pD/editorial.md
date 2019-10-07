Polycut
============

One can use any data structure for polyhedra to implement the cutting procedure.

A common data structure is splitting each edge into two edges, each in one direction, which belong to different faces. For each splitted edge, store the next edge in the same face, and the other edge representing the same edge. One can also triangulate the polyhedron to simplify the implementation.

To convert the input polyhedron into the data structure, one need to sort the edges connected to a vertex. This can be implemented by projecting all edges along an edge onto a plane, and sort the edges by angle.

The volume of a polyhedron is given by $\frac{1}{6}\left|\sum_\textbf{a} \textbf{a}_1\cdot (\textbf{a}_2\times \textbf{a}_3)\right|$, where $\textbf{a}$ is the set of all faces in the triangulated polyhedron.
