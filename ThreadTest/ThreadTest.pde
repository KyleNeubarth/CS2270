 void setup()
{
        Thread t = new Thread(new SleepDemo("1"));
 
        // call run() function
        t.start();
 
        Thread t2 = new Thread(new SleepDemo("2"));
 
        // call run() function
        t2.start();
}