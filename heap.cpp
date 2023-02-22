#include "heap.hpp"
#include <iostream>

heap::heap(int vertices, int node_child)
{
    curr_size = 0;
    heap_array = new Node[vertices];
    heap_posi = new int[vertices];
    for (int i = 0; i < vertices; i++)
    {
        heap_posi[i] = -1;
    }
    num_child = node_child;
    max = vertices;
}

bool heap::is_empty()
{
    return curr_size == 0;
}

bool heap::is_max()
{
    return curr_size == max;
}

int heap::parent(int child_idx)
{
    return (child_idx - 1) / num_child;
}

int heap::child_index(int parent_index, int child)
{
    return (parent_index * num_child) + child;
}

int heap::vertex_posi(int vertex)
{
    if (heap_posi[vertex] != -1)
    {
        return heap_posi[vertex];
    }
    else
    {
        return -1;
    }
}

void heap::swap_idx(Node x, Node y, int x_idx, int y_idx)
{
    heap_posi[x.vertex] = y_idx;
    heap_posi[y.vertex] = x_idx;
}

/*need to finish check to see if function works*/
void heap::insert_elt(int v, float d)
{
    if (is_max())
    {
        std::cout << "Max heap size reached." << std::endl;
        return;
    }
    if (vertex_posi(v) == -1)
    {
        heap_array[curr_size].vertex = v;
        heap_array[curr_size].distance = d;
        heap_posi[v] = curr_size;
        BubbleUp(curr_size);
        curr_size++;
    }
    else
    {
        heap_array[heap_posi[v]].distance = d;
        MinHeapify(heap_posi[v]);
        BubbleUp(heap_posi[v]);
    }
}

/*need to finish*/
void heap::BubbleUp(int insert_pos)
{
    while (insert_pos > 0 && heap_array[insert_pos].distance < heap_array[parent(insert_pos)].distance)
    {
        int parent_pos = parent(insert_pos);
        swap_idx(heap_array[insert_pos], heap_array[parent_pos], insert_pos, parent_pos);
        std::swap(heap_array[insert_pos], heap_array[parent_pos]);
        insert_pos = parent_pos;
    }
}

/*need to finish*/
Node heap::DeleteMin(Node min)
{
    if (is_empty())
    {
        std::cout << "No elements in heap" << std::endl;
        return min;
    }
    min.vertex = heap_array[0].vertex;
    min.distance = heap_array[0].distance;
    heap_posi[heap_array[0].vertex] = -1;
    if (!is_empty())
    {
        heap_posi[heap_array[curr_size - 1].vertex] = 0;
    }
    heap_array[0] = heap_array[curr_size - 1];
    curr_size --;
    MinHeapify(0);
    return min;
}

void heap::MinHeapify(int parent_pos)
{
    int swap_pos = parent_pos;
    int swap_bool = 1;
    while (swap_bool)
    {
        for (int i = 1; i < num_child + 1; i++) {
            int child_pos = child_index(parent_pos, i);
            if (child_pos < curr_size) {
                if (heap_array[child_pos].distance < heap_array[swap_pos].distance) {
                    swap_pos = child_pos;
                }
            }
        }
        if (swap_pos != parent_pos) {
            swap_idx(heap_array[parent_pos], heap_array[swap_pos], parent_pos, swap_pos);
            std::swap(heap_array[parent_pos], heap_array[swap_pos]);
            parent_pos = swap_pos;
        }
        else {
            swap_bool = 0;
        }
    }
}