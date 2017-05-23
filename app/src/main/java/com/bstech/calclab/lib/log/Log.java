package com.bstech.calclab.lib.log;

import com.bstech.calclab.lib.util.StackTraceInfo;


public class Log
{
    private static boolean m_enabled = false;

    // METHODS
    
    public static void init(boolean enabled) { m_enabled = enabled; }
    
    
    public static void e(final String msg)
    {
        if (m_enabled)
        {
            String tag =
                StackTraceInfo.getInvokingFileName() + " [" + 
                StackTraceInfo.getInvokingClassName() + "/" + 
                StackTraceInfo.getInvokingMethodName() + "()]: ";
            android.util.Log.e(tag, msg);
        }
    }
    
    
    public static void e(final String tg, final String msg)
    {
        if (m_enabled)
        {
            String tag =
                StackTraceInfo.getInvokingFileName() + " [" + 
                StackTraceInfo.getInvokingClassName() + "/" + 
                StackTraceInfo.getInvokingMethodName() + "()]: " +
                tg + ": ";
            android.util.Log.e(tag, msg);
        }
    }
    
    
    public static void w(final String msg)
    {
        if (m_enabled)
        {
            String tag =
                StackTraceInfo.getInvokingFileName() + " [" + 
                StackTraceInfo.getInvokingClassName() + "/" + 
                StackTraceInfo.getInvokingMethodName() + "()]: ";
            android.util.Log.w(tag, msg);
        }
    }
    
    
    public static void w(final String tg, final String msg)
    {
        if (m_enabled)
        {
            String tag = 
                StackTraceInfo.getInvokingFileName() + " [" + 
                StackTraceInfo.getInvokingClassName() + "/" + 
                StackTraceInfo.getInvokingMethodName() + "()]: " +
                tg + ": ";
            android.util.Log.w(tag, msg);
        }
    }
    
    
    public static void i(final String msg)
    {
        if (m_enabled)
        {
            String tag =
                StackTraceInfo.getInvokingFileName() + " [" + 
                StackTraceInfo.getInvokingClassName() + "/" + 
                StackTraceInfo.getInvokingMethodName() + "()]: ";
            android.util.Log.i(tag, msg);
        }
    }
    
    
    public static void i(final String tg, final String msg)
    {
        if (m_enabled)
        {
            String tag = 
                StackTraceInfo.getInvokingFileName() + " [" + 
                StackTraceInfo.getInvokingClassName() + "/" + 
                StackTraceInfo.getInvokingMethodName() + "()]: " +
                tg + ": ";
            android.util.Log.i(tag, msg);
        }
    }
    
    
    public static void d(final String msg)
    {
        if (m_enabled)
        {
            String tag =
                StackTraceInfo.getInvokingFileName() + " [" + 
                StackTraceInfo.getInvokingClassName() + "/" + 
                StackTraceInfo.getInvokingMethodName() + "()]: ";
            android.util.Log.d(tag, msg);
        }
    }
    
    
    public static void d(final String tg, final String msg)
    {
        if (m_enabled)
        {
            String tag = 
                StackTraceInfo.getInvokingFileName() + " [" + 
                StackTraceInfo.getInvokingClassName() + "/" + 
                StackTraceInfo.getInvokingMethodName() + "()]: " +
                tg + ": ";
            android.util.Log.d(tag, msg);
        }
    }
    
    
    public static void v(final String msg)
    {
        if (m_enabled)
        {
            String tag =
                StackTraceInfo.getInvokingFileName() + " [" + 
                StackTraceInfo.getInvokingClassName() + "/" + 
                StackTraceInfo.getInvokingMethodName() + "()]: ";
            android.util.Log.v(tag, msg);
        }
    }
    
    
    public static void v(final String tg, final String msg)
    {
        if (m_enabled)
        {
            String tag = 
                StackTraceInfo.getInvokingFileName() + " [" + 
                StackTraceInfo.getInvokingClassName() + "/" + 
                StackTraceInfo.getInvokingMethodName() + "()]: " +
                tg + ": ";
            android.util.Log.v(tag, msg);
        }
    }

} // class Log
