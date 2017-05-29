package com.bstech.calclab.models;

import android.content.Context;
import android.content.SharedPreferences;

import com.google.gson.Gson;

/**
 * Created by brayskiy on 5/24/17.
 */

public class GraphData {
    private static final String GRAPH_DATA = "graph_data_";
    private static final String GRAPH_TYPE = "graph_type";

    private static Context mContext = null;

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

    public static void init(Context context) { mContext = context; }

    public String toJson() {
        return new Gson().toJson(this, GraphData.class);
    }

    public static GraphData fromJson(String src) {
        return new Gson().fromJson(src, GraphData.class);
    }

    public static void writeType(int type) {
        SharedPreferences sharedPreferences = mContext.getSharedPreferences(
                mContext.getPackageName(), Context.MODE_PRIVATE);
        sharedPreferences.edit().putInt(GRAPH_TYPE, type).apply();
    }

    public static int readType() {
        SharedPreferences sharedPreferences = mContext.getSharedPreferences(
                mContext.getPackageName(), Context.MODE_PRIVATE);
        return sharedPreferences.getInt(GRAPH_TYPE, -1);
    }

    public static void writeData(int type, String data) {
        SharedPreferences sharedPreferences = mContext.getSharedPreferences(
                mContext.getPackageName(), Context.MODE_PRIVATE);
        sharedPreferences.edit().putString(GRAPH_DATA + type, data).apply();
    }

    public static String readData(int type) {
        SharedPreferences sharedPreferences = mContext.getSharedPreferences(
                mContext.getPackageName(), Context.MODE_PRIVATE);
        return sharedPreferences.getString(GRAPH_DATA + type, null);
    }
}
