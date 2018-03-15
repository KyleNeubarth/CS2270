import org.gamecontrolplus.gui.*;
import org.gamecontrolplus.*;
import net.java.games.input.*;

ControlIO control;
//Configuration config;
ControlDevice gpad;

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

public void setup() {
  size(400, 240);
  
  // Initialise the ControlIO
  control = ControlIO.getInstance(this);
  // Find a device that matches the configuration file
  gpad = control.getMatchedDevice("snes");
  if (gpad == null) {
    println("No suitable device configured");
    System.exit(-1); // End the program NOW!
  }
  
}

public void draw() {
  
  background(255, 246, 196);
  
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
  
  
  textAlign(CENTER,CENTER);
  
  ellipse(width/4+xAxis*30,height/2+yAxis*30,10,10);
  
  fill(255);
  
  if (zero) {
    ellipse(width*.8,height*.5,15,15);
  } else {
    ellipse(width*.8,height*.5,10,10);
  }
  if (one) {
    ellipse(width*.75,height*.55,15,15);
  } else {
    ellipse(width*.75,height*.55,10,10);
  }
  if (two) {
    ellipse(width*.75,height*.45,15,15);
  } else {
    ellipse(width*.75,height*.45,10,10);
  }
  if (three) {
    ellipse(width*.7,height*.5,15,15);
  } else {
    ellipse(width*.7,height*.5,10,10);
  }
  if (four) {
    ellipse(width*.4,height*.1,15,15);
  } else {
    ellipse(width*.4,height*.1,10,10);
  }
  if (five) {
    ellipse(width*.6,height*.1,15,15);
  } else {
    ellipse(width*.6,height*.1,10,10);
  }
  if (six) {
    ellipse(width*.45,height*.6,15,15);
  } else {
    ellipse(width*.45,height*.6,10,10);
  }
  if (seven) {
    ellipse(width*.55,height*.6,15,15);
  } else {
    ellipse(width*.55,height*.6,10,10);
  }
  /*fill(0);
  text("0",width/2,height/2);*/
}