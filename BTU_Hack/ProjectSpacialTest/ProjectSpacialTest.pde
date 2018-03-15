//gamepad
import org.gamecontrolplus.gui.*;
import org.gamecontrolplus.*;
import net.java.games.input.*;
//spacial mapping
import deadpixel.keystone.*;

//spacial mapping
Keystone ks;
CornerPinSurface surface;
PGraphics offscreen;

//gamepad
ControlIO control;
ControlDevice gpad;
//gamepad controls
float xAxis;
float yAxis;
boolean zero;
boolean one;
boolean two;
boolean three;
boolean four;
boolean five;
boolean six;
boolean seven;
//time variables
int lastTime;
float deltaTime = 0;

PImage level;
PImage altLevel;
int[] data;

int spawnX = 0;
int spawnY = 0;
int numPoints = 0;

float x;
float y;
float velX;
float velY;
float maxVelX = 3;
float maxVelY = 6;
float minJumpVel = 3;
float maxJumpVel = 8;
boolean jump = true;
boolean grounded = false;
int pWidth = 20;
int pHeight = 30;

boolean updateData = true;

void settings() {
  level = loadImage("level.jpg");
  altLevel = loadImage("level.jpg");
  size(round(level.width*1.5f), level.height,P3D);
  //size(1920,1200,P3D);
  //print(1920+";"+1200);
  data = new int[level.width*level.height];
}
void setup() {
  ProcessImage(level);
  //color representation of data
  for (int i=0;i<altLevel.width*altLevel.height;i++) {
    if (data[i] == 0) {
      altLevel.set(i%altLevel.width,i/altLevel.width,color(198,159,0));
    } else if (data[i] == 1) {
      altLevel.set(i%altLevel.width,i/altLevel.width,color(175,47,154));
    } else if (data[i] == 2) {
      altLevel.set(i%altLevel.width,i/altLevel.width,color(80,255,0));
    } else if (data[i] == 3) {
      altLevel.set(i%altLevel.width,i/altLevel.width,color(0,246,255));
    }
  }
  // Initialise the ControlIO
  control = ControlIO.getInstance(this);
  // Find a device that matches the configuration file
  gpad = control.getMatchedDevice("snes");
  if (gpad == null) {
    println("No suitable device configured");
    //System.exit(-1); // End the program NOW!
  }
  ks = new Keystone(this);
  surface = ks.createCornerPinSurface(level.width, level.height, 20);
  offscreen = createGraphics(level.width,level.height, P3D);
  surface.moveTo(level.width/2,0);
}

void draw() {
  //gamepad controls
  if (gpad != null) {
    xAxis = gpad.getSlider("X").getValue();
    yAxis = gpad.getSlider("Y").getValue();
    zero = gpad.getButton("ZERO").pressed();
    one = gpad.getButton("ONE").pressed();
    two = gpad.getButton("TWO").pressed();
    three = gpad.getButton("THREE").pressed();
    four = gpad.getButton("FOUR").pressed();
    five = gpad.getButton("FIVE").pressed();
    six = gpad.getButton("SIX").pressed();
    seven = gpad.getButton("SEVEN").pressed();
  }
  
  //get deltaTime
  deltaTime = (millis()-lastTime)/1000f;
  lastTime = millis();
  //spacial mapping
  //PVector surfaceMouse = surface.getTransformedMouse();
  
  //physics
  DoPhysics();
  
  offscreen.beginDraw();
  offscreen.background(255);
  
  offscreen.image(level,0,0);
  offscreen.fill(54,193,156);
  offscreen.rect(x-pWidth/2,y-pHeight/2,pWidth,pHeight);
  
  offscreen.endDraw();
  
  // render the scene, transformed using the corner pin surface
  //background(0);
  fill(0);
  rect(level.width/2,0,level.width,level.height);
  surface.render(offscreen);
  if (updateData) {
    image(level,0,0,level.width/2,level.height/2);
    image(altLevel,0,level.height/2,level.width/2,level.height/2);
  }
}
float GetDistance(color c1,color c2) {
  return sqrt(pow(red(c1)-red(c2),2)+pow(green(c1)-green(c2),2)+pow(blue(c1)-blue(c2),2));
}
void die() {
  x = spawnX;
  y = spawnY;
  velX = 0;
  velY = 0;
  jump = false;
}

void keyPressed() {
  switch(key) {
  case 'c':
    // enter/leave calibration mode, where surfaces can be warped 
    // and moved
    ks.toggleCalibration();
    break;
  case 'w':
    yAxis = 1;
    break;
  case 'a':
    xAxis = -1;
    break;
  case 's':
    yAxis = -1;
    break;
  case 'd':
    xAxis = 1;
    break;
  }
}