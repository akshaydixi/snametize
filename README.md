# snametize
Convert a graph from an ASCIIGraph format to SNAP and METIS formats 

###Usage

- First, generate the binary using `make`
- Convert your graph file as follows
```bash
 ./snametize mygraphfile.txt outputfile.txt --snap
```

###TODOs

- [ ] Write simple tests
- [ ] Add more graph formats
- [ ] Currently, it runs only using a single core. Look into improving performance by utilizing more cores(maybe during the writing phase)