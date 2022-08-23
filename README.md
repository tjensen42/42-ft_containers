# 42-ft_containers

## Resources

1. https://cplusplus.com/reference/stl/
2. https://github.com/gcc-mirror/gcc/tree/master/libstdc%2B%2B-v3/include/bits
3. https://github.com/llvm-mirror/libcxx/tree/master/include

- https://en.cppreference.com/w/cpp/types/enable_if
- https://eli.thegreenplace.net/2014/sfinae-and-enable_if/


## Red–black tree
* https://edutechlearners.com/download/Introduction_to_algorithms-3rd%20Edition.pdf
* https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
* https://www.youtube.com/watch?v=qvZGUFHWChY&list=PLwyTr3n29dXRDviK2r4fcF_9lr8pL1tlr
* specific type of balanced binary search trees

**Rules:**
* a node is either red or black
* root and leaves (NIL) are black
* if a node is red, its children are black
* all paths from a node to its NIL descendants contain the same number of black nodes

- longest path is no more than twice the length of the shortest path
    - shortest: all black nodes
    - longest: alternating red and black

**Operations:**
- all operations have a time complexity of O(log n)
* Search
* Insert, require rotation
* Remove, require rotation
