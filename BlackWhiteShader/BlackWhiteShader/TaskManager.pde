/*class TaskManager {
  ArrayList<Task> tasks;
  int imageID;
  public TaskManager(int id) {
    tasks = new ArrayList<Task>();
    imageID = id;
  }
  void DoTask() {
    switch(tasks.get(0).name) {
      case "move":
        images.get(imageID).x += (tasks.get(0).moveToX - tasks.get(0).startX)/tasks.get(0).time*deltaTime;
        images.get(imageID).y += (tasks.get(0).moveToY - tasks.get(0).startY)/tasks.get(0).time*deltaTime;
        if ((tasks.get(0).moveToX-images.get(imageID).x > 0) != tasks.get(0).dirX) {
          images.get(imageID).x = tasks.get(0).moveToX;
          images.get(imageID).y = tasks.get(0).moveToY;
          tasks.remove(0);
        }
        break;
      case "wait":
        break;
    }
  }
}
class Task {
  String name;
  int moveToX;
  int moveToY;
  int startX;
  int startY;
  boolean dirX;
  boolean dirY;
  float time;
  public Task(int x,int y,int t,int sX,int sY) {
    name = "move";
    moveToX = x;
    moveToY = y;
    startX = sX;
    startY = sY;
    dirX = (moveToX-startX > 0)? true : false;
    dirX = (moveToY-startY > 0)? true : false;
    time = t;
  }
  public Task(int t) {
    name = "wait";
    time = t;
  }
}*/

class TaskManager {
  ArrayList<Task> tasks;
  image target;
  Thread thread;
  public TaskManager(image _target) {
    tasks = new ArrayList<Task>();
    target = _target;
    thread = new Thread(new TaskThread("",this));
    thread.start();
  }
}
class Task {
  String name;
  int[] args;
  public Task(String _name,int[] _args) {
    name = _name;
    args = new int[_args.length];
    for (int i=0;i<_args.length;i++) {
      args[i] = _args[i];
    }
  }
}
int Sign(int x) {
  if (x > 0) {
    return 1;
  } else if (x < 0) {
    return -1;
  } else {
    return 0;
  }
}