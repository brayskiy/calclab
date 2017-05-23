package com.bstech.calclab.lib.util;

import java.util.ArrayList;

public class Debug
{
    public static String printArrayList(ArrayList<?> arrayList)
    {
        StringBuffer buf = new StringBuffer();
        buf.append("[");
        for (int i = 0; i < arrayList.size(); ++i)
        {
            buf.append(arrayList.get(i));
            buf.append(",");
        }
        buf.append("]");
        
        return buf.toString();
    }

} // class Debug
