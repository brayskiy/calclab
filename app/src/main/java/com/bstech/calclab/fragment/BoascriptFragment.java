package com.bstech.calclab.fragment;


import java.io.File;

import com.bstech.calclab.NdkBridge;
import com.bstech.calclab.R;
import com.bstech.calclab.TaskType;
import com.bstech.calclab.filemanager.FileManager;
import com.bstech.calclab.GlobalData;
import com.bstech.calclab.lib.io.FIleIO;
import com.bstech.calclab.lib.log.Log;
import com.bstech.calclab.lib.util.Storage;
import com.bstech.calclab.models.DrawData;
import com.bstech.calclab.models.GraphData;

import android.annotation.SuppressLint;
import android.app.Fragment;
import android.content.Intent;
import android.os.Bundle;
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
        GraphData data = new GraphData();
        data.task = TaskType.BOA_SCRIPT;
        data.function1 = inText.getText().toString();
     
        String res = NdkBridge.runBoaScript(data.toJson());

        if (res == null) return;

        DrawData drawData = DrawData.fromJson(res);
        for (DrawData.Item item : drawData.items) {
            if (item.tag.equals("calc"))
            {
                StringBuilder out = new StringBuilder();
                out.append(outText.getText().toString());
                out.append(item.msg);
                outText.setText(out.subSequence(0, out.length()));
            }
            else if (item.tag.equals("error"))
            {
                final String msg = item.msg;
                Log.e(msg);
                Toast.makeText(GlobalData.context, msg, Toast.LENGTH_LONG).show();
                break;
            }
            else if (item.tag.equals("debug"))
            {
                Log.d(item.msg);
            }
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
                Log.e("Wrong requestCode = " + requestCode);
            }
            break;
            
        } // switch (requestCode)
    } 

    
    @Override
    public void onResume()
    {
        super.onResume();

        String text = Storage.read(BOASCRIPT_SAVE_NAME);
        
        if ((text != null) && !text.isEmpty())
        {
            inText.setText(text);
        }
    }
    
    @Override
    public void onPause()
    {
        Storage.write(BOASCRIPT_SAVE_NAME, inText.getText().toString());
        
        super.onPause();
    }   
 
} // class BoascriptFragment
