int[][] compgraph;
int[][] graphelements;
int graphsize = 30;
int rad = 25;
PrintWriter output;
PrintWriter graphnodes;
int mousex,mousey;
int origin=-1;
int destination=1;
int loopednode=0;
PImage bckgrnd;



void setup()
{
 strokeWeight(2);
 compgraph = new int [graphsize][graphsize];
 graphelements = new int [graphsize][2];
 
 output = createWriter("graph.txt"); 
 graphnodes = createWriter("nodes.txt");
 
 size(850,400);
 bckgrnd=loadImage("Eliat.gif");
 background(bckgrnd);

 ellipse(rad/2+10, rad/2+10, rad, rad);
 graphelements[0][0]=rad/2+10;
 graphelements[0][1]=rad/2+10;
 
 

}

void draw() 
{
  
 
}


void mousePressed()
{
  mousex=mouseX;
  mousey=mouseY;
  for(int i=0;i<graphsize;i++)
    if(abs(graphelements[i][0]-mouseX)<rad/2 &&
       abs(graphelements[i][1]-mouseY)<rad/2)
    {
      origin=i;
      //     println(origin);
    }
 
}


void mouseReleased() 
{
  if(origin!=-1)
  {
    for(int i=0;i<graphsize;i++)
         if(abs(graphelements[i][0]-mouseX)<rad/2 &&
            abs(graphelements[i][1]-mouseY)<rad/2)
         {
           if(compgraph[i][origin]==0)
           {
              line(graphelements[origin][0], graphelements[origin][1],
                   graphelements[i][0],graphelements[i][1]);
                
              compgraph[origin][i]=int(sqrt(pow(graphelements[origin][0]-graphelements[i][0],2)+
                                            pow(graphelements[origin][1]-graphelements[i][1],2))) ;
           }  
           if(compgraph[i][origin]!=0)
           {
             stroke(0,255,0);
             line(graphelements[origin][0]+2, graphelements[origin][1],
                  graphelements[i][0]+2,graphelements[i][1]);
             stroke(0);
             compgraph[origin][i]=int(sqrt(pow(graphelements[origin][0]-graphelements[i][0],2)+
                                           pow(graphelements[origin][1]-graphelements[i][1],2))) ;
           } 
           loopednode=1;
         }
    
         if(loopednode==0)
         {
           line(graphelements[origin][0], graphelements[origin][1],
                mouseX,mouseY);
           ellipse(mouseX, mouseY, rad, rad);
           graphelements[destination][0]=mouseX;
           graphelements[destination][1]=mouseY;
           compgraph[origin][destination]=1;
           
           compgraph[origin][destination]=int(sqrt(pow(graphelements[origin][0]-graphelements[destination][0],2)+
                                         pow(graphelements[origin][1]-graphelements[destination][1],2))) ;
            
           
           destination++;
         }
         
  }
  origin=-1;
  loopednode=0;
  // print(destination);
  
}

void keyPressed()
{
  for(int i=0;i<graphsize; i++)
  {
    graphnodes.print(graphelements[i][0]);
    graphnodes.print("\t");
    graphnodes.print(graphelements[i][1]);
    graphnodes.print("\t");
    for(int j=0;j<graphsize; j++)
    { 
      output.print(compgraph[i][j]);
      output.print("\t"); 
    }
    output.println();
    graphnodes.println();
  }
  output.flush();
  graphnodes.flush();
  output.close();
  graphnodes.close();
  
}
