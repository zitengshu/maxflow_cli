# Maximum Link Flow Framework

## Prerequisite

* Git
* Build-essentials packages
* cmake

## Getting started

1. Clone the repository and update the submodule.

   ```
   git clone git@github.com:zitengshu/maxflow_framework.git
   cd maxflow_framework
   git submodule init
   git submodule update
   ```

2. Build the project. We provide `configure.sh` and `build.sh` to build an executable file. After running following commands, you can find the executable file `MaxFlow` in the `build` folder

   ```
   ./configure.sh
   ./build.sh
   ```

3. Run an example. We provide an example input file `topology.json` in the `example` folder and a script `run.sh` to run the demo.

   ```
   ./run.sh
   ```

   After running the demo, you can find the result json file `flow_dist.json` in the `build` folder.

   If you wish to run your own experiment, you may want to run following commands:

   ```
   cd build
   ./MaxFlow <INPUT_FILE_PATH> <OUTPUT_FILE_NAME>
   ```

## Input File

There are 4 fields in the input file.

| Field Name   | Description                                                | Example                                                      |
| ------------ | ---------------------------------------------------------- | ------------------------------------------------------------ |
| node_num     | Number of node in the graph                                | "node_num": 6<br />It means there are 6 nodes in total including source and sink nodes. |
| source_nodes | A list of source nodes                                     | "source_nodes": [0, 1]<br />It means node0 and node1 are source nodes. |
| sink_nodes   | A list of sink nodes                                       | "sink_nodes": [4,5]<br />It means node4 and node5 are sink nodes. |
| nodes        | A map of nodes to a map of adjacent nodes to edge capacity | "nodes": { "0": { "1": 16 } }<br />It means there is an edge connect node0 and node1 with capacity 16. This is a symmetric edge which means the capacity of node0 to node1 is equal to capacity of node1 to node0. |

### To be noted

* You should not define duplicate edges in the input file. If you define a edge of 0 to 1, then you should not define another edge of 1 to 0 in the input file.

## Output File

There are 5 fields in the output file.

| Field Name   | Description                                            | Example                                                      |
| ------------ | ------------------------------------------------------ | ------------------------------------------------------------ |
| node_num     | Number of node in the graph                            | "node_num": 6<br />It means there are 6 nodes in total including source and sink nodes. |
| source_nodes | A list of source nodes                                 | "source_nodes": [0, 1]<br />It means node0 and node1 are source nodes. |
| sink_nodes   | A list of sink nodes                                   | "sink_nodes": [4,5]<br />It means node4 and node5 are sink nodes. |
| nodes        | A map of nodes to a map of adjacent nodes to edge flow | "nodes": { "0": { "1": 16 } }<br />It means the flow of node0 and node1 is 16. Since this is a symmetric edge, you will find the flow of node1 to node0 is the negative number of the flow of node0 and node1. In the above case, flow of node1 to node0 is -16. |
| max_flow     | The maximum flow of the graph                          | "max_flow": 35<br />It means the maximum flow of the graph is 35 |

### To be noted

* Edges in the output file will not be deduplicated. If there is a edge of 0 to 1, then it will have a edge of 1 to 0 in the output file.
* The output file will be generated in the same folder of binary executable file `MaxFlow`.