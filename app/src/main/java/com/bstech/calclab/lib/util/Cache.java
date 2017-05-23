package com.bstech.calclab.lib.util;


import java.io.File;
import android.content.Context;


public class Cache
{

    public static void trim(final Context context)
    {
        try
        {
            File dir = context.getCacheDir();
            if (dir != null && dir.isDirectory())
            {
                deleteDir(dir);
            }
        } catch (Exception e) {}
    }


    private static boolean deleteDir(final File dir)
    {
        if (dir != null && dir.isDirectory())
        {
            String [] children = dir.list();
            for (int i = 0; i < children.length; ++i)
            {
                boolean success = deleteDir(new File(dir, children[i]));
                
                if (!success)
                {
                    return false;
                }
            }
        }
        // The directory is now empty so delete it.
        return dir.delete();
    }

} // class Cache
