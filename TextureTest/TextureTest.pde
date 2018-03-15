PImage image;

int[][] uv;
int active = 0;
void setup() {
  image = loadImage("CircaInfinity.png");
  size(400,400,P2D);
  uv = new int[][] {{0,0},{0,0},{0,0},{0,0}};
}
void draw() {
  background(255);
  if (keyPressed) {
    if (key >= '1' && key <= '4') {
      active = Character.getNumericValue(key)-1;
    }
    //int keyInt = Character.getNumericValue(key);
    if (key == 'q') {
      uv[active][0]+=10;
    }
    if (key == 'w') {
      uv[active][0]-=10;
    }
    if (key == 'a') {
      uv[active][1]+=10;
    }
    if (key == 's') {
      uv[active][1]-=10;
    }
  }
  beginShape();
  texture(image);
  vertex(10, 10, uv[0][0], uv[0][1]);
  vertex(390, 10, uv[1][0], uv[1][1]);
  vertex(390, 390, uv[2][0], uv[2][1]);
  vertex(10, 390, uv[3][0], uv[3][1]);
  endShape();
}