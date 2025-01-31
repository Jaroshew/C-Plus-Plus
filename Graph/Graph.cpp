/* This program implements a graph using an adjacency list.
It includes Depth-First Search (DFS) and Breadth-First Search (BFS). */

#include <iostream>
#include <limits> // numeric_limits
using namespace std;

class Node {
public:
    int id; // Vertex identifier (ID)
    Node* next; // Reference to the next vertex in the list

    Node(int id); // Constructor
};

class Graph {
private:
    int vertices; // Number of vertices
    Node** adjacencyList; // Adjacency list
    Node* removeNode(Node* head, int id); // Removes a node from the list
    bool DFSUtil(int vertex, int endVertex, bool* visited, int& steps); // Helper function for DFS

public:
    Graph(int vertices);
    ~Graph();

    void addEdge(int source, int destination); // Adds an edge between two vertices
    void removeEdge(int source, int destination); // Removes an edge between two vertices
    void printGraph(); // Prints the graph
    void addStandardEdges(); // Adds a default set of edges
    void DFS(int startVertex, int endVertex); // Depth-First Search
    void BFS(int startVertex, int endVertex); // Breadth-First Search
};

Node::Node(int id) : id(id), next(nullptr) {}

// adjacencyList is initialized as an array with references, where each element is nullptr
Graph::Graph(int vertices) {
    this->vertices = vertices;
    adjacencyList = new Node*[vertices];
    for (int i = 0; i < vertices; ++i) {
        adjacencyList[i] = nullptr;
    }
}

// Destructor. Removes all vertices of the graph
Graph::~Graph() {
    for (int i = 0; i < vertices; ++i) {
        Node* current = adjacencyList[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjacencyList;
}

// Adds an edge between source and destination vertices. Since the graph is undirected, two entries need to be added to the adjacency list.
void Graph::addEdge(int source, int destination) {
    Node* newNode = new Node(destination);
    newNode->next = adjacencyList[source];
    adjacencyList[source] = newNode;

    newNode = new Node(source);
    newNode->next = adjacencyList[destination];
    adjacencyList[destination] = newNode;
}

// Removes an edge between 'source' and 'destination'
void Graph::removeEdge(int source, int destination) {
    adjacencyList[source] = removeNode(adjacencyList[source], destination);
    adjacencyList[destination] = removeNode(adjacencyList[destination], source);
}

// Removes a node
Node* Graph::removeNode(Node* head, int id) {
    if (head == nullptr) {
        return nullptr;
    }
    if (head->id == id) {
        return head->next;
    }
    Node* current = head;
    while (current->next != nullptr && current->next->id != id) {
        current = current->next;
    }
    if (current->next != nullptr) {
        current->next = current->next->next;
    }
    return head;
}

// Prints the graph
void Graph::printGraph() {
    for (int i = 0; i < vertices; ++i) {
        cout << i << ": ";
        Node* current = adjacencyList[i];
        while (current != nullptr) {
            cout << "--" << current->id << " ";
            current = current->next;
        }
        cout << endl;
    }
}

// The visited array marks visited vertices.
void Graph::DFS(int startVertex, int endVertex) {
    bool* visited = new bool[vertices]();
    int steps = -1; // Start from -1 because the first step will be added after the first traversal
    bool found = DFSUtil(startVertex, endVertex, visited, steps);
    if (!found) {
        cout << "Vertex " << endVertex << " is not reachable.\n";
    }
    delete[] visited;
}

// Recursively performs Depth-First Search (DFS) in the graph, visiting all neighbors.
bool Graph::DFSUtil(int vertex, int endVertex, bool* visited, int& steps) {
    visited[vertex] = true;
    steps++;

    cout << vertex << " ";

    if (vertex == endVertex) {
        cout << "\nReached the destination vertex " << endVertex << " in " << steps << " steps.\n";
        return true;
    }

    Node* current = adjacencyList[vertex];
    while (current) {
        if (!visited[current->id]) {
            if (DFSUtil(current->id, endVertex, visited, steps)) {
                return true;
            }
        }
        current = current->next;
    }

    return false;
}

// Performs Breadth-First Search (BFS) in the graph, starting from the specified vertex.
void Graph::BFS(int startVertex, int endVertex) {
    bool* visited = new bool[vertices](); // Array to mark visited vertices
    int* queue = new int[vertices]; // Queue for performing the search

    int front = 0, rear = 0;
    int steps = -1;  // -1 to avoid counting the starting vertex as a step.

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++]; // Removes a vertex from the queue
        cout << currentVertex << " ";

        // If the destination vertex is reached
        if (currentVertex == endVertex) {
            cout << "\nReached the destination vertex " << endVertex << " in " << steps << " steps.\n";
            delete[] visited;
            delete[] queue;
            return;
        }

        Node* current = adjacencyList[currentVertex];
        while (current) {
            if (!visited[current->id]) {
                visited[current->id] = true;
                queue[rear++] = current->id;
                steps++; // Increment steps when transitioning to a new vertex
            }
            current = current->next;
        }
    }

    cout << "\nThe destination vertex " << endVertex << " is not reachable.\n";
    delete[] visited;
    delete[] queue;
}

// Function to check if the entered value is valid
bool isValidInput() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please try again.\n";
        return false;
    }
    return true;
}

// Function to load a default set of edges
void Graph::addStandardEdges() {
    addEdge(0, 1);
    addEdge(0, 4);
    addEdge(1, 2);
    addEdge(1, 3);
    addEdge(1, 4);
    addEdge(2, 3);
    addEdge(3, 4);
    cout << "Default set of edges added.\n";
}

// Main function
int main() {
    int vertices = 5;
    Graph g(vertices);
    bool running = true;

    while (running) {
        int choice;
        cout << "\nMenu:\n";
        cout << "1. Add an edge\n";
        cout << "2. Remove an edge\n";
        cout << "3. Print the graph\n";
        cout << "4. Perform DFS (Depth-First Search)\n";
        cout << "5. Perform BFS (Breadth-First Search)\n";
        cout << "6. Add a default set of edges (for testing)\n";
        cout << "7. Exit\n";
        cout << "Choose an action: ";
        cin >> choice;

        if (!isValidInput()) {
            continue;
        }

        switch (choice) {
            case 1: {
                int src, dest;
                cout << "Enter the vertices (src dest): ";
                cin >> src >> dest;
                if (!isValidInput()) continue;
                g.addEdge(src, dest);
                break;
            }
            case 2: {
                int src, dest;
                cout << "Enter the vertices (src dest): ";
                cin >> src >> dest;
                if (!isValidInput()) continue;
                g.removeEdge(src, dest);
                break;
            }
            case 3:
                g.printGraph();
                break;
            case 4: {
                int start, end;
                cout << "Enter the starting vertex: ";
                cin >> start;
                cout << "Enter the destination vertex: ";
                cin >> end;
                g.DFS(start, end);
                break;
            }
            case 5: {
                int start, end;
                cout << "Enter the starting vertex: ";
                cin >> start;
                cout << "Enter the destination vertex: ";
                cin >> end;
                g.BFS(start, end);
                break;
            }
            case 6:
                g.addStandardEdges();
                break;
            case 7:
                running = false;
                cout << "Program terminated.\n";
                break;
            default:
                cout << "Invalid choice!\n";
                break;
        }
    }

    return 0;
}
