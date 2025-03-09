# cpp_dsa
Data Structures and Algorithms in cpp

## Setup

Find all the git precommits `hooks/pre-commit`; please copy these to `.git/hooks/pre-commit`


## Common Data Structures and Algorithms

### Data Structures
- Linked Lists
- Stacks
- Trees: Trie & Binary Tree


## TODO

- expand to geometry-flavored data structures (quadtree)
- Refactor one old structure (e.g., Stack) with std::unique_ptr.
- Explore Eigen—compute distances in Quadtree.



### Possible
- Refactor one existing structure (e.g., LinkedList) to use std::unique_ptr and <vector>
- stdlibs to learn:
-- <vector>, <array>, <list>
-- <memory>:
-- <algorithm>:
-- <optional>:
-- <numeric>:



Rule of Zero: Let destructors default where possible (e.g., SortedBinaryTree—no need to redefine ~SortedBinaryTree).
Const: Mark methods const (e.g., getData() const).
Avoid Raw Loops: Use <algorithm> (e.g., replace for with std::find_if).
Interfaces: Define abstract base classes (e.g., Tree with virtual insert—BinaryTree could inherit).


Image Processing:
Next Structure: 2D Grid or Matrix (use std::vector<std::vector<int>>).

ROS Point Clouds:
Next: Point Cloud class (wrap std::vector<Point3D>).
Library: PCL (Point Cloud Library)—Bazel integration later.
Task: Parse a simple .pcd file—mimic ROS sensor_msgs::PointCloud2.

Computational Geometry:
Next: Convex Hull (e.g., Graham Scan—use <algorithm>).
Library: Eigen (linear algebra)
