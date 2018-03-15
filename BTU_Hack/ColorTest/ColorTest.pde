PImage white;
PImage grey;
void setup() {
  size(600,300);
  white = loadImage("white.png");
  grey = loadImage("grey.png");
}
void draw() {
  tint(100);
  image(white,0,0,width/2,height);
  loadPixels();
  int gam = pixels[0];
  println(red(gam),green(gam),blue(gam));
  noTint();
  image(grey,width/2,0,width/2,height);
}
int gamma(int c, float g) {
  float R = pow(red(c)/255f,g);
  float G = pow(green(c)/255f,g);
  float B = pow(blue(c)/255f,g);
  //println(R,G,B);
  return color(R,G,B);
}