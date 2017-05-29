package com.bstech.calclab.lib.io;


import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

import com.bstech.calclab.lib.log.Log;


public class FIleIO {
    public static String read(final File file) {
        String retData = null;

        try {
            FileInputStream is   = new FileInputStream(file);
        
            int size = is.available();
            byte [] contents = new byte[size];
            int got = is.read(contents);
            if (got == size) {
                is.close();
                retData = new String(contents);
            }
            else {
                is.close();
                Log.e("Error file reading: " + file.getPath());
            }
        }
        catch (IOException e) { Log.e("" + e); }
        catch (Exception e) { Log.e("" + e); }

        return retData;
    }
    
    
    public static boolean write(final File file, final String data) {
        try {
            FileOutputStream os = new FileOutputStream(file);
            
            byte [] buffer = data.getBytes();
            os.write(buffer, 0, buffer.length);
            os.close();
            return true;
        }
        catch (IOException e) { Log.e("" + e); }
        catch (Exception e) { Log.e("" + e); }

        return false;
    }
} // class FileIO
