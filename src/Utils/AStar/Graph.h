#pragma once
#include "Node.h"	

typedef struct GraphNode{
    int row;
    int col;
    struct GraphNode* left;
    struct GraphNode* right;
    struct GraphNode* up;
    struct GraphNode* down;
    int c;
}GraphNode;

GraphNode* newGraphNode(int row,int col){
    GraphNode* node = (GraphNode*)malloc( sizeof(GraphNode));
    node->row = row;
    node->col = col;
    node->left = NULL;
    node->right = NULL;
    node->up = NULL;
    node->down = NULL;

    node->c = 0;
    return node;
}

int isGraphNodeConnected(GraphNode* node, int row,int col){
    GraphNode* tmp = node->left;
    if (tmp != NULL)
    {
        if(tmp->row == row && tmp->col == col){
            return 1;
        }
    }
    tmp = node->right;
    if (tmp != NULL)
    {
        if(tmp->row == row && tmp->col == col){
            return 1;
        }
    }
    tmp = node->up;
    if (tmp != NULL)
    {
        if(tmp->row == row && tmp->col == col){
            return 1;
        }
    }
    tmp = node->down;
    if (tmp != NULL)
    {
        if(tmp->row == row && tmp->col == col){
            return 1;
        }
    }
    return 0;
}

typedef struct Graph{
   int** grid;
   GraphNode*** graphNodes;

    int width;
    int height;
    Vec2i start;
    Vec2i end;
}Graph;
    
GraphNode*** setupGraphNodes(GraphNode*** graphNodes){

    // first road
    for(int i = 1; i < 56; i++){
        graphNodes[27][i]->right = graphNodes[27][i+1];
    }
    for(int i = 27; i >= 1 ;i-- ){
        graphNodes[i][56]->up = graphNodes[i-1][56];
    }
    for(int i = 56; i >= 1; i--){
        graphNodes[26][i]->left = graphNodes[26][i-1];
    }
    for(int i = 1; i < 27; i++){
        graphNodes[i][1]->down = graphNodes[i+1][1];
    }

    for(int i = 56; i >= 1; i--){
        graphNodes[1][i]->left = graphNodes[1][i-1];
    }
    for(int i = 1; i < 27; i++){
        graphNodes[i][55]->down = graphNodes[i+1][55];
    }
    for(int i = 1; i < 56; i++){
        graphNodes[2][i]->right = graphNodes[2][i+1];
    }
    for(int i = 27; i >= 1 ;i-- ){
        graphNodes[i][2]->up = graphNodes[i-1][2];
    }

    for(int i = 1; i < 56; i++){
        graphNodes[23][i]->right = graphNodes[23][i+1];
    }
    for(int i = 1; i < 56; i++){
        graphNodes[20][i]->right = graphNodes[20][i+1];
    }
    for(int i = 1; i < 56; i++){
        graphNodes[16][i]->right = graphNodes[16][i+1];
    }
    for(int i = 1; i < 56; i++){
        graphNodes[13][i]->right = graphNodes[13][i+1];
    }
    for(int i = 1; i < 56; i++){
        graphNodes[9][i]->right = graphNodes[9][i+1];
    }
    for(int i = 1; i < 56; i++){
        graphNodes[6][i]->right = graphNodes[6][i+1];
    }

    for(int i = 56; i >= 1; i--){
        graphNodes[5][i]->left = graphNodes[5][i-1];
    }
    for(int i = 56; i >= 1; i--){
        graphNodes[8][i]->left = graphNodes[8][i-1];
    }
    for(int i = 56; i >= 1; i--){
        graphNodes[12][i]->left = graphNodes[12][i-1];
    }
    for(int i = 56; i >= 1; i--){
        graphNodes[15][i]->left = graphNodes[15][i-1];
    }
    for(int i = 56; i >= 1; i--){
        graphNodes[19][i]->left = graphNodes[19][i-1];
    }
    for(int i = 56; i >= 1; i--){
        graphNodes[22][i]->left = graphNodes[22][i-1];
    }

    for(int i = 1; i < 27; i++){
        graphNodes[i][5]->down = graphNodes[i+1][5];
    }
    for(int i = 1; i < 27; i++){
        graphNodes[i][11]->down = graphNodes[i+1][11];
    }
    for(int i = 1; i < 27; i++){
        graphNodes[i][15]->down = graphNodes[i+1][15];
    }
    for(int i = 1; i < 27; i++){
        graphNodes[i][21]->down = graphNodes[i+1][21];
    }
    for(int i = 1; i < 27; i++){
        graphNodes[i][25]->down = graphNodes[i+1][25];
    }
    for(int i = 1; i < 27; i++){
        graphNodes[i][31]->down = graphNodes[i+1][31];
    }
    for(int i = 1; i < 27; i++){
        graphNodes[i][35]->down = graphNodes[i+1][35];
    }
    for(int i = 1; i < 27; i++){
        graphNodes[i][41]->down = graphNodes[i+1][41];
    }
    for(int i = 1; i < 27; i++){
        graphNodes[i][45]->down = graphNodes[i+1][45];
    }
    for(int i = 1; i < 27; i++){
        graphNodes[i][51]->down = graphNodes[i+1][51];
    }

    for(int i = 27; i >= 1 ;i-- ){
        graphNodes[i][6]->up = graphNodes[i-1][6];
    }
    for(int i = 27; i >= 1 ;i-- ){
        graphNodes[i][12]->up = graphNodes[i-1][12];
    }
    for(int i = 27; i >= 1 ;i-- ){
        graphNodes[i][16]->up = graphNodes[i-1][16];
    }
    for(int i = 27; i >= 1 ;i-- ){
        graphNodes[i][22]->up = graphNodes[i-1][22];
    }
    for(int i = 27; i >= 1 ;i-- ){
        graphNodes[i][26]->up = graphNodes[i-1][26];
    }
    for(int i = 27; i >= 1 ;i-- ){
        graphNodes[i][32]->up = graphNodes[i-1][32];
    }
    for(int i = 27; i >= 1 ;i-- ){
        graphNodes[i][36]->up = graphNodes[i-1][36];
    }
    for(int i = 27; i >= 1 ;i-- ){
        graphNodes[i][42]->up = graphNodes[i-1][42];
    }
    for(int i = 27; i >= 1 ;i-- ){
        graphNodes[i][46]->up = graphNodes[i-1][46];
    }
    for(int i = 27; i >= 1 ;i-- ){
        graphNodes[i][52]->up = graphNodes[i-1][52];
    }

    return graphNodes;
}

