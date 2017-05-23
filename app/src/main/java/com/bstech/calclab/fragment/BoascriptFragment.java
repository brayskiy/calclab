package com.bstech.calclab.fragment;


import java.io.File;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.bstech.calclab.R;
import com.bstech.calclab.TaskType;
import com.bstech.calclab.filemanager.FileManager;
import com.bstech.calclab.GlobalData;
import com.bstech.calclab.lib.io.FIleIO;
import com.bstech.calclab.lib.util.Storage;
import android.annotation.SuppressLint;
import android.app.Fragment;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


public class BoascriptFragment extends Fragment
{    
    private float m_inTextSize  = 18f;
    private float m_outTextSize = 18f;
    
    final private static String DEBUG_TAG           = "BoascriptFragment"; 
    final private static String BOASCRIPT_SAVE_NAME = "boascript_save";
    
    private EditText inText   = null;
    private EditText outText  = null;
    private File     workFile = null;
    
    // METHODS
    
    public BoascriptFragment()
    {
        super();
    }
    
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        if (container == null) return null;
        
        View view = inflater.inflate(R.layout.fragment_source, container, false);
         
        //AdView adViewTopSource = (AdView)view.findViewById(R.id.adViewTopSource);
        //AdRequest adRequest = new AdRequest.Builder().build();
        //adViewTopSource.loadAd(adRequest);
        
        inText = (EditText)view.findViewById(R.id.inputText);
        inText.setTextSize(m_inTextSize);
        
        outText = (EditText)view.findViewById(R.id.outputText);
         outText.setTextSize(m_outTextSize);
              
         if (!inText.getText().toString().isEmpty())
         {
             runScript();
         }
         
         Button button = (Button)view.findViewById(R.id.runButton);
         button.setOnClickListener(new OnClickListener() {
             @SuppressLint("NewApi")
            public void onClick(View view)
             {
                 if (inText.getText().toString().isEmpty()) return;
                 
                 runScript();
             }
         });
         
         Button fileNewButton = (Button)view.findViewById(R.id.fileNew);
         fileNewButton.setOnClickListener(new OnClickListener() {
             public void onClick(View view)
             {
                 inText.setText("");
                 workFile = null;
             }
         });
         
         Button fileOpenButton = (Button)view.findViewById(R.id.fileOpen);
         fileOpenButton.setOnClickListener(new OnClickListener() {
             public void onClick(View view)
             {
                 Intent intent = new Intent(getActivity(), FileManager.class);
                 intent.putExtra("requestCode", FileManager.FILE_OPEN);
                 startActivityForResult(intent, FileManager.FILE_OPEN);
             }
         });
         
         Button fileSaveButton = (Button)view.findViewById(R.id.fileSave);
         fileSaveButton.setOnClickListener(new OnClickListener() {
             public void onClick(View view)
             {
                 if (workFile != null)
                 {
                     FIleIO.write(workFile, inText.getText().toString());
                 }
             }
         });
         
         Button fileSaveAsButton = (Button)view.findViewById(R.id.fileSaveAs);
         fileSaveAsButton.setOnClickListener(new OnClickListener() {
             public void onClick(View view)
             {
                 Intent intent = new Intent(getActivity(), FileManager.class);
                 intent.putExtra("requestCode", FileManager.FILE_SAVE);
                 if (workFile != null)
                 {
                     intent.putExtra("workFile", workFile.getName());
                 }
                 startActivityForResult(intent, FileManager.FILE_SAVE);
             }
         });
         
         Button inputZoomInButton = (Button)view.findViewById(R.id.inputZoomIn);
         inputZoomInButton.setOnClickListener(new OnClickListener() {
             public void onClick(View view)
             {
                 inText.setTextSize(m_inTextSize *= 1.2f);
             }
         });
         
         Button inputZoomOutButton = (Button)view.findViewById(R.id.inputZoomOut);
         inputZoomOutButton.setOnClickListener(new OnClickListener() {
             public void onClick(View view)
             {
                 inText.setTextSize(m_inTextSize /= 1.2f);
             }
         });
         
         Button resultClearButton = (Button)view.findViewById(R.id.resultClear);
         resultClearButton.setOnClickListener(new OnClickListener() {
             public void onClick(View view)
             {
                 outText.setText("");
             }
         });
         
