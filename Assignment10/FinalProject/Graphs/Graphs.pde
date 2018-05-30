/* Kyle Neubarth 2017 for CS2270. I made this! */

int marginX = 20;
int marginY = 20;

int graphMarginX = 30;
int graphMarginY = 30;

float lengthX = 900;
float lengthY = 1;

float dividersX = 20;
float dividersY = 0.1;

float numberX = 100;
float numberY = .5;

float[][][][] points;
String[] names = new String[] {
  "Average Enqueue Time",
  "Standard Deviation of\nAverage Enqueue Times",
  "Average Dequeue Time",
  "Standard Deviation of\nAverage Dequeue Times",
  "Average Total Run Time"
};
String[] ys = new String[] {
  "Milliseconds",
  "Standard Deviations",
  "Milliseconds",
  "Standard Deviations",
  "Milliseconds"
};
int drawIndex = 0;
int[][] colors = new int[][] {
  {244, 66, 66},
  {244, 66, 235},
  {66, 101, 244}
};

void setup() {
  size(720,600);
  
  getPoints("data.txt");
  
  DrawGraph(0);
}
void DrawGraph(int index) {
  stroke(1);
  background(230);
  scale(1, -1);
  translate(0, -height);
  fill(255);
  rect(marginX,marginY,width-2*marginX,height-2*marginY);
  
  int graphLength = width-2*(marginX + graphMarginX);
  int graphHeight = height-2*(marginY + graphMarginY);
  strokeWeight(1);
  //draw dividers
  for (int i=0;i<floor(lengthX/(float)dividersX);i++) {
    stroke(200);
    line(marginX + graphMarginX + i*dividersX*graphLength/lengthX,marginY + graphMarginY,marginX + graphMarginX + i*dividersX*graphLength/lengthX,height-(marginY + graphMarginY));
    stroke(0);
    line(marginX + graphMarginX + i*dividersX*graphLength/lengthX,marginY + graphMarginY-5,marginX + graphMarginX + i*dividersX*graphLength/lengthX,marginY + graphMarginY+5);
  }
  for (int i=0;i<floor(lengthY/(float)dividersY);i++) {
    stroke(200);
    line(marginX + graphMarginX,marginY + graphMarginY + i*dividersY*graphHeight/lengthY,width-(marginX + graphMarginX),marginY + graphMarginY + i*dividersY*graphHeight/lengthY);
    stroke(0);
    line(marginX + graphMarginX-5,marginY + graphMarginY + i*dividersY*graphHeight/lengthY,marginX + graphMarginX+5,marginY + graphMarginY + i*dividersY*graphHeight/lengthY);
  }
  //draw text and number wedges
  textSize(12);
  strokeWeight(3);
  fill(0);
  for (int i=0;i<floor(lengthX/(float)numberX);i++) {
    line(marginX + graphMarginX + i*numberX*graphLength/lengthX,marginY + graphMarginY-5,marginX + graphMarginX + i*numberX*graphLength/lengthX,marginY + graphMarginY+5);
    drawText(Float.toString(i*numberX),marginX + graphMarginX + i*numberX*graphLength/lengthX,marginY + graphMarginY-20);
  }
  for (int i=0;i<floor(lengthY/(float)numberY);i++) {
    line(marginX + graphMarginX-5,marginY + graphMarginY + i*numberY*graphHeight/lengthY,marginX + graphMarginX+5,marginY + graphMarginY + i*numberY*graphHeight/lengthY);
    drawText(Float.toString(i*numberY),marginX + graphMarginX-25,marginY + graphMarginY + i*numberY*graphHeight/lengthY);
  }
  noStroke();
  for (int i=points[0].length-1;i>=0;i--) {
    fill(colors[i][0],colors[i][1],colors[i][2]);
    stroke(colors[i][0],colors[i][1],colors[i][2]);
    float prevX = marginX + graphMarginX;
    float prevY = marginY + graphMarginY;
    for (int j=0;j<points[index][i].length;j++) {
      //print(index +", "+i+", "+j+"\n");
      line(prevX,prevY,marginX + graphMarginX + points[index][i][j][0]*graphLength/lengthX,marginY + graphMarginY + points[index][i][j][1]*graphHeight/lengthY);
      prevX = marginX + graphMarginX + points[index][i][j][0]*graphLength/lengthX;
      prevY = marginY + graphMarginY + points[index][i][j][1]*graphHeight/lengthY;
      ellipse(prevX,prevY,10,10); 
    }
  }
  stroke(0);
  strokeWeight(3);
  line(marginX + graphMarginX,marginY + graphMarginY,marginX + graphMarginX,height-(marginY + graphMarginY));
  line(marginX + graphMarginX,marginY + graphMarginY,width-(marginX + graphMarginX),marginY + graphMarginY);
  fill(0);
  textAlign(CENTER);
  textSize(30);
  drawText(names[drawIndex],width/2,height-80);
  
  //graph key
  fill(230);
  strokeWeight(1);
  rect(marginX + graphMarginX + 30,height-(marginY + graphMarginY + 235),150,120);
  fill(colors[0][0],colors[0][1],colors[0][2]);
  noStroke();
  rect(marginX + graphMarginX + 40,height-(marginY + graphMarginY + 235)+120-15-20,20,15);
  fill(colors[1][0],colors[1][1],colors[1][2]);
  noStroke();
  rect(marginX + graphMarginX + 40,height-(marginY + graphMarginY + 235)+120-30-40,20,15);
  fill(colors[2][0],colors[2][1],colors[2][2]);
  noStroke();
  rect(marginX + graphMarginX + 40,height-(marginY + graphMarginY + 235)+120-45-60,20,15);
  fill(0);
  textAlign(LEFT);
  textSize(15);
  drawText("Linked List",marginX + graphMarginX + 70,height-(marginY + graphMarginY + 235)+120-15-20+2);
  drawText("Binary Heap",marginX + graphMarginX + 70,height-(marginY + graphMarginY + 235)+120-30-40+2);
  drawText("STL queue",marginX + graphMarginX + 70,height-(marginY + graphMarginY + 235)+120-45-60+2);
  
  textSize(12);
  translate(14,30);
  pushMatrix();
  scale(-1,1);
  rotate(PI/2);
  text(ys[drawIndex], 0,0);
  popMatrix();
  translate(-14,-30);
  
  translate(30,5);
  pushMatrix();
  scale(1,-1);
  text("Number of Nodes", 0,0);
  popMatrix();
  
  save("Graph_"+drawIndex +".png");
}

