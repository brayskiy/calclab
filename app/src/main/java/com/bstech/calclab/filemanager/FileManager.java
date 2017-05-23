package com.bstech.calclab.filemanager;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import com.bstech.calclab.R;
import com.bstech.calclab.GlobalData;
import com.bstech.calclab.lib.log.Log;


public class FileManager extends Activity
{
    final public static int RESULT_OK   = 0;
    final public static int RESULT_FAIL = 1;
    final public static int FILE_OPEN   = 0;
    final public static int FILE_SAVE   = 1;
    
    private ListView     filesList    = null;
    private List<String> textItem     = null;
    private List<String> iconItem     = null;
    private List<String> path         = null;
    private String       startDir     = GlobalData.context.getApplicationInfo().dataDir;
    private String       homeDir      = GlobalData.context.getApplicationInfo().dataDir;
    private String       root         = "/";
    private TextView     myPath       = null;
    private File         selectedFile = null;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
         
        setContentView(R.layout.file_manager);
         
        myPath = (TextView)findViewById(R.id.path);
        
        final EditText fileName = (EditText)FileManager.this.findViewById(R.id.fileName);
        
        filesList = (ListView)FileManager.this.findViewById(R.id.filesList);
        filesList.setOnItemClickListener(new OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> l, View v, int position, long id)
            {
                final File file = new File(path.get(position));

                if (file.isDirectory())
                {
                    if (file.canRead())
                    {
                        startDir = path.get(position);
                        getDir(startDir);
                    }
                    else
                    {
                        /*
                        new AlertDialog.Builder(FileManager.this)
                        .setIcon(R.drawable.file_manager_cantread)
                        .setTitle("[" + file.getName() + "] folder can't be read!")
                        .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                            }
                        }).show();
                        */
                    }
                }
                else
                {
                    fileName.setText(file.getName());
                    selectedFile = file;
                }
            }
        });
        
        Button button = (Button)FileManager.this.findViewById(R.id.openButton);
        button.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                //
                Intent requestData = getIntent();
                Bundle extras = requestData.getExtras();
                int requestCode = -1;
                if (extras != null)
                {
                    requestCode = extras.getInt("requestCode");
                }
                
                if (requestCode != -1)
                {
                    String filePath = null;                    
                    if (requestCode == FILE_OPEN)
                    {
                        if (selectedFile != null)
                        {
                            filePath = selectedFile.getPath();
                        }
                    }
                    else if (requestCode == FILE_SAVE)
                    {
                        if (!fileName.toString().equals(""))
                        {
                            filePath = startDir + "/" + fileName.getText().toString();
                            
                            Log.d("startDir = " + startDir);
                            Log.d("fileName = " + fileName.getText().toString());
                        }
                    }
                    
                    Log.d("FileManager.button", "filePath = " + filePath);
                    
                    Intent data = new Intent();
                    data.putExtra("filePath", filePath);
                    setResult(RESULT_OK, data);
                    FileManager.this.finish();
                }
                else
                {
                    Log.e("FileManager.openButton", "Unknown Request Code");
                    setResult(RESULT_FAIL, null);
                    FileManager.this.finish();
                }
            }
        });
        
        final Button cancelButton = (Button)FileManager.this.findViewById(R.id.cancelButton);
        cancelButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                setResult(RESULT_FAIL, null);
                FileManager.this.finish();
            }
        });
        
        getDir(startDir);
        
        Intent requestData = getIntent();
        Bundle extras = requestData.getExtras();
        String workFile = null;
        if (extras != null)
        {
            workFile = extras.getString("workFile");
            
            if (workFile != null)
            {
                fileName.setText(workFile);
            }
        }
    }

     
    private void getDir(String dirPath)
    {
        myPath.setText("Location: " + dirPath);
         
        textItem = new ArrayList<String>();
        iconItem = new ArrayList<String>();
        path     = new ArrayList<String>();
         
        File    f     = new File(dirPath);
        File [] files = f.listFiles();

        if (!dirPath.equals(root))
        {
            textItem.add(root);
            iconItem.add("file_manager_cantread");
            path.add(root);
        }
        
        if (!dirPath.equals(homeDir))
        {
            textItem.add("Home");
            iconItem.add("file_home");
            path.add(homeDir);
        }
        
        if (!dirPath.equals(root))
        {
            File parent = new File("..");
            textItem.add("../");
            if (parent.canRead())
            {
                iconItem.add("log_out");
            }
            else
            {
                iconItem.add("file_cancel");
            }
            path.add(f.getParent());
        }
        
        for (int i = 0; i < files.length; ++i)
        {
            File file = files[i];
            path.add(file.getPath());

            if (file.isDirectory())
            {
                textItem.add(file.getName() + "/");
                if (file.canRead())
                {
                    iconItem.add("file_folder");
                }
                else
                {
                    iconItem.add("file_cancel");
                }
            }
            else
            {
                textItem.add(file.getName());
                iconItem.add("file_file");
            }
        }

        FileManagerListAdapter fileListAdapter = new FileManagerListAdapter(textItem, iconItem);
        filesList.setAdapter(fileListAdapter);
    }
}
