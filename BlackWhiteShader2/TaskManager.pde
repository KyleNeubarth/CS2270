class TaskManager {
  ArrayList<Task> tasks;
  image target;
  public TaskManager(image _target) {
    tasks = new ArrayList<Task>();
    target = _target;
  }
  public void DoTick() {
    if (tasks.size()==0) {
      return;
    }
    Task t = tasks.get(0);
    switch(t.name) {
      case "move":
        float velX = (t.args[0]-target.realX)/t.args[2];
        float velY = (t.args[1]-target.realY)/t.args[2];
        int dirX = Sign(t.args[0]-target.realX);
        int dirY = Sign(t.args[1]-target.realY);
        target.realX += velX*(deltaTime/1000f);
        target.realY += velY*(deltaTime/1000f);
        t.args[2] -= (deltaTime/1000f);
        //check if we have passed dest
        if (Sign(velX) != dirX & Sign(velY) != dirY) {
          target.realX = t.args[0];
          target.realY = t.args[1];
          tasks.remove(0);
        }
        
        break;
     case "wait":
       t.args[0] -= (deltaTime/1000f);
       if (t.args[0] <= 0) {
         tasks.remove(0);
       }
    }
  }
}
class Task {
  String name;
  float[] args;
  public Task(String _name,float[] _args/*,TaskManager parent*/) {
    //image target = parent.target;
    name = _name;
    //special cases, where args need to be calculated
    /*switch (_name) {
      case "move":
        args = new float[4];
        //copy x and y dest
        args[0] = _args[0];
        args[1] = _args[1];
        //calculate vel
        args[2] = (args[0]-target.realX)/_args[2];
        args[3] = (args[1]-target.realY)/_args[2];
        return;
    }*/
    args = new float[_args.length];
    for (int i=0;i<_args.length;i++) {
      args[i] = _args[i];
    }
  }
}
int Sign(float x) {
  if (x > 0) {
    return 1;
  } else if (x < 0) {
    return -1;
  } else {
    return 0;
  }
}