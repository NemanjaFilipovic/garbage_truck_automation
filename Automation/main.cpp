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
    FILE* outputFile = fopen("outFile", "w");

    //----read File --------
    ReadFile();
    InitVars(gTruckCnt, _LENGTH);
    calculateEveryDistance();

    for(int cnter = 0; cnter < _LENGTH; cnter++){
        fprintf(outputFile,"--------%d-------\n", cnter);
        for(int i = 0; i<_LENGTH; i++) fprintf(outputFile,"%d ", nodes[0][i][cnter]);
        fprintf(outputFile,"\n");
        for(int i = 0; i<_LENGTH; i++) fprintf(outputFile,"%d ", nodes[1][i][cnter]);
        fprintf(outputFile,"\n");

    }
    getchar();


    return 0;
}
