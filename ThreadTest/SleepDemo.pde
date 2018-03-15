class SleepDemo implements Runnable
{
    SleepDemo(String _name) {
      name = _name;
    }
    Thread t;
    String name;
    public void run()
    {
        for (int i = 0; i < 4; i++)
        {
            System.out.println(Thread.currentThread().getName()
                                                   + "  " + i);
            try
            {
                // thread to sleep for 1000 milliseconds
                Thread.sleep(1000);
            }
 
            catch (Exception e)
            {
                System.out.println(e);
            }
        }
    }
}