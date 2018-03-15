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
  public void move() {
    x+=velX;
    y+=velY;
    velX*=.95f;
    velY*=.95f;
  }
}

float imageScale = 0.25f;

PImage startImage;
int numImages = 1;
slice[] images;

boolean mouseDown = false;
boolean dragging = false;
slice dragItem;
int mX = 0;
int mY = 0;

void settings() {
  startImage = loadImage("Downwell.png");
  size(floor(startImage.width*imageScale+200),floor(startImage.height*imageScale+200));
}

void setup() {
  images = new slice[100];
  images[0] = new slice(startImage,100,100,0,0);
}
void draw() {
  background(255);
  if (dragging) {
    float targetX = (mouseX-(dragItem.x+dragItem.image.width*imageScale/2));
    float targetY = (mouseY-(dragItem.y+dragItem.image.height*imageScale/2));
    dragItem.x += (targetX)/10;
    dragItem.y += (targetY)/10;
  }
  for (int i=0;i<numImages;i++) {
    image(images[i].image,images[i].x,images[i].y,images[i].image.width*imageScale,images[i].image.height*imageScale);
    images[i].move();
  }
}
void mousePressed() {
  for (int i=0;i<numImages;i++) {
    if (mouseX > images[i].x && mouseX < images[i].x+images[i].image.width*imageScale && mouseY > images[i].y && mouseY <  images[i].y+images[i].image.height*imageScale) {
      dragging = true;
      dragItem = images[i];
      break;
    }
  }
  mouseDown = true;
  mX = mouseX;
  mY = mouseY;
}
void mouseReleased() {
  mouseDown = false;
  if (dragging) {
    dragging = false;
  } else {
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
          SliceV(i,imagePoint);
          i++;
        }
      }
    }
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