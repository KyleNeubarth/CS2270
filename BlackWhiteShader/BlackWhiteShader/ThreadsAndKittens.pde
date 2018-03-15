class TaskThread implements Runnable {
  String name;
  TaskManager manager;
  image target;
  public TaskThread(String _name,TaskManager _m) {
    //target = _image;
    name = _name;
    manager = _m;
    target = manager.target;
  }
  public void run() {
    try {
      //whoops
        while(manager.tasks.size()>0) {
          //manager.DoTask();
          Task task = manager.tasks.get(0);
          switch(task.name) {
            case "move":
              //which direction has the most distance, which can we use as a measure of direction?
              boolean xOrY = (task.args[0]-target.x > task.args[1]-target.y)?true:false;
              int dir = (xOrY)?Sign(task.args[0]-target.x):Sign(task.args[1]-target.y);
              target.x += (float)(task.args[0]-target.x)*deltaTime/task.args[2];
              target.y += (float)(task.args[1]-target.y)*deltaTime/task.args[2];
              print((float)deltaTime/task.args[2]+"\n");
              task.args[2]-=deltaTime;
              int nDir = (xOrY)?Sign(task.args[0]-target.x):Sign(task.args[1]-target.y);
              //if direction has changed,we have passed the target point
              if (dir == -1*nDir || dir == 0 || nDir == 0) {
                print(dir +", "+nDir+";\n");
                target.x = task.args[0];
                target.y = task.args[1];
                manager.tasks.remove(0);
              }
              Thread.sleep(0);
              break;
            case "wait":
              Thread.sleep(task.args[0]);
              manager.tasks.remove(0);
              break;
            case "moveTest":                
              while (task.args[0] > 0) {              
                task.args[0]-=deltaTime;
                target.x++;
                print("new x: "+target.x+"\n");
                print(deltaTime);
                //.suspend();
                Thread.sleep(deltaTime);
              }
              manager.tasks.remove(0);
              break;
          }
        }
        print("I am done\n");
      }
      catch(InterruptedException e) {
        print("ONO");
        e.printStackTrace();
      }
  }
}
/*
  Disjunctive Sylogism: everything else is eliminated, the remaining one must be true
  Modus Podens: p->q, p --> q
  Simplification, p^q --> p
  Addition: p --> pvq
  conjunction: p, q --> p^q
  Resolution: pvq, !qvr --> pvr
*/