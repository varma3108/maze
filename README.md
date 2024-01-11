# maze
maze
# Maze Solver

This project is a maze solver implemented in C++. It uses a Breadth-First Search (BFS) algorithm to find the shortest path from the start to the goal in a maze.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

You need to have g++ installed on your machine to compile and run the program.

### Compiling

To compile the program, navigate to the directory containing the `mazefinal.cpp` file in the terminal and run the following command:

```bash
        g++ -std=c++11 -g mazefinal.cpp -o mazefinal

To run the program, use the following command:
        /mazefinal

This will execute the program and display its output.

The program has been tested against all the test cases and gives the expected output for inputs.
Apollo Diana Maze Report
1) The problem input is modeled as a directed graph where each cell in the maze is a vertex. The edges are determined by the direction and color of each cell. The direction determines which cells (vertices) are reachable from the current cell (vertex) and the color determines if a cell can be visited or not.
The graph is constructed by reading the maze from an input file. Each cell in the maze is represented as a node in the graph and stored in an adjacency matrix. The adjacency matrix is a 2D array where each element is a node that contains information about the color of the cell, the direction it points to, whether it has been visited or not, and the parent node from which it was reached.
The BFS function then traverses this graph, starting from the top left cell (0,0), and following the directions and colors of the cells to find a path to the destination cell. The path is stored as a sequence of parent nodes, which can be followed from the destination back to the source to find the shortest path.
2) The algorithm used to solve the problem is Breadth-First Search (BFS). Here is the pseudocode for the algorithm:
U11309664 Sri Indukuri
1. Initialize an empty queue and add the starting node (top left cell of the maze) to the queue.
2. While the queue is not empty:
1. Dequeue a node from the queue.
2. If the dequeued node is the destination node (color 'O'), stop the BFS
and store the row and column of the destination node.
3. Otherwise, for the dequeued node, check its direction and add all the nodes in that direction to the queue, if they have not been visited and
their color is not the same as the dequeued node.
4. Mark the dequeued node as visited and store the parent node from
which it was reached.
3. After the BFS is done, start from the destination node and follow the parent
nodes to find the path to the source node. This path is the sequence of moves
Apollo must take to reach the goal.
4. Print the path.
The complexity of the BFS algorithm is O(V+E) so it will the minimum complexity of the algo, where V is the number of vertices (cells in the maze) and E is the number of edges (connections between cells). This is the minimum possible

complexity for this problem, as every cell in the maze must be visited at least once to ensure that the shortest path is found.
