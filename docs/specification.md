# Specification

## Overview

The project implements a generic undirected graph in C++11. The graph uses an adjacency matrix for storage, with nodes represented by a dedicated class. Tests are written in a separate module. The graph can be experimented with using a simple interactive program.

## Graph Storage

The graph nodes are stored in a dynamic array, the edges are represented by an adjacency matrix.

- The matrix is a dynamically allocated bool matrix of size nxn (n is the current number of nodes)
  - The matrix is symmetric, `matrix[i][j] == matrix[j][i]` because the graph is undirected
- Nodes are stored in a dynamically allocated array of node objects
- Both the matrix and the array are reallocated when the number of nodes change (with capacity)
- The matrix can be persisted into a file

## Classes

### Array

Used inside `Graph<T>` as `Array<Node<T>>` for the node list and as `Array<Array<bool>>` for the matrix row pointers.

#### Members and Methods

- `data: T*`: heap-allocated buffer
- `size: size_t`: current number of elements
- `capacity: size_t`: Allocated capacity of the buffer
- `Array(size_t) -> Array`: constructor, takes initial capacity (default 10, minimum 1)
- `Array(size_t, T) -> Array`: constructor, creates array of given size filled with default value
- `Array(const Array&) -> Array`: copy constructor
- `operator= -> Array&`: Deep copy assignment
- `~Array()`: destructor
- `pushBack(const T&)`: append element, double capacity if needed
- `removeAt(size_t)`: removes element at index and shifts other elements down
- `operator[](size_t) -> T&`: Element access, throws error if out of bounds
- `first() -> T&`: returns reference to the first element, throws error if empty
- `getSize() -> size_t`: returns the current number of elements
- `clear()`: removes all elements, resets size to 0, keeps capacity

### Node

Wraps a single piece of data of type `T`.

#### Members and Methods

- `data: T`: the value stored by the node
- `Node()`: default constructor
- `Node(const T&)`: constructor
- `getData() -> const T&`
- `setData(const T&)`
- `operator=(const Node&)`: deep copy assignment
- `operator==(const Node<T>&)`: equality comparison
- `operator<<(ostream&, const Node<T>&)`: prints to ostream

### Graph

Owns a dynamic node array and the associated adjacency matrix. `T` must derive from `Persistable`, enforced by a `static_assert` at compile time.

> **Note:** the graph doesn't allow loops. This means values across the main diagonal are all 0.

#### Members and Methods

- `nodes: Array<Node<T>>`: dynamic array of all nodes
- `matrix: Array<Array<bool>>`: nxn adjacency matrix (heap-allocated)
- `edgeCount: size_t`: current number of edges
- `Graph()`: constructor
- `Graph(const Graph&)`: copy constructor
- `operator=(const Graph&)`: deep copy assignment
- `addNode(const T&)`: add node, reallocates if needed
- `removeNode(size_t):` remove node at index, uses the `Array::removeAt()` method, and removes the row and column from the matrix. Throws error if out of bounds.
- `addEdge(size_t, size_t)`: connects nodes `i` and `j`, no-op if edge already exists. Throws `std::out_of_range` if out of bounds, or `GraphError::SelfLoopNotAllowed` if `i == j` (loop).
- `removeEdge(size_t, size_t)`: no-op if edge does not exist. Throws errors if out of bounds.
- `hasEdge(size_t, size_t) -> bool`: error if out of bounds
- `getNodeCount() -> size_t`: returns `nodes.getSize()`
- `getEdgeCount() -> size_t`: returns `edgeCount` directly
- `isConnected() -> bool`: runs BFS from first node, returns true if all nodes visited
- `getNode(size_t) -> Node<T>&`: error if out of bounds
- `print(ostream&)`: prints node list and adjacency matrix
- `operator<<(ostream&, const Graph<T>&)`: friend function, calls `print()`
- `save(const std::string&)`: saves the graph to a file at the given path
- `load(const std::string&)`: loads a graph from a file at the given path, replaces current state

### Queue

