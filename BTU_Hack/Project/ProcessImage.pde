void ProcessImage(PImage img) {
  img.loadPixels();
  float dist;
  for (int i=0;i<img.pixels.length;i++) {
    //blue
    dist = GetDistance(img.pixels[i],color(31,44,89));
    if (dist < 30) {
      data[i] = 3;
      spawnX+=i%level.width;
      spawnY+=i/level.width;
      numPoints++;
      continue;
    }
    //black
    dist = GetDistance(img.pixels[i],color(50,50,50));
    if (dist < 80) {
      data[i] = 0;
      continue;
    }
    //red
    dist = GetDistance(img.pixels[i],color(235,70,70));
    if (dist < 60) {
      data[i] = 1;
      continue;
    }
    //green
    dist = GetDistance(img.pixels[i],color(8,129,124));
    if (dist < 50) {
      data[i] = 2;
      continue;
    }
    //nothing
    data[i] = -1;
  }
  spawnX /= numPoints;
  spawnY /= numPoints;
  die();
}