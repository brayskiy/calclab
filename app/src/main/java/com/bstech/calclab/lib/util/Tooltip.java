package com.bstech.calclab.lib.util;

import android.content.Context;
import android.widget.Toast;

public class Tooltip
{
    private static boolean m_enabled = false;
    
    // METHODS

    public static void enable(final boolean enabled) { m_enabled = enabled; }

    public static void show(Context context, String msg) {
        if (m_enabled) Toast.makeText(context, msg, Toast.LENGTH_SHORT).show();
    }
    
    public static void show(Context context, int id) {
        if (m_enabled) Toast.makeText(context, id, Toast.LENGTH_SHORT).show();
    }
    
} // class Tooltip
