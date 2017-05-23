package com.bstech.calclab.fragment;

import android.annotation.SuppressLint;
import android.content.Context;
import android.view.View;
import android.widget.TabHost.TabContentFactory;

@SuppressLint("ValidFragment")
public class DummyFragment implements TabContentFactory
{
    private Context mContext;
 
    public DummyFragment(Context context)
    {
        mContext = context;
    }
 
    @Override
    public View createTabContent(String tag)
    {
        View v = new View(mContext);
        return v;
    }
} // class DummyFragment
