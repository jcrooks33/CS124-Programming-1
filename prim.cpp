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
float primalg(float *x, float *y, float *z, float *q, int n, int dim) {
    //make our variables
    float dist[n];
    int prev[n];
    Node v = {-1, -1};
    float mstweight = 0.0;
    int visited[n];

    // child value for heap
    int childval = n/8;
    if (n == 131072) {
        childval = n/16;
    }
    heap heap(n, childval);

    for (int i = 1; i < n; i++) {

        // not visited
        visited[i] = 0;

        // make value large enough to be larger than coords
        dist[i] = 10000;
    }

    //start Prim's from the 1st vertex
    visited[0] = 1;
    dist[0] = 0;
    float largest = -10;

    heap.insert_elt(0, dist[0]);

    while (!heap.is_empty()) {

        v = heap.DeleteMin(v);
        
        // visited
        visited[v.vertex] = 1;
        mstweight += dist[v.vertex];

        if (dist[v.vertex] > largest)
            largest = dist[v.vertex];

        // go through edges
        for (int j = 0; j < n; j++) {
            if (visited[j] == 0) {

                int v1 = v.vertex;
                int v2 = j;

                float weight;

                if (dim == 0) {
                    weight = (float)rand() / RAND_MAX;
                }

                else if (dim == 2) {
                    weight = sqrt(pow(x[v1] - x[v2], 2.0) + (pow(y[v1] - y[v2], 2.0)));
                }

                else if (dim == 3) {
                    weight = sqrt(pow(x[v1] - x[v2], 2.0) + (pow(y[v1] - y[v2], 2.0)) + (pow(z[v1] - z[v2], 2.0)));
                }

                else {
                    weight = sqrt(pow(x[v1] - x[v2], 2.0) + (pow(y[v1] - y[v2], 2.0)) + (pow(z[v1] - z[v2], 2.0)) + (pow(q[v1] - q[v2], 2.0)));
                }

                

                if (dist[j] > weight) {
                    dist[j] = weight;
                    prev[j] = v.vertex;
                    heap.insert_elt(j, dist[j]);
                }
            }
        }
    }
    std::cout << largest;
    return mstweight;
}

int main(int argc, const char * argv[]) {

    if (argc != 5) {
        printf("Invalid arguments.");
        return 1;
    }

    // # of vertices, trials, and dimensions
    int n = atoi(argv[2]);
    int trials = atoi(argv[3]);
    int dim = atoi(argv[4]);

    // our random number depends on our seed, if we make our seed time, then over time our seed should change to give us enough randomness
    srand((unsigned)time(NULL));
    float mstweight = 0.0;
    for (int i = 0; i < trials; i++) {
        if (dim == 0) {
            // can just make coords using random
            float x[1];
            float y[1];
            float z[1];
            float v[1];

            mstweight += primalg(x, y, z, v, n, dim);
        }

        if (dim == 2) {
            float x[n];
            float y[n];
            float z[1];
            float q[1];

            // dim 2 coords
            for (int j = 0; j < n; j++) {
                x[j] = (float)rand() / RAND_MAX;
                y[j] = (float)rand() / RAND_MAX;
            }

            mstweight += primalg(x, y, z, q, n, dim);

        }

        else if (dim == 3) {
            float x[n];
            float y[n];
            float z[n];
            float q[1];

            // dim 3 coords
            for (int j = 0; j < n; j++) {
                x[j] = (float)rand() / RAND_MAX;
                y[j] = (float)rand() / RAND_MAX;
                q[j] = (float)rand() / RAND_MAX;
            }

            mstweight += primalg(x, y, z, q, n, dim);
        }

        else if (dim == 4) {
            float x[n];
            float y[n];
            float z[n];
            float q[n];

            // dim 4 coords
            for (int j = 0; j < n; j++) {
                x[j] = (float)rand() / RAND_MAX;
                y[j] = (float)rand() / RAND_MAX;
                z[j] = (float)rand() / RAND_MAX;
                q[j] = (float)rand() / RAND_MAX;
            }

            mstweight += primalg(x, y, z, q, n, dim);
        }
    }

    std::cout << mstweight / trials << " " << n << " " << trials << " " << dim << std::endl;

    return 0;
}

