int[][] compgraph;
int[][] graphelements;
int graphsize = 30;
int rad = 10;
PrintWriter output;
int mousex,mousey;
int origin=-1;
int destination=1;
int loopednode=0;




void setup()
{
 
 compgraph = new int [graphsize][graphsize];
 graphelements = new int [graphsize][2];
 output = createWriter("graph.txt"); 
 size(600,600);
 background(255);
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
      println(origin);
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
            line(graphelements[origin][0], graphelements[origin][1],
                 graphelements[i][0],graphelements[i][1]);
            
            
            loopednode=1;
         }
    
         if(loopednode==0)
         {
           line(graphelements[origin][0], graphelements[origin][1],
                mouseX,mouseY);
           ellipse(mouseX, mouseY, rad, rad);
           graphelements[destination][0]=mouseX;
           graphelements[destination][1]=mouseY;
           destination++;
         }
         
  }
  origin=-1;
  loopednode=0;
  print(destination);
  
}
