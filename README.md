# CPPGraph

Generic, undirected graph in C++11. Adjacency-matrix backed, with persistable nodes that can be saved to and loaded from disk.

📖 **Documentation:** <https://milanvarady.github.io/CPPGraph/>

## Usage

Node types must derive from `Persistable`. A `PInt` wrapper around `int` is included.

```cpp
#include "graph.h"
#include "pint.h"

Graph<PInt> g;
g.addNode(PInt(1));
g.addNode(PInt(2));
g.addNode(PInt(3));

g.addEdge(0, 1);
g.addEdge(1, 2);

g.isConnected(); // true
g.save("graph.txt");
```

## Build Options

### Build Project

```
make
```

### Run Tests

```
make test
```

### Run Interactive Playground

```
make play
```

### Clean

```
make clean
```

## Create Specification PDF

1. Install `pandoc` and `typst`
2. `cd docs`

```zsh
pandoc specification.md \
  --from=markdown \
  --to=typst \
  --pdf-engine=typst \
  --include-in-header=./pandoc/template.typ \
  --output=specification.pdf
```

> [!TIP]
> Optional: Install fonts
> 1. Vollkorn
> 2. Lato
> 3. FiraCode Nerd Font Mono
