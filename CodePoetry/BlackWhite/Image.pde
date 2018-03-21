class image {
  String type;
  PImage myImage;
  
  //animations only
  int xF;
  int yF;
  int speed;
  int ticksSinceChange = 0;
  int frame = 0;
  
  int x;
  int y;
  float realX;
  float realY;
  int w;
  int h;
  //static image
  public image(String _path,int _x, int _y, int _w, int _h) {
    myImage = loadImage(_path);
    if (myImage == null) {
      print("Image loading failed, check the file path\n");
      type = "rect";
    } else {
      type = "static";
    }
    x = _x;
    y = _y;
    realX = x;
    realY = y;
    w = _w;
    h = _h;
    CheckBounds();
  }
  public image(String _path,int _x, int _y) {
    myImage = loadImage(_path);
    if (myImage == null) {
      print("Image loading failed, check the file path\n");
      type = "rect";
    } else {
      type = "static";
      w = myImage.width;
      h = myImage.height;
    }
    x = _x;
    y = _y;
    realX = x;
    realY = y;
    CheckBounds();
  }
  //animation
  public image(String _path,int _xF,int _yF,int _speed,int _x, int _y, int _w, int _h) {
    myImage = loadImage(_path);
    if (myImage == null) {
      print("Image loading failed, check the file path\n");
      type = "rect";
    } else {
      type = "anim";
    }
    xF = _xF;
    yF = _yF;
    speed = _speed;
    x = _x;
    y = _y;
    realX = x;
    realY = y;
    w = _w;
    h = _h;
    CheckBounds();
  }
  public image(String _path,int _xF,int _yF,int _speed,int _x, int _y) {
    myImage = loadImage(_path);
    if (myImage == null) {
      print("Image loading failed, check the file path\n");
      type = "rect";
    } else {
      type = "anim";
      w = myImage.width;
      h = myImage.height;
    }
    xF = _xF;
    yF = _yF;
    speed = _speed;
    x = _x;
    y = _y;
    realX = x;
    realY = y;
    CheckBounds();
  }
  //rectangle
  public image(int _x, int _y, int _w, int _h) {
    type = "rect";
    x = _x;
    y = _y;
    realX = x;
    realY = y;
    w = _w;
    h = _h;
    CheckBounds();
  }
  void DoTick() {
    if (type != "anim") {
      print("Tried to do tick on non animatic image\n");
      return;
    }
    ticksSinceChange++;
    if (ticksSinceChange >= speed) {
      frame++;
      if (frame >= (xF*yF)-1) {
        frame = 0;
      }
      ticksSinceChange = 0;
    }
  }
  void CheckBounds() {
    /*
    int tW;
    int tH;
    if (type == "anim") {
      tW = w/xF;
      tH = h/yF;
    } else {
      tW = w;
      tH = h;
    }
    boolean movedX = false;
    boolean movedY = false;
    if (x < 0) {
      x =0;
      movedX = true;
    }
    if (x+tW > width) {
      x = width-tW;
      if (movedX) {
        print("Image does not fit in canvas width");
      }
    }
    if (y < 0) {
      y = 0;
      movedY = true;
    }
    if (y+tH > height) {
      y = height-tH;
      if (movedY) {
        print("Image does not fit in canvas height");
      }
    }*/
  }
}