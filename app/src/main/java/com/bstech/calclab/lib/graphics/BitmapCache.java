package com.bstech.calclab.lib.graphics;


import java.util.HashMap;

import com.bstech.calclab.lib.struct.Point;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;


class LevelOneCache extends HashMap<Point, Bitmap>
{
    private static final long serialVersionUID = -6006987136088890344L;    
}


public class BitmapCache
{    
    // MEMBERS
    
    private static HashMap<String, LevelOneCache> cache = new HashMap<String, LevelOneCache>();
    
    // METHODS
    
    public static void reset()
    {   
        cache.clear();
    }
    
    
    public static Bitmap get(final String key, final Point size, final Resources res, final Context context)
    {
        Bitmap bi = null;
        
        LevelOneCache cc = cache.get(key);
        
        if (cc == null)
        {
            bi = getBitmap(key, size, res, context);
            LevelOneCache c  = new LevelOneCache();
            c.put(size, bi);
            cache.put(key, c);
            
            //Log.i("Created new bitmap:", key);
        }
        else
        {
            bi = cc.get(size);
            
            if (bi == null)
            {
                bi = getBitmap(key, size, res, context);
                cc.put(size, bi);
                
                //Log.i("Created new bitmap:", key);
            }
            
            //Log.i("Used bitmap from cache:", key);
        }
        return bi;
    }

        
    private static Bitmap getBitmap(final String key, final Point size, final Resources res, final Context context)
    {
        try
        {
            int id = res.getIdentifier(key, "drawable", context.getPackageName());

            Bitmap src = BitmapFactory.decodeResource(res, id);

            Matrix bitmapScale = new Matrix();
            bitmapScale.postScale(
                (float)size.x / (float) src.getWidth(),
                (float)size.y / (float) src.getHeight());
            Matrix mat = bitmapScale;

            return Bitmap.createBitmap(src, 0, 0, src.getWidth(), src.getHeight(), mat, true);
        }
        catch (Exception e)
        {
            return null;
        }
        //return bi;
    }
    
} // class BitmapCache
