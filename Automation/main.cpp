#include <iostream>
#include <math.h>
#include <stdio.h>
#include <fstream>

//Constants for additional change
#define _LENGTH  6
#define _inf 2147483646
#define maxVolume 1000
#define maxFuel 150
#define gTruckCnt 1


//----------

using namespace std;

int origin = 0;
typedef struct{
    int gVolumeRemaining;
    int tDistance;
    int Fuel;
} gTruck;

typedef struct{
    int gProduction[7];
    int tID;
    int gCurrent;
    int pickUpID;
} gBin;
int graph[6][6] = {{0, 10, 0, 0, 0, 0},
                   {10, 0, 10, 30, 0, 0},
                   {0, 10, 0, 20, 50, 0},
                   {0, 30, 20, 0, 0, 10},
                   {0, 0, 50, 0, 0, 10},
                   {0, 0, 0, 10, 10, 0}};

int nodes[2][_LENGTH] = {{_inf,_inf,_inf,_inf,_inf,_inf}, {_inf,_inf,_inf,_inf,_inf,_inf}};
gTruck gTruckArr[gTruckCnt];
gBin gBinArr[_LENGTH];

void InitVars(int numGTrucks, int nGBin){
    for(int i = 0; i<gTruckCnt; i++){
        gTruckArr[i].gVolumeRemaining = maxVolume;
        gTruckArr[i].Fuel = maxFuel;
        gTruckArr[i].tDistance = 0;
    }
    for(int i = 0; i<_LENGTH; i++){
        gBinArr[i].gCurrent = 0;
        gBinArr[i].tID = -1;
        gBinArr[i].pickUpID = -1;
        for(int y = 0; y<7; y++) gBinArr[i].gProduction[y] = 0;
    }
}

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
