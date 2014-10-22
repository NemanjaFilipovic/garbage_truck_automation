void ReadFile(){
    FILE* inputFile = fopen("../graphgenerator_AdavancedII/graph.txt", "r");
    for(int x = 0; x < _LENGTH; x++)
        for(int y = 0; y <_LENGTH; y++)
            fscanf(inputFile, "%d ", &graph[x][y]);

    return;

}
