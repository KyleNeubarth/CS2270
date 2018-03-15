class slice {
  PImage image;
  float x;
  float y;
  float velX;
  float velY;
  public slice(PImage _image,float _x,float _y,float _velX,float _velY) {
    image = _image;
    x=_x;
    y=_y;
    velX=_velX;
    velY=_velY;
  }
}

float imageScale = 0.25f;

PImage startImage;
int numImages = 1;
slice[] images;

boolean mouseDown = false;
int mX = 0;
int mY = 0;

void settings() {
  startImage = loadImage("Downwell.png");
  //weirdShape.setTexture(weirdShapeTexture);
  size(floor(startImage.width*imageScale+200),floor(startImage.height*imageScale+200));
}

void setup() {
  images = new slice[100];
  images[0] = new slice(startImage,100,100,0,0);
}
void draw() {
  background(255);
  for (int i=0;i<numImages;i++) {
    if (images[i] == null) {
      print(i + " is null; ");
      continue;
    }
    image(images[i].image,images[i].x,images[i].y,images[i].image.width*imageScale,images[i].image.height*imageScale);
    images[i].x += images[i].velX;
    images[i].y += images[i].velY;
  }
}
void mousePressed() {
  //SliceH(0,10);
  mouseDown = true;
  mX = mouseX;
  mY = mouseY;
}
void mouseReleased() {
  if (mouseDown) {
    mouseDown = false;
    if (abs(mouseX-mX) > abs(mouseY-mY)) {
      int point = (mY + mouseY)/2;
      for (int i=0;i<numImages;i++) {
        if (point > images[i].y&&point < images[i].y+images[i].image.height*imageScale) {
          int imagePoint = point-(int)images[i].y;
          SliceH(i,imagePoint);
          i++;
        }
      }
    } else {
      int point = (mX + mouseX)/2;
      for (int i=0;i<numImages;i++) {
        if (point > images[i].x&&point < images[i].x+images[i].image.width*imageScale) {
          int imagePoint = point-(int)images[i].x;
          //line = imagePoint+(int)images[i].x;
          SliceV(i,imagePoint);
          i++;
        }
      }
    }
    /*for (int i=0ds;i<numImages;i++) {
      float side = (mouseY-mY)*images[0].x+(mX-mouseX)*images[0].y+(mouseX*mY-mX*mouseY);
        print(side+"; ");
    }*/
  }
}
void SliceH(int index,int y) {
  y*=1/imageScale;
  PImage first = images[index].image.get(0,0,images[index].image.width,y);
  PImage second = images[index].image.get(0,y,images[index].image.width,images[index].image.height-y);
  
  for (int i=numImages;i>=index+2;i--) {
    images[i] = images[i-1];
  }
  numImages++;
  images[index+1] = new slice(first,images[index].x,images[index].y,0,-0.5f);
  images[index] = new slice(second,images[index].x,images[index].y+y*imageScale,0,0.5f);
}
void SliceV(int index,int x) {
  x*=1/imageScale;
  PImage first = images[index].image.get(0,0,x,images[index].image.height);
  PImage second = images[index].image.get(x,0,images[index].image.width-x,images[index].image.height);
  
  for (int i=numImages;i>=index+2;i--) {
    images[i] = images[i-1];
  }
  numImages++;
  images[index+1] = new slice(first,images[index].x,images[index].y,-0.5f,0);
  images[index] = new slice(second,images[index].x+x*imageScale,images[index].y,0.5f,0);
}