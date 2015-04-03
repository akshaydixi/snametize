# snametize
Convert a graph from an ASCIIGraph format to SNAP, GML and METIS formats 

## Dependencies
- Boost.Program_options

###Usage

- `mkdir build && cd build && cmake ..`
- `make`
- If it builds successfully, convert your graph file as follows
```bash
 ./snametize --input /path/to/mygraphfile --output /path/to/outputfile --format <SNAP|GML|METIS>
```

###TODOs

- [ ] Write simple tests
- [ ] Add more graph formats
- [ ] Currently, it runs only using a single core. Look into improving performance by utilizing more cores(maybe during the writing phase)
- [ ] Add property support for GML graphs
