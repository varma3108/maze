#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <fstream>  
#include <sstream>

using namespace std;

class mazesolver
{
public:
	mazesolver(); //Default constructor
	~mazesolver(); //Default descrtuctor
    void AddNodeToQueue(int i, int j, int NodeRow, int NodeColumn, char NodeColor);//add note to queue 
	void AddNodesToQueue(); //Adds all the neighbors of the current node in the BFS search
	void CreateMatrix(int r, int c); //Creates the adjacency matrix for the graph
	void BFS(); //Performs the BFS on the graph
	void PrintGraph(); //Prints the graph for testing input from file
	void PrintPath(ofstream& outFile); //Prints the shortest path found by BFS
	void SetGraph(string data); //Takes the data from the file and stores it on the matrix
private:
	struct Node //Holds the info for each node for when we perform our BFS
	{
		char color;
		string direction;
		int visited;
		pair <int, int> parentNode;
	};
    int destRow, destColumn; // we use these cols if the destROW and destCOl are other than bottom right
	int row, column;// Row and Col indicators one to indicate the order of the matric and r and c to indicate row and col in adj matrix
	int r, c;
	Node** adjMartix;
	queue<pair <int, int> > queueNode; //Queue for BFS
	vector <pair <string, int> > pathToEnd; //Holds the shortest path to the goal
};

//Constructor
mazesolver::mazesolver() : row(0), column(0), r(-1), c(-1)
{
}


mazesolver::~mazesolver()
{
    for (int i = 0; i < row; i++)
    {
        delete[] adjMartix[i];
    }
    delete[] adjMartix;
}

//Function that adds a node to the queue
void mazesolver::AddNodeToQueue(int i, int j, int NodeRow, int NodeColumn, char NodeColor) {
    if (adjMartix[i][j].color != NodeColor && adjMartix[i][j].visited == 0) {
        queueNode.push(make_pair(i, j));
        adjMartix[i][j].visited = 1;
        adjMartix[i][j].parentNode = make_pair(NodeRow, NodeColumn);
    }
}

//checks the node direction and iterates through the directions accordingly, while adding nodes to the queue.
void mazesolver::AddNodesToQueue() {
    char NodeColor = adjMartix[queueNode.front().first][queueNode.front().second].color;
    int NodeColumn = queueNode.front().second;
    int NodeRow = queueNode.front().first;
    string NodeDirection = adjMartix[queueNode.front().first][queueNode.front().second].direction;

    if (NodeDirection == "N") {
        for (int i = NodeRow; i >= 0; i--) {
            AddNodeToQueue(i, NodeColumn, NodeRow, NodeColumn, NodeColor);
        }
    } else if (NodeDirection == "NE") {
        for (int i = NodeRow, j = NodeColumn; i >= 0 && j < column; i--, j++) {
            AddNodeToQueue(i, j, NodeRow, NodeColumn, NodeColor);
        }
    } else if (NodeDirection == "E") {
        for (int i = NodeColumn; i < column; i++) {
            AddNodeToQueue(NodeRow, i, NodeRow, NodeColumn, NodeColor);
        }
    } else if (NodeDirection == "SE") {
        for (int i = NodeRow, j = NodeColumn; i < row && j < column; i++, j++) {
            AddNodeToQueue(i, j, NodeRow, NodeColumn, NodeColor);
        }
    } else if (NodeDirection == "S") {
        for (int i = NodeRow; i < row; i++) {
            AddNodeToQueue(i, NodeColumn, NodeRow, NodeColumn, NodeColor);
        }
    } else if (NodeDirection == "SW") {
        for (int i = NodeRow, j = NodeColumn; i < row && j >= 0; i++, j--) {
            AddNodeToQueue(i, j, NodeRow, NodeColumn, NodeColor);
        }
    } else if (NodeDirection == "W") {
        for (int i = NodeColumn; i >= 0; i--) {
            AddNodeToQueue(NodeRow, i, NodeRow, NodeColumn, NodeColor);
        }
    } else if(NodeDirection == "NW") {
        for (int i = NodeRow, j = NodeColumn; i >= 0 && j >= 0; i--, j--) {
            AddNodeToQueue(i, j, NodeRow, NodeColumn, NodeColor);
        }
    }
}


