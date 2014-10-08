#include <iostream>
#include <math.h>
#include <stdio.h>
#include <fstream>


#define _LENGTH 6
#define _inf 2147483646

using namespace std;

int origin = 0;


int graph[6][6] = {{0, 10, 0, 0, 0, 0},
                   {10, 0, 10, 30, 0, 0},
                   {0, 10, 0, 20, 50, 0},
                   {0, 30, 20, 0, 0, 10},
                   {0, 0, 50, 0, 0, 10},
                   {0, 0, 0, 10, 10, 0}};

int nodes[2][_LENGTH] = {{_inf,_inf,_inf,_inf,_inf,_inf}, {_inf,_inf,_inf,_inf,_inf,_inf}};


void relax(int current_node){
    for(int i=0; i<_LENGTH; i++){
        if(graph[current_node][i] > 0){
            if(nodes[0][i] > nodes[0][current_node] + graph[i][current_node]){
                nodes[0][i] = nodes[0][current_node] + graph[i][current_node];
                nodes[1][i] = current_node;
                relax(i);
            }

        }
    }
    return;
}

int main()
{
    nodes[0][0] = 0;
    nodes[1][0] = 0;
    relax(0);
    for(int i = 0; i<_LENGTH; i++) printf("%d ", nodes[0][i]);
    printf("\n");
    for(int i = 0; i<_LENGTH; i++) printf("%d ", nodes[1][i]);
    getchar();

    return 0;
}
