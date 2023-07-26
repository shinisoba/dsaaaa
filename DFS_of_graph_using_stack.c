#include <stdio.h>
#include <stdlib.h>

#define MAX 15

int stack[MAX];
int top = -1;
int Graph[MAX][MAX];

void push(int item) {
    top++;
    stack[top] = item;
}

int pop() {
    return stack[top--];
}

int peek() {
    return stack[top];
}

typedef struct Node {
    char nodeName;
    int visit;
} Node;

Node* nodes[MAX];
int N, M;
int nodeCount = 0;
char nodeNames[MAX];
int nodeIndices[MAX];

void addNode(char nodeName) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->nodeName = nodeName;
    newNode->visit = 0;
    nodes[nodeCount] = newNode;
    nodeNames[nodeCount] = nodeName;
    nodeIndices[nodeCount] = nodeCount;
    nodeCount++;
}

void displayNode(int nodeIndex) {
    if (nodes[nodeIndex]->visit == 1) {
        printf("%c ", nodes[nodeIndex]->nodeName);
        nodes[nodeIndex]->visit = 1;
        push(nodeIndex);
    }
}

int getAdjUnvisitedNode(int nodeIndex) {
    for (int i = 0; i < N; i++) {
        if (Graph[nodeIndex][i] == 1 && nodes[i]->visit == 0) {
            return i;
        }
    }
    return -1;
}

void addEdges(int Adj[MAX][MAX], int edges[][2]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Adj[i][j] = 0;
        }
    }

    for (int i = 0; i < M; i++) {
        int x = edges[i][0];
        int y = edges[i][1];

        Adj[x][y] = 1;
        Adj[y][x] = 1;
    }
}

void printAdjMatrix(int Adj[MAX][MAX]) {
    printf("  ");
    for (int k = 1; k <= N; k++) {
        printf("%d ", k);
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < N; j++) {
            printf("%d ", Adj[i][j]);
        }
        printf("\n");
    }
}

void depthFirstSearch(char startNode) {
    for (int j = 0; j < nodeCount; j++) {
        if (nodes[j]->nodeName == startNode) {
            nodes[j]->visit = 1;
            displayNode(j);
            break;
        }
    }
    

    while (top != -1) {
        int currentNodeIndex;
        currentNodeIndex = peek();
        int unvisitedNode;
        unvisitedNode = getAdjUnvisitedNode(currentNodeIndex);

        if (unvisitedNode == -1) {
            pop();
        } 
        else {
            nodes[unvisitedNode]->visit = 1;
            displayNode(unvisitedNode);
        }
    }

    for (int i = 0; i < nodeCount; i++) {
        nodes[i]->visit = 0;
    }
}

int main() {
    printf("Enter the number of nodes: ");
    scanf("%d", &N);
    printf("The nodes of the input graph will be represented by alphabets, so please enter only alphabets as nodes.\n");
    char inpNode;
    for (int j = 0; j < N; j++) {
        printf("Enter %dth character node: ", j + 1);
        scanf(" %c", &inpNode);
        if (inpNode >= 65 && inpNode <= 90 || inpNode >= 97 && inpNode <= 122) {
            int found = 0;
            for (int k = 0; k < j; k++) {
                if (nodeNames[k] == inpNode) {
                    found = 1;
                    break;
                }
            }
            if (found) {
                printf("Duplicate node input. Please enter a unique node.\n");
                j--;
            } 
            else {
                nodeNames[j] = inpNode;
                addNode(inpNode);
            }
        } 
        else {
            printf("Invalid node input.\n");
            j--;
        }
    }

    printf("Enter the number of edges: ");
    scanf("%d", &M);
    int edges[M][2];
    char Anode, Bnode;
    for (int i = 0; i < M; i++) {
        printf("Enter the edges as < format: node1 node2 >: ");
        scanf(" %c %c", &Anode, &Bnode);
        int foundA = 0, foundB = 0;

        for (int v = 0; v < N; v++) {
            if (nodeNames[v] == Anode) {
                edges[i][0] = nodeIndices[v];
                foundA = 1;
            }
            if (nodeNames[v] == Bnode) {
                edges[i][1] = nodeIndices[v];
                foundB = 1;
            }
        }

        if (!(foundA && foundB)) {
            printf("Enter valid nodes.\n");
            i--; 
        }
    }

    addEdges(Graph, edges);
    printAdjMatrix(Graph);

    char dfsnode;
    printf("Enter the starting node for Depth First Search Traversal: ");
    scanf(" %c", &dfsnode);
    int vn=0;
    for (int l=0;l<N;l++){
        if (nodeNames[l]==dfsnode){
            vn = 1;
        }
    }
    if (vn == 1){
        printf("Depth First Search Traversal of the input graph:\n");
        depthFirstSearch(dfsnode);
    }
    else{
        printf("Node does not exist in the input graph.");
    }
    return 0;
}
