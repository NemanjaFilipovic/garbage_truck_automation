#include <iostream>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include "GraphAndDijkstra.h"
#include "OpenFile.h"

double fittness(gTruck currentTruck, int nNodes, int* nodes_){
    double fit;
    for(int i = 0; i < nNodes; i++){

    }
    return fit;

}


int main()
{
    //----read File --------
    FILE* inputFile = fopen("../graphgenerator_AdavancedII/graph.txt", "r");
    fprintf(inputFile, "something");

    InitVars(gTruckCnt, _LENGTH);
    calculateEveryDistance();

    for(int cnter = 0; cnter < _LENGTH; cnter++){
        printf("--------%d-------\n", cnter);
        for(int i = 0; i<_LENGTH; i++) printf("%d ", nodes[0][i][cnter]);
        printf("\n");
        for(int i = 0; i<_LENGTH; i++) printf("%d ", nodes[1][i][cnter]);
        printf("\n");

    }
    getchar();


    return 0;
}
