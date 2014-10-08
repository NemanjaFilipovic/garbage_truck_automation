 int[][] compgraph;
 int graphsize = 30;
 int rad = 50;
 int dist = 3000;
 int xcount = 0;
 int ycount=0;
 int[] graphgraf; 
 int mousex,mousey;
 int origin=-1;
 int destination=-1;
 
void setup()
{
 
 compgraph = new int [graphsize][graphsize];
 
 for(int i=1;i<graphsize/2;i++)
 {
   if(graphsize%i==0)
   {
     if(dist>abs(graphsize/i-i))
     {
       dist=abs(graphsize/i-i);
       xcount=i;        
     }
   }
 }

 size(rad*2*xcount+100,rad*2+100*(graphsize/xcount)+100);
 background(255); 
  
}

void draw()
{
  
  
  //(mouseX, mouseY, mouseX, mouseY);
  
  
  ycount=graphsize/xcount;
  for(int i=1;i<=xcount;i++)
    for(int j=1;j<=ycount;j++)
    {
      
      ellipse(i*(2*rad),j*(2*rad), rad,rad);
    }
    
    if(origin!=-1 && destination!=-1)
    {
      strokeWeight(5);
      line((origin/10)*(2*rad),
           (origin%10)*(2*rad),
           (destination/10)*(2*rad),
           (destination%10)*(2*rad));  
      strokeWeight(1);
     origin=-1;
     destination=-1;
     
    }
    
    print(origin);
    print("  ");
    println(destination);
}

void mouseClicked()
{
  mousex=mouseX;
  mousey=mouseY;
  for(int i=1;i<=xcount;i++)
    for(int j=1;j<=ycount;j++)
    {
      
      if(i*(2*rad)-rad<mousex && i*(2*rad)+rad>mousex)
        if(j*(2*rad)-rad<mousey && j*(2*rad)+rad>mousey)
        {
          if(origin==-1)
            origin=i*10+j;
          else
           destination=i*10+j; 
        }        
    }
 
}

