package com.bstech.calclab.models;

import com.google.gson.Gson;

/**
 * Created by brayskiy on 5/24/17.
 */

public class GraphData {
    public int    task       = -1;
    public String function1  = "";
    public String function2  = "";
    public Number xMin       = 0;
    public Number xMax       = 0;
    public Number yMin       = 0;
    public Number yMax       = 0;
    public int    viewWidth  = 0;
    public int    viewHeight = 0;
    public int    densityDpi = 0;
    public int    discrete   = 50;

    public String toJson() {
        return new Gson().toJson(this, GraphData.class);
    }

    public static GraphData fromJson(String src) {
        return new Gson().fromJson(src, GraphData.class);
    }
}
