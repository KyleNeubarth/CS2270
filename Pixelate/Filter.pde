class Filter {
  public PGraphics temp;
  PGraphics dest;
  
  public Filter(int x1,int y1, int x2, int y2) {
    temp = createGraphics(x1,y1);
    dest = createGraphics(x2,y2);
    ratio = width/float(dest.width);
  }
  
  public void execute() {
    dest.beginDraw();
    dest.background(255);
    
    dest.image(temp,0,0,dest.width,dest.height);
    
    dest.endDraw();
    dest.loadPixels();
    
    noStroke();
    for (int i=0;i<dest.height;i++) {
      for (int j=0;j<dest.width;j++) {
        fill(dest.pixels[dest.width*i+j]);
        rect(j*ratio,i*ratio,ratio,ratio);
      }
    }
  }
  public void setRes(int num) {
    dest = createGraphics(num,num);
    ratio = width/float(dest.width);
  }
  public void debug() {
    image(temp,0,0,width,height);
  }
}
