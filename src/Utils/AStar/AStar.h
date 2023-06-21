#pragma once
#include "Graph.h"	
#include "../vector.h"
#include "../vec.h"
 
typedef struct Astar {
    vector open_list;
    vector close_list;
    Graph* graphData;

    Node* startNode;
    Node* endNode;

}Astar;

Astar* createAstar(Graph* graphData){
    Astar* astar = (Astar*)malloc( sizeof(Astar));
    vector_init(&astar->open_list);
    vector_init(&astar->close_list);
    astar->graphData = graphData;
    return astar;
}

Node* isInOpenList(Astar* astar, Node* node) {

    for (int i = 0 ; i < vector_total(&astar->open_list);i++) {
        Node* n  = (Node*)vector_get(&astar->open_list,i); 
        if (isNodeEqual(n,node) == 1) {
            return n;
        }
    }
    return NULL;
}
Node* isInCloseList(Astar* astar, int row, int col) {
    for (int i = 0 ; i < vector_total(&astar->close_list);i++) {
        Node* n  = (Node*)vector_get(&astar->close_list,i); 
        if (n->row == row && n->col == col) {
            return n;
        }
    }
    return NULL;
}

int findMinFNode(Astar* astar) {
    int min = 999999999;
    // Node* minF_node = nullptr;
    int index = 0;
    for (int i = 0 ; i < vector_total(&astar->open_list);i++) {
        Node* n  = (Node*)vector_get(&astar->open_list,i); 
        if (getNodeF(n) < min) {
            min = getNodeF(n);
            index = i;
        }
    }
    return index;
}

void exploreNeightbour(Astar* astar,Node* node) {
    // int dir_row[8] = { 1,-1,1,-1,1,-1,0,0 };
    // int dir_col[8] = { -1,-1,1,1,0,0,1,-1 };
    int dir_row[4] = { -1, 1, 0, 0 };
    int dir_col[4] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; i++) {
        int new_row = dir_row[i] + node->row;
        int new_col = dir_col[i] + node->col;

        if (new_row > astar->graphData->height - 1 || new_row < 0 || new_col > astar->graphData->width - 1 || new_col < 0) {
            continue;
        }
        if (astar->graphData->grid[new_row][new_col] == 2 ) {
            continue;
        }
        if (astar->graphData->grid[new_row][new_col] == 4 ) {
            continue;
        }
        if (astar->graphData->grid[new_row][new_col] == 5 ) {
            continue;
        }
        if (isInCloseList(astar,new_row, new_col) != NULL) {
            continue;
        }
        if(astar->graphData->grid[new_row][new_col] == 0 && astar->graphData->grid[node->row][node->col] == 0 ){
            if(isGraphNodeConnected(astar->graphData->graphNodes[node->row][node->col],new_row,new_col) == 0){
                continue;
            }
        }

        Node* new_node = createNode(new_row,new_col,node);
        if (isInOpenList(astar,new_node) != NULL) {
            new_node = isInOpenList(astar,new_node);
        }

        float path_to_this_neightbour = node->g + 1;

        if (path_to_this_neightbour < new_node->g || isInOpenList(astar,new_node) == NULL) {
            // is mud

            new_node->g = path_to_this_neightbour;
            new_node->h = euclidean_distance(new_node, astar->endNode);

            //graphData->changeType(new_node->getRow(), new_node->getCol(), 1);
            if (isInOpenList(astar,new_node) == NULL) {
                vector_add(&astar->open_list,new_node);
            }
        }
    }

}

void showPath(vector* path,Node* node) {
    vector_init(path);
    Node* tmp = node;
    vector tracepath;
    vector_init(&tracepath);

    while (tmp != NULL)
    {
        vector_add(&tracepath,tmp);
        tmp = tmp->parent;
    }

    for (int i = vector_total(&tracepath) - 2; i >= 0; i--) {
        Node* n = (Node*)vector_get(&tracepath,i);
        vector_add(path,newVec2P(n->col * 32, n->row * 32));
    }
}


void aStarFinding(Astar* astar,vector* path,Vec2i start,Vec2i end) {
    vector_free(&astar->open_list);
    vector_free(&astar->close_list);
    vector_init(&astar->open_list);
    vector_init(&astar->close_list);


    astar->startNode = createNode(start.y,start.x,NULL) ;
    astar->endNode =  createNode(end.y,end.x,NULL);

    vector_add(&astar->open_list,astar->startNode);
    while (vector_total(&astar->open_list) > 0) {

        int i_min = findMinFNode(astar);
        Node* currentNode = (Node*)vector_get(&astar->open_list,i_min);
        // if(astar->graphData->graphNodes[currentNode->row][currentNode->col]->next != NULL){
        //     printf("y\n");
        //     printf("%d %d\n",astar->graphData->graphNodes[currentNode->row][currentNode->col]->next->row,astar->graphData->graphNodes[currentNode->row][currentNode->col]->next->col);
        // }

        vector_add(&astar->close_list,currentNode);
        if (isNodeEqual(currentNode,astar->endNode) == 1) {
            // if (debug == 1) {
            //     cout << "Nodes Visited: " << this->close_list.size() << "\n";
            // }
            showPath(path,currentNode);
        }
        vector_delete(&astar->open_list,i_min);
        exploreNeightbour(astar,currentNode);
    }
}
