package com.bstech.calclab.lib.util;


public class ThreadUtil
{
    final public static void sleep(int mSec)
    {
        try
        {
            Thread.sleep(mSec);
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
        }
    }
    
} // class ThreadUtil
