package com.bstech.calclab.activity;

import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.webkit.WebView;
import android.webkit.WebViewClient;

import com.bstech.calclab.R;


public class Reference extends Activity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        
        final String mimeType = "text/html";
        final String encoding = "UTF-8";
        
        setContentView(R.layout.reference);
        
        WebView reference = (WebView)findViewById(R.id.reference);

        try
        {
            InputStream in = getAssets().open("reference.html");
            byte[] buffer  = new byte[in.available()];
            in.read(buffer);
            in.close();
            
            String html = new String(buffer);
            String enc  = null;
            try
            {
                enc = URLEncoder.encode(html, "UTF-8").replaceAll("\\+", " ");
            }
            catch (UnsupportedEncodingException e)
            {
                enc = html;
                e.printStackTrace();
            }
            //reference.loadData(enc, "text/html; charset=UTF-8", null);
            reference.loadData(enc, mimeType, encoding);
            reference.setWebViewClient(new WebViewClient());
        }
        catch(IOException e)
        {
            Log.d("Reference.onCreate", e.toString());
        }

        //reference.setMovementMethod(new ScrollingMovementMethod());
    }

    
    @Override
    public void onBackPressed()
    {
        finish();
    }
} // class Reference
