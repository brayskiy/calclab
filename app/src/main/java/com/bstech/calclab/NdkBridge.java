package com.bstech.calclab;

/**
 * Created by brayskiy on 5/24/17.
 */

public class NdkBridge {

    public static void init() {
        System.loadLibrary("native-lib");
    }

    public static native String runBoaScript(final String script);
}
