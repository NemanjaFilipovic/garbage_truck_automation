import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class graphgenerator extends PApplet {

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
 PrintWriter output;
 
public void setup()
{
 
 compgraph = new int [graphsize][graphsize];
 output = createWriter("graph.txt"); 
 
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

public void draw()
{
  
  
  //(mouseX, mouseY, mouseX, mouseY);
  
  
  ycount=graphsize/xcount;
  for(int i=1;i<=xcount;i++)
    for(int j=1;j<=ycount;j++)
    {
      if((i*10+j)==origin)
        fill(255,0,0);
      if((i*10+j)==destination)
        fill(0,255,0);
      ellipse(i*(2*rad),j*(2*rad), rad,rad);
        fill(255);
    }
    
    if(origin!=-1 && destination!=-1)
    {
      strokeWeight(5);
      line((origin/10)*(2*rad),
           (origin%10)*(2*rad),
           (destination/10)*(2*rad),
           (destination%10)*(2*rad));  
      strokeWeight(1);
      
      compgraph[(origin/10)-1+(origin%10)-1]
               [(destination/10)-1+(destination%10)-1]       =1;
      compgraph[(destination/10)-1+(destination%10)-1]
               [(origin/10)-1+(origin%10)-1]       =1;
      
      origin=-1;
      destination=-1;
     
    }
    
    
    
    /*print(origin);
    print("  ");
    println(destination);*/
}

public void mouseClicked()
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

public void keyPressed() 
{
  for(int i=0;i<graphsize;i++)
  {
    for(int j=0;j<graphsize;j++)
    {
      output.print(compgraph[i][j]);
      output.print(" "); 
    }
    output.println(" ");
  }
  output.flush();
  output.close();
}

  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "graphgenerator" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
