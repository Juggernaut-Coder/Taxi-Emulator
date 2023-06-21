
#pragma once
#include <math.h>

typedef struct Node{
    float g, h;
    struct Node* parent;
    int row, col;

    float distance;
}Node;
    

Node* createNode(int row, int col, Node* parent){
    Node* node = (struct Node*)malloc( sizeof(Node));
    node->row = row;
    node->col = col;
    node->parent = parent;

    node->g = 0;
    node->h = 0;
    node->distance = 999999999;
    return node;
} 
float getNodeF(Node* node){
    return node->g + node->h;
}

int isNodeEqual(Node* a,Node*b) {
    return (a->row == b->row && a->col == b->col) ? 1 : 0;
}

float euclidean_distance(Node* node1, Node* node2) {
    return sqrt((node2->row - node1->row) * (node2->row - node1->row) + (node2->col - node2->col) * (node2->col - node2->col));
}

float manhattan_distance(Node* node1, Node* node2) {
    return abs(node2->row - node1->row) + abs(node2->col - node1->col);
}