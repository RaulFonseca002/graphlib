# graphlib

A small C++ graph library built for an algorithms course: a `Graph` class over
separate node and edge stores, with DFS edge classification, BFS, and Dijkstra.

The point of the exercise was the classification pass. Running DFS and labelling
every edge as a **tree**, **back**, **forward**, or **cross** edge is what turns a
traversal into something you can reason about — back edges mean cycles, cross
edges mean disconnected subtrees.

## Graph format

Graphs are read from a text file, one per line:

```
d/a,b,c,d/{0,a,b},{0,b,c},{0,c,d},{0,d,a}
│  │       └── edges as {weight, from, to}
│  └────────── node names
└───────────── `d` for directed, `nd` for undirected
```

`src/main.cpp` reads `input.txt`, builds each graph, tags its edges, and prints
the result:

```
node name: a reach set:  a
node name: b reach set:  b
...
from a to: b tree,
from b to: c tree,
from c to: d tree,
from d to: a back,
```

The `d → a` back edge is the cycle in that graph.

## API

```cpp
Graph g("d/a,b,c/{0,a,b},{0,b,c}");

g.addNode("d");
g.addEdge("c", "d", 2.5);
g.removeEdge("a", "b");

g.tagEdges();                  // DFS classification over every component
g.dfsTag("a");                 // classification from one start node
g.bfs("a", "d");               // unweighted shortest path
g.dijkstra("a", "d");          // weighted shortest path
g.print();
```

`tagEdges()` covers disconnected graphs: after the first DFS it repeatedly picks
an unreached node and restarts, so every edge in every component gets a label.

Undirected graphs are stored as edge pairs — `removeEdge` drops both directions.

## Layout

| File | Holds |
|---|---|
| `src/graph.{h,cpp}` | `Graph` — parsing, node/edge mutation, printing |
| `src/Nodes.{h,cpp}` | node store, in/out degree, reach tracking |
| `src/Edges.{h,cpp}` | edge store with weights |
| `src/path.{h,cpp}` | `dfsTag`, `bfs`, `dijkstra` |

## Building

```bash
./make.sh build   # compiles to bin/main
./make.sh run
./make.sh         # build and run
```

Requires a C++11 compiler. `bin/` must exist.

## Limitations

- Reads `input.txt` from the working directory; the path is not configurable.
- Node names are strings looked up linearly, so this is not built for large graphs.
- `src/path.h` declares free `dfs`/`bfs`/`dijkstra` functions that are unused
  leftovers — the working implementations are the `Graph` methods.
- No test suite. Correctness was checked by reading the printed classification
  against hand-worked examples.
