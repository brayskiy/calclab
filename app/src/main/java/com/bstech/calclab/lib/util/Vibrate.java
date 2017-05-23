package com.bstech.calclab.lib.util;


import android.content.Context;
import android.os.Vibrator;


public class Vibrate
{
    final public static int SHORT = 100;
    final public static int LONG  = 250;
    
    public static void once(Context context, int duration)
    {
        Vibrator v = (Vibrator) context.getSystemService(Context.VIBRATOR_SERVICE);
        v.vibrate(duration);
    }
    
} // class Vibrate
