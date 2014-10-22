
//Constants for additional change
#define _LENGTH  30
#define _inf 2147483646
#define maxVolume 1000
#define maxFuel 150
#define gTruckCnt 1
#define density 10

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

int graph[_LENGTH][_LENGTH];

int nodes[2][_LENGTH][_LENGTH];
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
    for(int x = 0; x < 2; x++)
        for(int y = 0; y < _LENGTH; y++)
            for(int z = 0; z < _LENGTH; z++)
                nodes[x][y][z] = _inf;


}

void relax(int current_node, int current_origin){
    for(int i=0; i<_LENGTH; i++){
        if(graph[current_node][i] > 0){
            if(nodes[0][i][current_origin] > nodes[0][current_node][current_origin] + graph[current_node][i]){
                nodes[0][i][current_origin] = nodes[0][current_node][current_origin] + graph[current_node][i];
                nodes[1][i][current_origin] = current_node;
                relax(i, current_origin);
            }

        }
    }
    return;
}



void calculateEveryDistance(){
    for(int i = 0; i<_LENGTH; i++){
        nodes[0][i][i] = 0;
        nodes[1][i][i] = i;
        relax(i,i);
	}


    return;


}
