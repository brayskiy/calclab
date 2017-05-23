package com.bstech.calclab.lib.io;


import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

import com.bstech.calclab.lib.log.Log;


public class FIleIO
{
    public static String read(final File file)
    {        
        try
        {
            FileInputStream is   = new FileInputStream(file);
        
            int size = is.available();
            byte [] contents = new byte[size];
            int got = is.read(contents);
            if (got == size)
            {
                is.close();
                return new String(contents);
            }
            else
            {
                is.close();
                Log.e("FileIO.read", "Error file reading: " + file.getPath());
                return null;
            }
        }
        catch (Exception e) 
        {
            Log.e("FileIO.read", "Exception");
        }
        return null;
    }
    
    
    public static boolean write(final File file, final String data)
    {        
        try
        {
            FileOutputStream os = new FileOutputStream(file);
            
            byte [] buffer = data.getBytes();
            os.write(buffer, 0, buffer.length);
            os.close();
            return true;
        }
        catch (IOException e) 
        {
            Log.e("FileIO.write", "Exception");
            return false;
        }
    }
} // class FileIO
