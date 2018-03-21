ArrayList<image> images;
int[][] nextFrame;

boolean drag = false;
int dragX;
int dragY;
float coeff;
float lCoeff;

int firstTime;
int lastTime;
int deltaTime = 0;

boolean moving = false;
boolean left = false;
boolean pos = false;
void setup() {
  //nextFrame is the next frame, which gets made and then pasted over the previous
  //If I were a stronger man I would rename it
  nextFrame = new int[width][height];
  size(350,350);
  
  images = new ArrayList<image>();
  images.add(new image(0,0,50,height-50));
  images.add(new image(0,height-50,width-50,50));
  images.add(new image(width-50,50,50,height-50));
  images.add(new image(50,0,width-50,50));
  images.add(new image("Text1.png",70,90));
  images.add(new image("Text3.png",70,190));
  images.add(new image("Text3.png",70,390));
  images.add(new image("Text2.png",70,490));
  
  lastTime = millis();
}
void draw() {
  
  if (!moving && floor(random(1)*200)==199) {
    images.add(new image("leaf.png",floor(random(1)*width)-100,-17));
  }
  
  deltaTime = millis()-lastTime;
  lastTime = millis();
  coeff = (pos)?-1:1*225*pow(sin((lastTime-firstTime)/2000f),3);
  if (moving) {
    images.get(0).realX += coeff/2*deltaTime/1000f;
    images.get(1).realY -= coeff/2*deltaTime/1000f;
    images.get(2).realX -= coeff/2*deltaTime/1000f;
    images.get(3).realY += coeff/2*deltaTime/1000f;
    
    images.get(6).realY -= coeff/2*deltaTime/1000f/1.5f;
    images.get(7).realY -= coeff/2*deltaTime/1000f;
    
    for (int i=0;i<8;i++) {
      images.get(i).x = round(images.get(i).realX);
      images.get(i).y = round(images.get(i).realY);
    }
    if (!pos &&images.get(7).y == 190) {
      moving = false;
      pos = true;
    }
    if (pos &&images.get(7).y == 490) {
      moving = false;
      pos = false;
    }
  } else {
    lCoeff = 10*pow(sin((lastTime)/1000f),1)+10;
    for (int i=8;i<images.size();i++) {
      images.get(i).realX += lCoeff*deltaTime/1000f;
      images.get(i).realY += 25*deltaTime/1000f;
      images.get(i).x = round(images.get(i).realX);
      images.get(i).y = round(images.get(i).realY);
      if (images.get(i).x > width || images.get(i).y > height) {
        images.remove(i);
        i--;
      }
    }
    
  }
  
  if (drag) {
    images.get(0).x = mouseX-dragX;
    images.get(0).y = mouseY-dragY;
    images.get(0).CheckBounds();
  }
  
  for (int i=0;i<nextFrame.length;i++) {
    for (int j=0;j<nextFrame[0].length;j++) {
      nextFrame[i][j] = 255;
    }
  }
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
  loadPixels();
  for (int i=0;i<pixels.length;i++) {
    int newColor = nextFrame[i%nextFrame.length][i/nextFrame.length];
    pixels[i] = color(newColor,newColor,newColor);
  }
  updatePixels();
}
void mousePressed() {
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
void keyPressed() {
  if (!moving) {
    moving = true;
    firstTime = millis();
  }
}