A simple heap-allocated FIFO queue, using a circular buffer. Declared as a private nested struct inside `Graph<T>`. Used exclusively by the BFS algorithm. Because of this the queue is minimal, tailored for the graph's needs:

- The queue stores the node indices, not the nodes themselves
- The queue is fixed size, as the maximum number of elements is the node count
- We allocate `nodeCount + 1` slots to avoid ambiguity. If we only allocated `nodeCount` slots `head` would equal `tail` when the queue is empty, but also when the queue is full, because of the circular buffer. By adding an extra sentinel slot this never happens.

#### Members and Methods

- `data: size_t*`: fixed array of size `nodeCount + 1`
- `head: size_t`: front index
- `tail: size_t`: back index
- `capacity: size_t`: total buffer size (`nodeCount + 1`)
- `Queue(size_t)`: allocates `n + 1` slots
- `~Queue()`: destructor
- `enqueue(size_t)`: adds index, moves `tail` forward with wrapping
- `dequeue() -> size_t`: returns index, moves `head` forward with wrapping
- `isEmpty() -> bool`

## UML Diagram

![](./uml-diagram/uml-diagram.png)

## Key Algorithms

### addNode - Row Expansion

- When a new node is added, the adjacency matrix grows from nxn to (n+1)x(n+1).
- The `Array<Node<T>>` handles node storage automatically via `pushBack()`.
- Both the rows and the columns of the adjacency matrix utilize the `Array` class, so they can be easily expanded with `pushBack()` as well.

### isConnected - Breadth-First Search

Returns true if every node is reachable from the first node via a [Breadth-First Search](https://en.wikipedia.org/wiki/Breadth-first_search). An empty graph (0 nodes), and a single isolated node (1 node) is considered connected.

### getEdgeCount

Instead of calculating the edge count from the upper triangle matrix, we can just keep track of edges added by `addEdge()` and `removeEdge()`. This makes this an `O(1)` operation.

## Persistence

The matrix can be saved to a text file. The problem is because the graph is generic we need a way to represent the objects as text. To do this `Graph<T>` only accepts types that derive from a `Persistable` abstract class.

```cpp
class Persistable {
public:
    virtual std::string encode() const = 0;
    virtual ~Persistable() {}
};
```

Nodes are serialized by the `encode()` method. For deserialization in `Graph<T>` `T` must implement a **constructor** that takes `const std::string&` as a parameter. It must construct the object from the string saved by `encode()`.

Data is saved in the following format:

```
CPPGraph vX.x
<node count>
<edge count>
<node 1>
<node 2>
...
<node n>
0 1 ... 0
...
1 0 ... 1
```

- First line contains the save file version
- Then we have the node and edge count
- Then comes the nodes
- Then the adjacency matrix

## Interactive Mode

The interactive mode is a console-like interface for experimenting with the graph. A `Graph<PInt>` with 4 nodes (0–3) is preloaded. Edges are visualized as an ASCII diagram with the nodes arranged in a square. The save file is automatically cleaned up when the session ends.

### Available Commands

- `help`: prints available commands
- `print`: prints the graph as an ASCII diagram
- `connect {u} {v}`: adds an edge between nodes `u` and `v`
- `disconnect {u} {v}`: removes edge between nodes `u` and `v`
- `connected`: checks if the graph is connected
- `save`: saves the current graph state to a temporary file
- `load`: loads previously saved graph state
- `exit`: exits interactive mode

### Example Usage

```
CPPGraph Interactive mode
Type 'help' for available commands
> print
0   1



2   3
> connected
false
> connect 0 1
> connect 1 2
> connect 1 3
> print
0---1
   /|
  / |
 /  |
2   3
> connected
true
> save
> disconnect 1 2
> connected
false
> load
> connected
true
> exit
```

## Testing

The project uses **gtest_lite**, which is preinstalled on **JPorta** and requires no external configuration. It supports batch/command-line testing, is fully redirectable to a file, and integrates cleanly with **memtrace**. I will test the most important methods of each class.
