# graphlib

A small C++ graph library built for an algorithms course. It parses graphs from a
text format, classifies every edge with a DFS, and finds paths with BFS and
Dijkstra.

The classification pass is the part the exercise was really about. Running a DFS
and labelling each edge as **tree**, **back**, **forward**, or **cross** turns a
traversal into something you can reason about: a back edge means the graph has a
cycle, a cross edge means you reached a vertex in a subtree you had already
finished.

## How it fits together

`Graph` owns two stores. `Nodes` holds the vertices, each with a name, an index,
in and out degree, and a flag for whether the traversal has reached it. `Edges`
holds the connections, each with a source, a target, a weight, and the tag the
classification pass writes into it.

`Graph::set` takes one line of the text format and fills both stores. It reads
the direction flag first, then registers the node names, then walks the edge list
and calls `addEdge` for each entry. For an undirected graph it inserts the
reverse edge too, which is why `removeEdge` drops both directions.

`tagEdges` runs the classification. It calls `dfsTag` from every node in turn,
and each call marks the nodes it reaches and tags the edges it crosses. When the
first sweep finishes it asks `Nodes` for the vertices nothing reached and
restarts from one of those, repeating until the unreached set is empty. That way
a disconnected graph still gets every edge in every component labelled.

`bfs` and `dijkstra` both work over the same stores. `bfs` walks outward level by
level and ignores weights. `dijkstra` keeps a running distance per node, relaxes
each edge against it, and returns the cheapest path once the target settles.

## Graph format

One graph per line:

```
d/a,b,c,d/{0,a,b},{0,b,c},{0,c,d},{0,d,a}
│  │       └── edges as {weight, from, to}
│  └────────── node names
└───────────── `d` for directed, `nd` for undirected
```

`src/main.cpp` reads `input.txt`, builds each graph on the line, tags its edges,
and prints the result:

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

g.tagEdges();                  // classify every edge, all components
g.dfsTag("a");                 // classify from one start node
g.bfs("a", "d");               // unweighted shortest path
g.dijkstra("a", "d");          // weighted shortest path
g.print();
```

## Layout

| File | Holds |
|---|---|
| `src/graph.{h,cpp}` | `Graph`: parsing, node and edge mutation, printing |
| `src/Nodes.{h,cpp}` | node store, in/out degree, reach tracking |
| `src/Edges.{h,cpp}` | edge store with weights and tags |
| `src/path.{h,cpp}` | `dfsTag`, `bfs`, `dijkstra` |

## Building

```bash
./make.sh build   # compiles to bin/main
./make.sh run
./make.sh         # build and run
```

Needs a C++11 compiler, and `bin/` has to exist.

## Limitations

- `main` reads `input.txt` from the working directory. The path is not
  configurable.
- Node lookup is linear over the name list, so this is not built for large
  graphs.
- `src/path.h` still declares free `dfs`, `bfs`, and `dijkstra` functions left
  over from an earlier shape. The working implementations are the `Graph`
  methods; the free `dfs` has an empty body.
- No test suite. Correctness was checked by reading the printed classification
  against hand-worked examples.
