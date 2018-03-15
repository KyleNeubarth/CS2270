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

void settings() {
  level = loadImage("level.jpg");
  size(level.width, level.height,P3D);
  data = new int[level.width*level.height];
}
void setup() {
  ProcessImage(level);
  // Initialise the ControlIO
  control = ControlIO.getInstance(this);
  // Find a device that matches the configuration file
  gpad = control.getMatchedDevice("snes");
  if (gpad == null) {
    println("No suitable device configured");
    System.exit(-1); // End the program NOW!
  }
  //calculate spawn
  
}

void draw() {
  //gamepad controls
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
  
  //get deltaTime
  deltaTime = (millis()-lastTime)/1000f;
  lastTime = millis();
  
  /*for (int i=0;i<width*height;i++) {
    if (data[i] == 0) {
      set(i%width,i/width,color(198,159,0));
    } else if (data[i] == 1) {
      set(i%width,i/width,color(175,47,154));
    } else if (data[i] == 2) {
      set(i%width,i/width,color(80,255,0));
    } else if (data[i] == 3) {
      set(i%width,i/width,color(0,246,255));
    }
  }*/
  
  //physics
  
  //y
  if (three && !jump && grounded) {
    velY = maxJumpVel;
    grounded = false;
    jump = true;
  }
  if (jump && !three) {
    if (velY > minJumpVel) {
      velY = minJumpVel;
    }
    jump = false;
  }
  //x
  if (xAxis < -0.5f) {
    velX -= 0.4f;
    if (abs(velX) > abs(maxVelX)) {
      velX = -maxVelX;
    }
  }
  if (xAxis > 0.5f) {
    velX += 0.4f;
    if (abs(velX) > abs(maxVelX)) {
      velX = maxVelX;
    }
  }
  //friction
  velX *= .95f;
  //gravity
  velY -= 14f*deltaTime;
  //raycast
  DoCollisions();
  /*for (int i=0;i<11;i++) {
    RayCastHit v;
    RayCastHit h;
    if (velY < 0) {
      //bottom
      v = VRayCast(round(x-pWidth/2+pWidth*i/10),round(y+pHeight/2),floor(velY));
    } else {
      //top
      v = VRayCast(round(x-pWidth/2+pWidth*i/10),round(y-pHeight/2),ceil(velY));
    }
    if (velX < 0) {
      //Left
      h = HRayCast(round(x-pWidth/2),round(y-pHeight/2+pHeight*i/10),floor(velX));
    } else {
      //Right
      h = HRayCast(round(x+pWidth/2),round(y-pHeight/2+pHeight*i/10),ceil(velX));
    }
    if (v != null) {
      velY = 0;
      if (v.dir == direction.TOP) {
        y = v.y+pHeight/2;
        jump = false;
      } else if (v.dir == direction.BOTTOM) {
        y = v.y-pHeight/2;
        grounded = true;
        jump = false;
      }
      
    }
    if (h != null) {
      velX = 0;
      if (h.dir == direction.LEFT) {
        x = h.x+pWidth/2;
      } else if (h.dir == direction.RIGHT) {
        x = h.x-pWidth/2;
      }
      
    }
  }*/
  
  x += velX;
  y -= velY;
  
  //draw
  image(level,0,0);
  fill(54,193,156);
  rect(x-pWidth/2,y-pHeight/2,pWidth,pHeight);
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
  println("dead");
}