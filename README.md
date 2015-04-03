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
## Future
I'm planning to refactor this into a full fledged library to convert graphs from one format to another blazingly fast.
Refer to the [wiki](https://github.com/akshaydixi/snametize/wiki) for more details.
