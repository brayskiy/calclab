package com.bstech.calclab.activity;


import android.app.Activity;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;
import android.widget.TextView;

import com.bstech.calclab.R;


public class About extends Activity
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        
        setContentView(R.layout.about);
        
        TextView appVersion = (TextView)findViewById(R.id.app_ver);
        appVersion.setText(getVersion());
    }

    
    private String getVersion()
    {
        StringBuilder version = new StringBuilder("Version: ");
        try
        {
            PackageInfo pInfo = 
                About.this.getPackageManager().getPackageInfo(About.this.getPackageName(), 0);
            version
            .append(pInfo.versionName)
            .append(" build ")
            .append(Integer.valueOf(pInfo.versionCode).toString());
                
        }
        catch (NameNotFoundException e)
        {}
        
        return version.toString();
    }

    
    @Override
    public void onBackPressed()
    {
        finish();
    }
    
} // class About...
