ArrayList<image> images;
ArrayList<TaskManager> managers;
int[][] nextFrame;

boolean drag = false;
int dragX;
int dragY;

int lastTime;
int deltaTime = 0;

void setup() {
  nextFrame = new int[width][height];
  size(300,300);
  
  images = new ArrayList<image>();
  images.add(new image(10,10,50,150));
  images.add(new image(10,20,200,15));
  images.add(new image("Hello.png",200,200));
  images.add(new image("stickman_right.png",15,1,5,0,100));
  images.add(new image("tamogachi.png",26,17,50,100,0));
  
  managers = new ArrayList<TaskManager>();
  TaskManager image0 = new TaskManager(images.get(0));
  image0.tasks.add(new Task("wait",new float[]{2}));
  image0.tasks.add(new Task("move",new float[]{100,100,2}));
  image0.tasks.add(new Task("wait",new float[]{1}));
  image0.tasks.add(new Task("move",new float[]{200,200,2}));
  image0.tasks.add(new Task("move",new float[]{200,0,4}));
  
  managers.add(image0);
}

void draw() {
  //get deltaTime
  deltaTime = millis()-lastTime;
  lastTime = millis();
  
  //do all the tasks
  for (int i=0;i<managers.size();i++) {
    managers.get(i).DoTick();
  }
  
  //move selected image
  if (drag) {
    images.get(0).realX = mouseX-dragX;
    images.get(0).realY = mouseY-dragY;
    images.get(0).CheckBounds();
  }
  //turn the coordinate system to ints, for drawing reasons.
  for (int i=0;i<images.size();i++) {
    image temp = images.get(i);
    temp.x = round(temp.realX);
    temp.y = round(temp.realY);
  }
  
  //refresh the new frame so it can be painted
  for (int i=0;i<nextFrame.length;i++) {
    for (int j=0;j<nextFrame[0].length;j++) {
      nextFrame[i][j] = 255;
    }
  }
  //flip pixels for rectangle images
  for (int i=0;i<images.size();i++) {
    if (images.get(i).type == "rect") {
      for (int j=images.get(i).x;j<images.get(i).x+images.get(i).w;j++) {
        for (int k=images.get(i).y;k<images.get(i).y+images.get(i).h;k++) {
          if (!inBounds(j,k)) {
            continue;
          }
          //dark or light?
          if (nextFrame[j][k]>=128) {
            nextFrame[j][k] = 0;
          } else {
            nextFrame[j][k] = 255;
          }
        }
      }
    } else if (images.get(i).type == "static") {
      for (int j=images.get(i).x;j<images.get(i).x+images.get(i).w;j++) {
        for (int k=images.get(i).y;k<images.get(i).y+images.get(i).h;k++) {
          if (!inBounds(j,k)) {
            continue;
          }
          int imageWidth = images.get(i).w;
          //if image pixel is dark, flip pixel on canvas
          color c = images.get(i).myImage.pixels[(k-images.get(i).y)*imageWidth+j-images.get(i).x];
          if (brightness(c) < 128) {
            //dark or light?
            if (nextFrame[j][k]>=128) {
              nextFrame[j][k] = 0;
            } else {
              nextFrame[j][k] = 255;
            }
          }
        }
      }
    } else if (images.get(i).type == "anim") {
      for (int j=images.get(i).x;j<images.get(i).x+images.get(i).w/images.get(i).xF;j++) {
        for (int k=images.get(i).y;k<images.get(i).y+images.get(i).h/images.get(i).yF;k++) {
          if (!inBounds(j,k)) {
            continue;
          }
          //if image pixel is dark, flip pixel on canvas
          int x = (images.get(i).frame%images.get(i).xF)*images.get(i).w/images.get(i).xF+j-images.get(i).x;
          int y = (images.get(i).frame/images.get(i).xF)*images.get(i).h/images.get(i).yF+k-images.get(i).y;
          color c = images.get(i).myImage.pixels[y*images.get(i).w+x];
          if (brightness(c) < 128) {
            //dark or light?
            if (nextFrame[j][k]>=128) {
              nextFrame[j][k] = 0;
            } else {
              nextFrame[j][k] = 255;
            }
          }
        }
      }
      images.get(i).DoTick();
    }
  }
  //actually paste the pixels onto the screen
  loadPixels();
  for (int i=0;i<pixels.length;i++) {
    int newColor = nextFrame[i%nextFrame.length][i/nextFrame.length];
    pixels[i] = color(newColor,newColor,newColor);
  }
  updatePixels(); 
}

void mousePressed() {
  //for each image, are you clicking me?
  //first get the width and height of each, different types of images need to have them computed
  for (int i=0;i<images.size();i++) {
    int realW;
    int realH;
    if (images.get(i).type == "anim") {
      realW = images.get(i).w/images.get(i).xF;
      realH = images.get(i).h/images.get(i).yF;
    } else {
      realW = images.get(i).w;
      realH = images.get(i).h;
    }
    if (mouseX > images.get(i).x && mouseX < images.get(i).x+realW && mouseY > images.get(i).y && mouseY < images.get(i).y+realH) {
      drag = true;
      dragX = mouseX-images.get(i).x;
      dragY = mouseY-images.get(i).y;
      image temp = images.get(i);
      images.remove(i);
      images.add(0,temp);
    }
  }
}

void mouseReleased() {
  drag = false;
}

boolean inBounds(int x,int y) {
  boolean in = true;
  if (x <= 0 || x >= width) {
    in = false;
  }
  if (y <= 0 || y >= height) {
    in = false;
  }
  return in;
}