         Button outputZoomInButton = (Button)view.findViewById(R.id.outputZoomIn);
        outputZoomInButton.setOnClickListener(new OnClickListener() {
            public void onClick(View view)
            {
                outText.setTextSize(m_outTextSize *= 1.2f);
            }
        });
        
        Button outputZoomOutButton = (Button)view.findViewById(R.id.outputZoomOut);
        outputZoomOutButton.setOnClickListener(new OnClickListener() {
            public void onClick(View view)
            {
                outText.setTextSize(m_outTextSize /= 1.2f);
            }
        });
         
         return view;
    }

    
    private void runScript()
    {
        StringBuilder in = new StringBuilder();
        in.append(TaskType.BOA_SCRIPT);
        in.append("@");
        in.append(inText.getText().toString());
        in.append("@2@3@4@5@6@7@8@9");
     
        String res = GlobalData.mainActivity.runBoaScript(in.toString());

        if (res == null) return;
        
        try
        {
            JSONArray json = new JSONObject(res).getJSONArray("items");
        
            Log.d("json.length", "" + json.length());
            
            for (int i = 0; i < json.length(); ++i)
            {
                JSONObject item = json.getJSONObject(i);        
        
                String tag = item.getString("tag");
                
                if (tag.equals("calc"))
                {
                    StringBuilder out = new StringBuilder();
                    out.append(outText.getText().toString());
                    out.append(item.getString("msg"));
                    outText.setText(out.subSequence(0, out.length()));
                }
                else if (tag.equals("error"))
                {
                    final String msg = item.getString("msg");
                    Log.e("JNI ERROR", msg);
                    Toast.makeText(GlobalData.context, msg, Toast.LENGTH_LONG).show();
                    break;
                }
                else if (tag.equals("debug"))
                {
                    final String msg = item.getString("msg");
                    Log.d("JNI DEBUG", msg);
                }
            }
        }
        catch (JSONException e)
        {
            Log.e("JSON Parser", "Error parsing data " + e.toString());
        }
    }
    

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        switch (requestCode)
        {
        case FileManager.FILE_OPEN:
            {
                switch (resultCode)
                {
                case FileManager.RESULT_OK:
                    {
                        if ((data != null) && data.hasExtra("filePath"))
                        {
                            File file = new File(data.getExtras().getString("filePath"));
                            inText.setText(FIleIO.read(file));
                            workFile = file;
                        }
                    }
                    break;
                    
                case FileManager.RESULT_FAIL:
                    {
                    
                    }
                    break;
                } // switch (resultCode)
            }
            break;
        
        case FileManager.FILE_SAVE:
            {
                switch (resultCode)
                {
                case FileManager.RESULT_OK:
                    {
                        if ((data != null) && data.hasExtra("filePath"))
                        {
                            File file = new File(data.getExtras().getString("filePath"));
                            if (FIleIO.write(file, inText.getText().toString()))
                            {
                                workFile = file;
                            }
                            else
                            {
                                Toast.makeText(getActivity(), "Can't write file", Toast.LENGTH_SHORT)
                                .show();
                            }
                        }
                    }
                    break;
                    
                case FileManager.RESULT_FAIL:
                    {
                    
                    }
                    break;
                } // switch (resultCode)
            }
            break;
            
        default:
            {
                Log.e(DEBUG_TAG, "Wrong requestCode = " + requestCode);
            }
            break;
            
        } // switch (requestCode)
    } 

    
    @Override
    public void onResume()
    {
        super.onResume();
        
        Log.i("BoascriptFragment", "onResume");

        String text = Storage.read(BOASCRIPT_SAVE_NAME);
        
        if ((text != null) && !text.isEmpty())
        {
            inText.setText(text);
        }
        
        //CharSequence res = out.subSequence(0, out.length());    
         //outText.setText(res);
    }
    
    @Override
    public void onStart()
    {
        super.onStart();
        
        Log.i("BoascriptFragment", "onStart");
    }
    
    
    @Override
    public void onStop()
    {
        Log.i("BoascriptFragment", "onStop");

        Storage.write(BOASCRIPT_SAVE_NAME, inText.getText().toString());
        
        super.onStop();
    }   
 
} // class SourceFragment