void draw() {
}

void drawText(String txt,float x, float y) {
  translate(x,y);
  pushMatrix();
  scale(1,-1);
  text(txt, 0,0);
  popMatrix();
  translate(-x,-y);
}
void getPoints(String name) {
  String[] lines = loadStrings(name);
    
  points = new float[GraphsNum(lines)][][][];
  //print( "Graphs: "+points.length+"\n");
  //plots
  for(int i=0;i<points.length;i++) {
    
    points[i] = new float[PlotsNum(lines,i)][][];
    //print( "Plots " +i+": "+points[i].length+"\n");
    //points
    for (int j=0;j<points[i].length;j++) {
      points[i][j] = new float[PointsNum(lines,i,j)][];
      //print( "points " +j+": "+points[i][j].length+"\n");
    }
  }
  
  int graphsNum = 0;
  int plotsNum = 0;
  int pointsNum = 0;
  
  for (int i=0;i<lines.length;i++) {
    
    if (lines[i].charAt(0) == '~') {
      graphsNum++;
      plotsNum = 0;
      pointsNum = 0;
      continue;
    } else if (lines[i].charAt(0) == '-') {
      plotsNum++;
      pointsNum = 0;
      continue;
    }
    
    for (int j=0;j<lines[i].length();j++) {
      if (lines[i].charAt(j) == ',') {
        //print(lines[i] +": "+graphsNum+", "+plotsNum+", "+pointsNum+"\n");
        points[graphsNum][plotsNum][pointsNum] = new float[2];
        points[graphsNum][plotsNum][pointsNum][0] = Float.parseFloat(lines[i].substring(0,j));
        points[graphsNum][plotsNum][pointsNum][1] = Float.parseFloat(lines[i].substring(j+1));
        pointsNum++;
      }
    }
  }
}
int GraphsNum(String[] lines) {
  int ret = 1;
  for (int i=0;i<lines.length;i++) {
    if (lines[i].equals("~~~")) {
      ret++;
    }
  }
  return ret;
}
int PlotsNum(String[] lines,int graphIndex) {
  int plotNum = 1;
  int tempGraphNum = 0;
  for (int j=0;j<lines.length;j++) {
    if (lines[j].equals("---") && tempGraphNum == graphIndex) {
      plotNum++;
    }
    if (lines[j].equals("~~~")) {
      if (tempGraphNum == graphIndex) {
        break;
      } else {
        tempGraphNum++;
      }
    }
  }
  return plotNum;
}
int PointsNum(String[] lines,int graphIndex,int plotsIndex) {
  int pointNum = 0;
  int tempGraphNum = 0;
  int tempPlotsNum = 0;
  for (int j=0;j<lines.length;j++) {
    if (lines[j].equals("---") && tempGraphNum == graphIndex) {
      if (tempGraphNum == graphIndex && tempPlotsNum == plotsIndex) {
        break;
      } else {
        tempPlotsNum++;
      }
    } else if (lines[j].equals("~~~")) {
      if (tempGraphNum == graphIndex) {
        break;
      } else {
        tempGraphNum++;
      }
    } else if (tempGraphNum == graphIndex && tempPlotsNum == plotsIndex) {
      pointNum++;
    }
  }
  return pointNum;
}

void keyPressed() {
  if (key == ENTER) {
    if (drawIndex < points.length-1) {
      drawIndex++;
    }
    DrawGraph(drawIndex);
  }
}
