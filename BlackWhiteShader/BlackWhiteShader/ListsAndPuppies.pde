class TaskList {
  Node first;
  public TaskList() {}
  void Add(String _type,Object _obj) {
    Node newNode = new Node(_type,_obj);
    boolean looking = true;
    if (first == null) {
      first = newNode;
      return;
    }
    Node suspect = first;
    while(looking) {
      if (suspect == null) {
        suspect = newNode;
        return;
      }
      suspect = suspect.next;
    }
  }
  void ReadTask() {
    switch(first.contains) {
      case "move":
        
        break;
    }
  }
}
class Node {
  String contains;
  Node next;
  Object obj;
  public Node(String _type,Object _obj) {
    contains = _type;
    obj = _obj;
  }
}
class Move {
  int x;
  int y;
  int t;
}