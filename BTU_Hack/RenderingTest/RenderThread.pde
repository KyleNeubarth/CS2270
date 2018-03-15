class RenderThread implements Runnable {
  Capture camel;
  int num = 0;
  public RenderThread(Capture _cam) {
    camel = _cam;
  }
  public void run() { 
    while (true) {
      //set(0, 0, cam);
      try {
        Thread.sleep(100);
        println("waiting"+num);
        num++;
      } catch(Exception e) {
        System.out.println(e);
      }
    }
  }
}