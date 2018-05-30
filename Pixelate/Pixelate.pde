PImage test;

Sprite background;
Sprite explode;
Sprite explode2;
Sprite grass;
Sprite tree;
Sprite windMillBlade;
Sprite windMill;


float ratio;

Filter f;
void setup() {
  size(500,500,P2D);
  frameRate(30);
  f = new Filter(500,500,1,1);
  test = loadImage("test.png");
  background = new Sprite("sky.jpg",0,0,f.temp.width,f.temp.height);
  explode = new Sprite("Explode.png",6,6,1,10,10,100,100);
  explode2 = new Sprite("Explode.png",6,6,1,200,200,200,200);
  grass = new Sprite("grassTile.png",0,f.temp.height-100);
  tree = new Sprite("Trees.png",300,f.temp.height-220);
  windMillBlade = new Sprite("WindMillBlade.png",4,2,1,90,10,350,350);
  windMill = new Sprite("windmill.png",8,1,1,10,10,350,350);
}

void draw() {
  
  background(255);
  f.temp.beginDraw();
  f.temp.background(255);
  
  background.render();
  
  DoRainTick();
  DoRainDraw();
  
  tree.render();
  grass.render();
  windMillBlade.render();
  windMillBlade.incrementFrame();
  //windMill.render();
  //windMill.incrementFrame();
  
  f.temp.endDraw();
  //f.debug();
  f.execute();
  
  //intro resolution increase
  if (f.dest.width < 64) {
    f.setRes(f.dest.width+1);
  }
}
