package com.bstech.calclab.lib.util;


public class StackTraceInfo
{
    private static final int CLIENT_CODE_STACK_INDEX;

    static
    {
        int i = 0;
        for (StackTraceElement ste: Thread.currentThread().getStackTrace())
        {
            i++;
            if (ste.getClassName().equals(StackTraceInfo.class.getName()))
            {
                break;
            }
        }
        CLIENT_CODE_STACK_INDEX = i;
    }

    
    public static String getCurrentMethodName()
    {
        return getCurrentMethodName(1);
    }

    
    private static String getCurrentMethodName(int offset)
    {
        return Thread.currentThread().getStackTrace()[CLIENT_CODE_STACK_INDEX + offset].getMethodName();
    }

    
    public static String getCurrentClassName()
    {
        return getCurrentClassName(1);
    }

    
    private static String getCurrentClassName(int offset)
    {
    return Thread.currentThread().getStackTrace()[CLIENT_CODE_STACK_INDEX + offset].getClassName();
    }

    
    public static String getCurrentFileName()
    {
        return getCurrentFileName(1);
    }

    
    private static String getCurrentFileName(int offset)
    {
        String filename = Thread.currentThread().getStackTrace()[CLIENT_CODE_STACK_INDEX + offset].getFileName();
        int lineNumber = Thread.currentThread().getStackTrace()[CLIENT_CODE_STACK_INDEX + offset].getLineNumber();

        return filename + ":" + lineNumber;
    }

    
    public static String getInvokingMethodName()
    {
        return getInvokingMethodName(2); 
    }

    
    private static String getInvokingMethodName(int offset)
    {
        return getCurrentMethodName(offset + 1);
    }

    
    public static String getInvokingClassName()
    {
        return getInvokingClassName(2); 
    }

    
    private static String getInvokingClassName(int offset)
    {
        return getCurrentClassName(offset + 1);
    }

    
    public static String getInvokingFileName()
    {
        return getInvokingFileName(2); 
    }

    
    private static String getInvokingFileName(int offset)
    {
        return getCurrentFileName(offset + 1);
    }

    
    public static String getCurrentMethodNameFqn()
    {
        return getCurrentMethodNameFqn(1);
    }

    
    private static String getCurrentMethodNameFqn(int offset)
    {
        String currentClassName = getCurrentClassName(offset + 1);
        String currentMethodName = getCurrentMethodName(offset + 1);

        return currentClassName + "." + currentMethodName ;
    }

    
    public static String getCurrentFileNameFqn()
    {
        String CurrentMethodNameFqn = getCurrentMethodNameFqn(1);
        String currentFileName = getCurrentFileName(1);

        return CurrentMethodNameFqn + "(" + currentFileName + ")";
    }

    
    public static String getInvokingMethodNameFqn()
    {
        return getInvokingMethodNameFqn(2);
    }

    
    private static String getInvokingMethodNameFqn(int offset)
    {
        String invokingClassName = getInvokingClassName(offset + 1);
        String invokingMethodName = getInvokingMethodName(offset + 1);

        return invokingClassName + "." + invokingMethodName;
    }


    public static String getInvokingFileNameFqn()
    {
        String invokingMethodNameFqn = getInvokingMethodNameFqn(2);
        String invokingFileName = getInvokingFileName(2);

        return invokingMethodNameFqn + "(" + invokingFileName + ")";
    }

} // class StackTraceInfo
