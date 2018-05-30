public enum SpriteType {
  animated,
  still
}

class Sprite {
  SpriteType type;
  PImage myImage;
  
  //animation
  int xF;
  int yF;
  int speed;
  int ticksSinceChange = 0;
  int frame = 0;
  
  int x;
  int y;
  int w;
  int h;
  public Sprite(String _path,int _x, int _y, int _w, int _h) {
    myImage = loadImage(_path);
    if (myImage == null) {
      print("Image loading failed, check the file path\n");
    }
    type = SpriteType.still;
    x = _x;
    y = _y;
    w = _w;
    h = _h;
  }
  public Sprite(String _path,int _x, int _y) {
    myImage = loadImage(_path);
    if (myImage == null) {
      print("Image loading failed, check the file path\n");
    }
    type = SpriteType.still;
    x = _x;
    y = _y;
    w = myImage.width;
    h = myImage.height;
  }
  public Sprite(String _path,int _xF,int _yF,int _speed,int _x, int _y, int _w, int _h) {
    myImage = loadImage(_path);
    if (myImage == null) {
      print("Image loading failed, check the file path\n");
    }
    type = SpriteType.animated;
    xF = _xF;
    yF = _yF;
    speed = _speed;
    x = _x;
    y = _y;
    w = _w;
    h = _h;
  }
  public Sprite(String _path,int _xF,int _yF,int _speed,int _x, int _y) {
    myImage = loadImage(_path);
    if (myImage == null) {
      print("Image loading failed, check the file path\n");
    }
    type = SpriteType.animated;
    xF = _xF;
    yF = _yF;
    speed = _speed;
    x = _x;
    y = _y;
    w = myImage.width/xF;
    h = myImage.height/yF;
  }
  public void render() {
    if (type == SpriteType.still) {
      f.temp.image(myImage,x,y,w,h);
    } else {
      f.temp.image(myImage.get(myImage.width/xF*(frame%xF),myImage.height/yF*(floor(frame/xF)),myImage.width/xF,myImage.height/yF),x,y,w,h);
    }
  }
  public void incrementFrame() {
    if (type == SpriteType.animated) {
      if (ticksSinceChange >= speed) {
        ticksSinceChange = 0;
        frame++;
      } else {
        ticksSinceChange++;
      }
      if (frame >= xF*yF) {
        frame = 0;
      }
    }
  }
}
