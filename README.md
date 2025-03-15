# cpp_dsa
Numeric C++ DSA library for computational geometry and mathematical modeling

## Setup

Find all the git precommits `hooks/pre-commit`; please copy these to `.git/hooks/pre-commit`. TODO: add this as a merge req.


## Common Data Structures and Algorithms

### Data Structures
- Linked Lists
- Stacks
- Trees: Trie & Binary Tree


## TODO

- 1. Enhance Quadtree with Eigen-Based Distance Features
- 2. What: Make LinkedList and Quadtree more flexible and interoperable.
-- Iterator Support: Add STL-style iterators to LinkedList and Quadtree.
-- Custom Allocators: Template parameter for memory allocation.
-- Traits: Add a traits class to unify point types.
- 3. Add More Spatial Data Structures
-- (K-d tree, R-tree, Octree)
- 4. Integrate with Eigen More Deeply
-- Point Type: Define a default Point using Eigen::Vector2f or VectorXf.
-- Distance Metrics: Add configurable distance functions.
-- Transformations: Support affine transforms on quadtree points.
5. Build Utility Functions
-- Serialization: Save/load LinkedList or Quadtree to/from files.
-- Visualization: Export to a format like SVG or a simple ASCII renderer.
-- Statistics: Compute stats (e.g., average point density in quadtree).

Ideas:
Image Processing: Quadtree for image compression (e.g., adaptive sampling).
Store pixel intensities, use Eigen for distance-based merging.
Point Clouds: Nearest-neighbor searches for 2D/3D data.
Integrate with PCL (Point Cloud Library) or ROS messages.
Game Dev: Collision detection with quadtree and distance checks.
LinkedList for dynamic objects, Quadtree for static.





### Possible



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
