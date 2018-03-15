String fileName = "rocks.png";
PImage image;
PGraphics canvas;
PGraphics canvas2;

int x = 0;
float 
int y = 200;

void setup() {
  size(800,800,P2D);
  image = loadImage(fileName);
  //image = rect();
  canvas = createGraphics(width,height);
  canvas2 = createGraphics(64,64);
  
}
void draw() {
  background(255);
  x++;
  canvas.beginDraw();
  canvas.image(image,0,0,width,height);
  noStroke();
  fill(130,200,30);
  canvas.rect(x,y,100,100);
  canvas.endDraw();
  canvas2.beginDraw();
  canvas2.image(canvas,0,0,64,64);
  canvas2.endDraw();
  
  image(canvas2,0,0,width,height);
}
void resize(PImage img, int w, int h) {
  colorMode(HSB);
  
}
void keyPressed() {
  
}