#ifndef heap_hpp
#define heap_hpp
#include <stdio.h>
#include <iostream>

struct Node{
    int vertex;
    float distance;
};

class heap{
private:
    /*pointer to an array for heap*/
    Node *heap_array;
    /*size of current heap*/
    int curr_size;
    /*num of children in heap*/
    int num_child;
    /*max value of heap*/
    int max;
    /*position of vertex noted by int value*/
    int *heap_posi;

public:
    heap(int vertices, int node_child);
    bool is_empty();
    bool is_max();
    int parent(int child_idx);
    int child_index(int parent_index, int child);
    int vertex_posi(int vertex);
    void swap_idx(Node x, Node y, int x_idx, int y_idx);
    void insert_elt(int v, float d);
    void BubbleUp(int insert_pos);
    Node DeleteMin(Node min);
    void MinHeapify(int parent_pos);
};

#endif
