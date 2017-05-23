package com.bstech.calclab.lib.util;

import android.content.Context;
import android.widget.Toast;

public class Tooltip
{
    private static boolean m_enabled = false;
    private static Context m_context = null;
    
    // METHODS
    
    public static void setContext(final Context context) { m_context = context; }
    public static void enable(final boolean enabled)     { m_enabled = enabled; }
    
    public static void show(String msg)
    {
        if (m_enabled) showOnce(msg);
    }
    
    public static void show(int id)
    {
        if (m_enabled) showOnce(id);
    }

    public static void showOnce(String msg)
    {
        Toast.makeText(m_context, msg, Toast.LENGTH_SHORT).show();
    }
    
    public static void showOnce(int id)
    {
        Toast.makeText(m_context, id, Toast.LENGTH_SHORT).show();
    }
    
} // class Tooltip
