import processing.video.*;

Capture cam;

int lastTime;
int deltaTime = 0;

int timer = 0;

float threshold = 200;

void setup() {
  size(640, 480);
  String[] cameras = Capture.list();
  
  if (cameras.length == 0) {
    println("There are no cameras available for capture.");
    exit();
  } else {
    /*println("Available cameras:");
    for (int i = 0; i < cameras.length; i++) {
      println(cameras[i]);
    }*/
    
    // The camera can be initialized directly using an 
    // element from the array returned by list():
    cam = new Capture(this, cameras[0]);
    cam.start();     
    
    /*Thread t = new Thread(new RenderThread(cam));
    t.start();*/
  }      
}

void draw() {
  
  //get deltaTime
  deltaTime = millis()-lastTime;
  lastTime = millis();
  if (timer > 1000) {
      cam.read();
      timer -= 1000;
      image(cam, 0, 0);
      loadPixels();
      for (int i = 0; i < (width*height); i++) {
        //represents the distance from a color in grayscale, darker is closer
        //pixels[i] = color(GetDistance(pixels[i],color(197, 95, 83)));
        float dist = GetDistance(pixels[i],color(0));
        if (dist < threshold) {
          pixels[i] = color(0);
        }
      }
      updatePixels();
  } else {
    timer += deltaTime;
  }
  
}
float GetDistance(color c1,color c2) {
  return sqrt(pow(red(c1)-red(c2),2)+pow(green(c1)-green(c2),2)+pow(blue(c1)-blue(c2),2));
}