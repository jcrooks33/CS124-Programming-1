// Jeffs file for prims algorithm

#include <iostream>
#include <stdio.h>
#include <math.h>
#include "heap.hpp"



/* Prims Algorithm in comment form 

    float dist[n] - an array of size n to store verticies distances
    int prev[n] - an array of size n for verticies prev 
    heap D: our d heap
    float sum;
    int verticies[n] - an array of size n to store visited or not

    Set each verticy to have a large dist and to for all prev to be empty, also all verticies to be not visited

    Then take the start verticy and set it to 0, visited, and insert into heap

    We can also then set our largest edge variable

    Then while our D heap is not empty
        
        we will set v to be our minimum edge from the heap

        set v to be visited and add its weight to our sum

        then for all edges in v (without nodes already in S)
        We can create edges here since ours is based of randomness

            if the distance of w is greater than the edge weight

                set distance w = edge weight

                set prev of w = n

                add w and its distance to our heap
*/ 
float PrimAlg(float *x, float *y, float*z, float *q, int n, int dim) {
    float dist[n];
    int prev[n];
    float sum = 0;
    int visited[n];
    Node v = {-1, -1};

    for (int i = 1; i < n; i++){
        visited[i] = 0;
        dist[i] = 10000;
    }

    visited[0] = 1;
    dist[0] = 0;

    // find child value for dheap
    int child_value = n/8;

    //initialize dheap
    heap min_heap(n, child_value);

    //insert node 0
    min_heap.insert_elt(0,dist[0]);

    
    while(!min_heap.is_empty()){

        v = min_heap.DeleteMin(v);

       
        visited[v.vertex] = 1;
        sum += dist[v.vertex];

        for (int j = 0; j < n; j++) {
            if (visited[j] == 0) {
                int v1 = v.vertex;
                int v2 = j;
                float weight;

                if (dim == 0) {
                    weight = (float)rand()/RAND_MAX;
                }

                if (dim == 2) {
                    weight = sqrt(pow(x[v1] - x[v2], 2.0) + (pow(y[v1] - y[v2], 2.0)));
                }

                if (dim == 3) {
                    weight = sqrt(pow(x[v1] - x[v2], 2.0) + (pow(y[v1] - y[v2], 2.0)) + (pow(z[v1] - z[v2], 2.0)));
                }

                else {
                    weight = sqrt(pow(x[v1] - x[v2], 2.0) + (pow(y[v1] - y[v2], 2.0)) + (pow(z[v1] - z[v2], 2.0)) + (pow(q[v1] - q[v2], 2.0)));
                }

                if (dist[j] > weight) {
                    dist[j] = weight;
                    prev[j] = v.vertex;
                    // insert j into heap
                    min_heap.insert_elt(j, dist[j]);
                }
            }
        }      
    }

    return sum;
}

/* 
    Since we are basing edge weight off of coordinates that are random 
    we can compute them and then run prims alg 
    So we will make a function to make random coordinates
    then use those to run prims, and do this for each trial
*/

float Trials(int n, int trials, int dim) {
    srand((unsigned)time(NULL));
    float sum = 0.0;
    for (int i = 0; i < trials; i++) {
        if (dim == 0) {
            float x[1];
            float y[1];
            float z[1];
            float q[1];

            sum += PrimAlg(x, y, z, q, n, dim);
        }
        if (dim == 2) {
            float x[n];
            float y[n];
            float z[1];
            float q[1];
            for (int j = 0; j < n; j++){
                x[j] = (float)rand() / RAND_MAX;
                y[j] = (float)rand() / RAND_MAX;
            }

            sum += PrimAlg(x, y, z, q, n, dim);
        }
        else if (dim == 3) {
            float x[n];
            float y[n];
            float z[n];
            float q[1];
            for (int j = 0; j < n; j++){
                x[j] = (float)rand() / RAND_MAX;
                y[j] = (float)rand() / RAND_MAX;
                z[j] = (float)rand() / RAND_MAX;
            }

            sum += PrimAlg(x, y, z, q, n, dim);
        }
        else if (dim == 4){
            float x[n];
            float y[n];
            float z[n];
            float q[n];
            for (int j = 0; j < n; j++){
                x[j] = (float)rand() / RAND_MAX;
                y[j] = (float)rand() / RAND_MAX;
                z[j] = (float)rand() / RAND_MAX;
                q[j] = (float)rand() / RAND_MAX;
            }

            sum += PrimAlg(x, y, z, q, n, dim);
        }
    }
    return sum;
}

int main(int argc, const char * argv[]) {

    if (argc != 5) {
        printf("Invalid arguments.");
        return 1;
    }

    // denotes # of vertices in the graph
    int n = atoi(argv[2]);

    // how many times to calculate prim
    int trials = atoi(argv[3]);

    // dimensions for the problem
    int dim = atoi(argv[4]);

    float sum = Trials(n, trials, dim);
    std::cout << (sum / trials) << " " << n << " " << trials << " " << dim << std::endl;

    return 0;
}