Graph* createGraph(int width, int height,int **grid) {
    Graph* graph = (Graph*)malloc( sizeof(Graph));
    graph->width = width;
    graph->height = height;
    graph->grid = (int**)malloc(height * sizeof(int*));
    graph->graphNodes = (GraphNode***)malloc(height * sizeof(GraphNode**));

    for (int row = 0; row < height; row++) {
        graph->grid[row] = (int*)malloc(width * sizeof(int));
        graph->graphNodes[row] = (GraphNode**)malloc(width * sizeof(GraphNode*));
        for (int col = 0; col < width; col++) {
            graph->grid[row][col] = grid[row][col];
            graph->graphNodes[row][col] = newGraphNode(row,col);
        }
    }
    graph->start = newVec2(0, 0);
    graph->end = newVec2(0, 0);


    // GraphNode*** graphNodes = graph->graphNodes;

    graph->graphNodes = setupGraphNodes(graph->graphNodes);

    return graph;
}

void drawArrows(GraphNode*** graphNodes,int rows,int cols,MImage* left,MImage*right,MImage *up,MImage *down){
      for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            GraphNode* node = graphNodes[row][col];
            if(node->right != NULL){
                right->dest.x = col * 32 + 16 - 5;
                right->dest.y = row * 32 + 16 - 5;
                drawMImage(right);
            }
            if(node->left != NULL){
                left->dest.x = col * 32 + 16 - 5;
                left->dest.y = row * 32 + 16 - 5;
                drawMImage(left);
            }
            if(node->up != NULL){
                up->dest.x = col * 32 + 16 - 5;
                up->dest.y = row * 32 + 16 - 5;
                drawMImage(up);
            }
             if(node->down != NULL){
                down->dest.x = col * 32 + 16 - 5;
                down->dest.y = row * 32 + 16 - 5;
                drawMImage(down);
            }
        }
    }
}

GraphNode*** resetGraphNodeC(GraphNode*** graphNodes,int rows,int cols){
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            graphNodes[row][col]->c = 0;
        }
    }
    return graphNodes;
}

// void print() {
//     for (int i = 0; i < height; i++) {
//         for (int j = 0; j < width; j++) {

//             cout << this->grid[i][j] << " ";
//         }
//         cout << "\n";
//     }
// }
