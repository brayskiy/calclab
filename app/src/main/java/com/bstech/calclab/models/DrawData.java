package com.bstech.calclab.models;

import com.google.gson.Gson;

import java.util.ArrayList;

/**
 * Created by brayskiy on 5/24/17.
 */


public class DrawData {

    public class Item {
        public String tag   = null;
        public String msg   = null;
        public String calc  = null;
        public String error = null;
        public int    x1    = 0;
        public int    x2    = 0;
        public int    y1    = 0;
        public int    y2    = 0;
        public int    color = 0;
    }

    public ArrayList<Item> items;

    public String toJson() {
        return new Gson().toJson(this, DrawData.class);
    }

    public static DrawData fromJson(String src) {
        return new Gson().fromJson(src, DrawData.class);
    }
}
