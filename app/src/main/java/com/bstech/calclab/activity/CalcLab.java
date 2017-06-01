package com.bstech.calclab.activity;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import android.annotation.SuppressLint;
import android.app.FragmentTransaction;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.WindowManager;
import android.widget.EditText;
import android.widget.TabHost;

import com.bstech.calclab.GlobalData;
import com.bstech.calclab.R;
import com.bstech.calclab.fragment.BoascriptFragment;
import com.bstech.calclab.fragment.DummyFragment;
import com.bstech.calclab.fragment.GraphFragment;
import com.bstech.calclab.lib.log.Log;
import com.bstech.calclab.models.GraphData;

public class CalcLab extends FragmentActivity
{
    // MEMBERS

    final private static String BOASCRIPT = "Boascript";
    final private static String GRAPH     = "Graph";
    
    public TabHost tabHost = null;

    // METHODS

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        GlobalData.mainActivity = CalcLab.this;
        GlobalData.context      = this;
        GlobalData.res          = this.getResources();

        loadFont();

        GraphData.init(this);

        this.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);
        
        tabHost = (TabHost)findViewById(android.R.id.tabhost);
        tabHost.setup();
 
        tabHost.setOnTabChangedListener(new TabHost.OnTabChangeListener()
        {
            @SuppressLint("NewApi")
            @Override
            public void onTabChanged(String tabId)
            {
                android.app.FragmentManager fm = getFragmentManager();
                
                GraphFragment graphFragment = (GraphFragment)fm.findFragmentByTag(GRAPH);
                BoascriptFragment boascriptFragment = (BoascriptFragment)fm.findFragmentByTag(BOASCRIPT);
                
                FragmentTransaction ft = fm.beginTransaction();
 
                if (graphFragment != null)
                {
                    ft.detach(graphFragment);
                }
                
                if (boascriptFragment != null)
                {
                    ft.detach(boascriptFragment);
                }
                
                if (tabId.equalsIgnoreCase(GRAPH))
                { 
                    if (graphFragment == null)
                    {
                        ft.add(R.id.realtabcontent, new GraphFragment(), GRAPH);
                    }
                    else
                    {
                        ft.attach(graphFragment);
                    }
                }
                else if (tabId.equalsIgnoreCase(BOASCRIPT))
                {
                    if (boascriptFragment == null)
                    {
                        ft.add(R.id.realtabcontent, new BoascriptFragment(), BOASCRIPT);
                    }
                    else
                    {
                        ft.attach(boascriptFragment);
                    }
                }
                else
                {
                    Log.w("Unknown Tab");
                }
               
                ft.commit();
            }
        });

        TabHost.TabSpec tabSpecGraph = tabHost.newTabSpec(GRAPH);
        tabSpecGraph.setIndicator(GRAPH, getResources().getDrawable(R.drawable.graph));
        tabSpecGraph.setContent(new DummyFragment(getBaseContext()));
        tabHost.addTab(tabSpecGraph);
        
        TabHost.TabSpec tabSpecBoascript = tabHost.newTabSpec(BOASCRIPT);
        tabSpecBoascript.setIndicator(BOASCRIPT, getResources().getDrawable(R.drawable.boascript));
        tabSpecBoascript.setContent(new DummyFragment(getBaseContext()));
        tabHost.addTab(tabSpecBoascript);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item)
    {
        Log.i("item = " + item.getTitle());
            
        CharSequence it = item.getTitle();

        Log.i("title = " + it.toString());
        
        if (it.equals(getString(R.string.SETTINGS)))
        {
            //Intent intent = new Intent(MainActivity.this, Options.class);
            //startActivity(intent);
        }
        else if (it.equals(getString(R.string.REFERENCE)))
        {
            startActivity(new Intent(CalcLab.this, Reference.class));
        }
        else if (it.equals(getString(R.string.TEST)))
        {
            try
            {
                InputStream is = getResources().openRawResource(R.raw.sample1);
                int size = is.available();
                byte [] contents = new byte[size];
                int got = is.read(contents);
                if (got == size)
                {
                    String in = new String(contents);
                    final EditText inText = (EditText)findViewById(R.id.inputText);
                    inText.setText(in);
                }
                else
                {
                    Log.e("Error file reading");
                }
            }
            catch (Exception e)
            {
                Log.e("" + e);
            }
        }
        else if (it.equals(getString(R.string.ABOUT)))
        {
            startActivity(new Intent(this, About.class)); 
        }
        else if (it.equals(getString(R.string.EXIT)))
        {
            // closing Entire Application
            android.os.Process.killProcess(android.os.Process.myPid());
            Editor editor = getSharedPreferences("clear_cache", Context.MODE_PRIVATE).edit();
            editor.clear();
            editor.commit();
            
            finish();
        }
        
        return false;
    }

    @Override
    public void onBackPressed() {
    }

    private void loadFont() {
        try {
            InputStream is = getResources().openRawResource(R.raw.plxtnd5);
            FileOutputStream fos = openFileOutput("plxtnd5.fnt", Context.MODE_PRIVATE);
            byte [] contents = new byte[4 * 1024];
            while (is.read(contents) > 0) {
                fos.write(contents);
            }
            is.close();
            fos.close();
        }
        catch (FileNotFoundException e) {Log.e("" + e); }
        catch (IOException e) {Log.e("" + e); }
        catch (Exception e) {Log.e("" + e); }
    }
        
} // class CalcLab