void mazesolver::CreateMatrix(int r, int c)
{
	//Creates the adjacency matrix
	adjMartix = new Node*[r];
	for (int i = 0; i < r; i++)
	{
		adjMartix[i] = new Node[c];
	}

	
}


void mazesolver::BFS()
{   
    queueNode.push(make_pair(0, 0));
    while (!queueNode.empty())
    {
        int currentRow = queueNode.front().first;
        int currentColumn = queueNode.front().second;
        adjMartix[currentRow][currentColumn].visited = 1;

        // If we have reached the destination node, stop the BFS
        if (adjMartix[currentRow][currentColumn].color == 'O') {
            destRow = currentRow; // Set the row of the destination node
            destColumn = currentColumn; // Set the column of the destination node
            break;
        }

        AddNodesToQueue();
        queueNode.pop();
    }
}

//print the graph representing the path from the source node to the destination node in a maze.
void mazesolver::PrintGraph()
{
	int i = destRow; // Start from the row of the destination node
    int j = destColumn; // Start from the column of the destination node
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			cout << adjMartix[i][j].parentNode.first << '-' << adjMartix[i][j].parentNode.second << ' ';
		}
		cout << endl;
	}
}


void mazesolver::PrintPath(ofstream& outFile) {
    int i = destRow; // Start from the row of the destination node
    int j = destColumn; // Start from the column of the destination node
    int parentRow, parentColumn;
    int tempRow, tempColumn;

    do {
        parentRow = adjMartix[i][j].parentNode.first;
        parentColumn = adjMartix[i][j].parentNode.second;
        tempRow = i - parentRow;
        tempColumn = j - parentColumn;

        switch (adjMartix[parentRow][parentColumn].direction[0]) {
            case 'S':
                pathToEnd.emplace_back(adjMartix[parentRow][parentColumn].direction, tempRow);
                break;
            case 'N':
                pathToEnd.emplace_back(adjMartix[parentRow][parentColumn].direction, (tempRow * -1));
                break;
            case 'E':
                pathToEnd.emplace_back(adjMartix[parentRow][parentColumn].direction, tempColumn);
                break;
            case 'W':
                pathToEnd.emplace_back(adjMartix[parentRow][parentColumn].direction, tempColumn * -1);
                break;
        }

        i = parentRow;
        j = parentColumn;
    } while (i != 0 || j != 0);

    for (int i = pathToEnd.size()-1; i >= 0; i--) {
        outFile << pathToEnd[i].second << pathToEnd[i].first<< ' ';
    }
    outFile << endl;
}

// Sets all the values in the adj matrix
void mazesolver::SetGraph(string data) {
    column = 0;

    for (unsigned int i = 0; i < data.size(); i++) {
        switch (data[i]) {
            case 'R':
            case 'B':
                adjMartix[row][column].color = data[i];
                adjMartix[row][column].visited = 0;
                adjMartix[row][column].parentNode = make_pair(0, 0);

                if (data[i + 3] != ' ') {
                    adjMartix[row][column].direction = data.substr(i + 2, 2);
                    i = i + 3;
                } else {
                    adjMartix[row][column].direction = data.substr(i + 2, 1);
                    i = i + 2;
                }
                column++;
                break;
            case 'O':
                adjMartix[row][column].color = 'O';
                adjMartix[row][column].visited = 0;
                adjMartix[row][column].direction = data[i];
                column++;
                break;
        }
    }

    row++;
}

// Main function to read data from file and execute the solver
int main() {
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    if (!inFile.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    string firstLine;
    getline(inFile, firstLine); // Read the first line for dimensions

    int rows, cols;
    istringstream dimStream(firstLine);
    dimStream >> rows >> cols; // Extract rows and columns from the first line

    mazesolver maze;
    maze.CreateMatrix(rows, cols);

    string line;
    while (getline(inFile, line)) {
        maze.SetGraph(line);
    }

    maze.BFS();
    maze.PrintPath(outFile);

    return 0;
}
