class droplet {
  public int x;
  public int y;
  public droplet() {
    x = floor(random(width));
    y = 0;
  }
}

ArrayList<droplet> drops = new ArrayList<droplet>();
ArrayList<droplet> farDrops = new ArrayList<droplet>();

public void DoRainTick() {
  for (int i=0;i<drops.size();i++) {
    drops.get(i).y += 19 + random(1)*2;
    if (drops.get(i).y > height) {
      drops.remove(i);
      i--;
    }
  }
  for (int i=0;i<farDrops.size();i++) {
    farDrops.get(i).y += 19 + random(1)*2;
    if (farDrops.get(i).y > height) {
      farDrops.remove(i);
      i--;
    }
  }
  if (random(1) < .9f) {
    drops.add(new droplet());
  }
  if (random(1) < .9f) {
    farDrops.add(new droplet());
  }
}
public void DoRainDraw() {
  f.temp.noStroke();
  f.temp.fill(66, 134, 244);
  for (int i=0;i<drops.size();i++) {
    droplet d = drops.get(i);
    f.temp.rect(d.x,d.y,5,10);
  }
  f.temp.fill(27, 56, 102);
  for (int i=0;i<farDrops.size();i++) {
    droplet d = farDrops.get(i);
    f.temp.rect(d.x,d.y,3,5);
  }
}
