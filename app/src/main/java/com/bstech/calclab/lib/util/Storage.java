package com.bstech.calclab.lib.util;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

import com.bstech.calclab.lib.log.Log;

import android.content.Context;

public class Storage
{
    private static Context m_context = null;
    
    // METHODS
    
    public static void setContext(final Context context) { m_context = context; }
    
    public static void write(final String file, final String data)
    { 
        try {
            FileOutputStream fos = m_context.openFileOutput(file, Context.MODE_PRIVATE);
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(data);
            oos.close();
        }
        catch (java.io.FileNotFoundException e) { Log.e("" + e); }
        catch (java.io.IOException e) { Log.e("" + e); }
    }
    
    
    public static String read(final String file)
    {
        String data = null;
        
        try
        {
            FileInputStream   fis  = m_context.openFileInput(file);
            ObjectInputStream ois  = new ObjectInputStream(fis);
            
            data = (String)ois.readObject();
        }
        catch (java.io.FileNotFoundException e) { Log.e("" + e); }
        catch (java.io.IOException e) { Log.e("" + e); }
        catch (ClassNotFoundException e) { Log.e("" + e); }
        
        return data;
    }
    
    
    public static void erase(String file)
    {
        write(file, "");
    }

} // class Storage
