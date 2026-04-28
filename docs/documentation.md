# Implementation & Testing Documentation

## Implementation Notes

The final implementation closely follows the original specification. The class interfaces, algorithms, and data structures were implemented as planned. The following minor additions were made during development:

- `Array::first()` — convenience method for accessing the first element, used in BFS to mark the root node as explored.
- `Array::clear()` — clears all elements while keeping allocated capacity, used in `Graph::load()` to reset state before loading.
- `Array(size_t, T)` — fill constructor that creates an array of a given size with a default value, used to initialize the BFS `explored` array.
- `Node()` — default constructor, required because `Array<Node<T>>` allocates a buffer with `new Node<T>[capacity]`.
- `GraphError::SelfLoopNotAllowed` — custom exception (inherits from `std::logic_error`) thrown when `addEdge()` is called with identical indices.
- `PInt` — a `Persistable` integer wrapper used by the playground and tests to satisfy the `static_assert` on `Graph<T>`.
- The interactive playground prints an ASCII diagram of the 4 node graph instead of a plain edge list.

## Testing

The project uses **gtest_lite** for unit testing. Tests are compiled with `-DMEMTRACE` to enable memory leak detection via the **memtrace** module. All tests use the `ENDM` macro which checks for memory leaks at the end of each test case.

Tests are run with `make test`.

### Test Strategy

Each class is tested in a separate file under `test/`. The tests cover:

- **Constructors and basic operations** — verify correct initialization and element access.
- **Edge cases and error handling** — out of bounds access, empty containers, self-loops, duplicate edges.
- **Deep copy** — copy constructors and assignment operators create independent copies.
- **Algorithms** — checking connectivity with different graphs.
- **Persistence** — save/load logic, state replacement, file handling errors.

### Test Cases

#### Array (15 tests)

| Test | What it verifies |
| --- | --- |
| DefaultConstructor | Empty array has size 0 |
| CustomCapacityConstructor | Custom capacity, size still 0 |
| PushBackAndAccess | Elements are stored and accessible via `operator[]` |
| PushBackBeyondCapacity | Automatic capacity doubling works correctly |
| OutOfBoundsThrows | `operator[]` throws `std::out_of_range` for invalid indices |
| EmptyArrayAccessThrows | Accessing index 0 on empty array throws |
| RemoveAtMiddle | Removing middle element shifts others down |
| RemoveAtFirst | Removing first element shifts others down |
| RemoveAtLast | Removing last element decreases size |
| RemoveAtOutOfBoundsThrows | `removeAt()` throws for invalid index |
| CopyConstructor | Copy has same size and elements |
| CopyIsDeep | Modifying copy doesn't affect original |
| AssignmentOperator | Assignment copies size and elements |
| SelfAssignment | Self-assignment doesn't corrupt data |
| AssignmentIsDeep | Modifying assigned copy doesn't affect original |

#### Node (8 tests)

| Test               | What it verifies                                |
| ------------------ | ----------------------------------------------- |
| Constructor        | Stores the given value                          |
| ConstructorString  | Works with `std::string` type                   |
| SetData            | `setData()` replaces stored value               |
| EqualityTrue       | `operator==` returns true for equal values      |
| EqualityFalse      | `operator==` returns false for different values |
| AssignmentOperator | Assignment copies data                          |
| StreamOutput       | `operator<<` outputs the value                  |
| StreamOutputString | `operator<<` works with string data             |

#### Graph (30 tests)

| Test | What it verifies |
| --- | --- |
| EmptyGraph | New graph has 0 nodes and 0 edges |
| AddNode | Nodes are stored with correct data |
| GetNodeOutOfBounds | `getNode()` throws for invalid index |
| AddEdge | Edge is symmetric, edge count increments |
| AddEdgeDuplicateIsNoop | Adding existing edge doesn't change count |
| AddEdgeSelfLoopThrows | `addEdge(i, i)` throws `SelfLoopNotAllowed` |
| AddEdgeOutOfBounds | Throws for invalid indices |
| HasEdgeNoEdge | Returns false when no edge exists |
| HasEdgeOutOfBounds | Throws for invalid indices |
| RemoveEdge | Edge removed symmetrically, count decrements |
| RemoveEdgeNonexistentIsNoop | Removing nonexistent edge is safe |
| RemoveEdgeOutOfBounds | Throws for invalid indices |
| RemoveNode | Node removed, remaining nodes shift down |
| RemoveNodeUpdatesEdgeCount | Edge count adjusted when node with edges is removed |
| RemoveNodeOutOfBounds | Throws for invalid index |
| CopyConstructor | Copy preserves nodes, edges, and connectivity |
| CopyIsDeep | Modifying copy doesn't affect original |
| AssignmentOperator | Assignment preserves full state |
| AssignmentIsDeep | Modifying assigned graph doesn't affect original |
| IsConnectedEmptyGraph | Empty graph is connected |
| IsConnectedSingleNode | Single node is connected |
| IsConnectedTwoNodesConnected | Two nodes with edge are connected |
| IsConnectedTwoNodesDisconnected | Two nodes without edge are disconnected |
| IsConnectedChain | Chain of 4 nodes is connected |
| IsConnectedDisjointComponents | Two separate components are disconnected |
| IsConnectedAfterRemoveEdge | Removing bridge edge disconnects graph |
| SaveAndLoad | Round-trip preserves nodes and edges |
| LoadReplacesExistingState | Load overwrites current graph state |
| SaveAndLoadEmptyGraph | Empty graph round-trips correctly |
| LoadInvalidFileThrows | Nonexistent file throws `std::runtime_error` |

### Memory Leak Detection

Memory leak detection is handled by the **memtrace** module, which is included in every compilation unit via the `-DMEMTRACE` compiler flag.

All 53 tests pass with no memory leaks detected:

```
==== TESZT VEGE ==== HIBAS/OSSZES: 0/53
```
