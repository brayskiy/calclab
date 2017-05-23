package com.bstech.calclab.fragment;

import java.io.File;

import android.annotation.SuppressLint;
import android.app.Fragment;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.DisplayMetrics;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.bstech.calclab.R;
import com.bstech.calclab.TaskType;
import com.bstech.calclab.filemanager.FileManager;
import com.bstech.calclab.GlobalData;
import com.bstech.calclab.lib.io.FIleIO;
import com.bstech.calclab.lib.log.Log;
import com.bstech.calclab.lib.util.Storage;
import com.bstech.calclab.view.GraphView;


public class GraphFragment extends Fragment
{
    //private float m_inTextSize  = 12f;

    final private static String GRAPH_DATA_SAVE_NAME = "graph_data_save_";
    
    private File      workFile      = null;
    private TextView  yTextView1    = null;
    private EditText  functionText1 = null;
    private TextView  yTextView2    = null;
    private EditText  functionText2 = null;
    private EditText  xMinText      = null;
    private TextView  xMinTextView  = null;
    private EditText  xMaxText      = null;
    private TextView  xMaxTextView  = null;
    private EditText  yMinText      = null;
    private TextView  yMinTextView  = null;
    private EditText  yMaxText      = null;
    private TextView  yMaxTextView  = null;
    private GraphView graphView     = null;
    private Spinner   graphType     = null;
    private int       m_taskType    = -1;
    private boolean   m_initView    = true;
    
    private volatile ProgressDialog progressDialog = null;
    
    // METHODS
    
    public GraphFragment()
    {
        super();
    }
    

    private String getGraphData(final int currentTask)
    {
        DisplayMetrics metrics = new DisplayMetrics();
        GlobalData.mainActivity.getWindowManager().getDefaultDisplay().getMetrics(metrics);
        int densityDpi = metrics.densityDpi;

        Log.d("densityDpi = " + densityDpi);
        
        StringBuilder in = new StringBuilder();
        in.append("" + currentTask);
        in.append("@");
        in.append(functionText1.getText().toString());
        in.append("@");
        in.append(functionText2.getText().toString());
        in.append("@");
        in.append(xMinText.getText().toString());
        in.append("@");
        in.append(xMaxText.getText().toString());
        in.append("@");
        in.append(yMinText.getText().toString());
        in.append("@");
        in.append(yMaxText.getText().toString());
        in.append("@" + graphView.getWidth());
        in.append("@" + graphView.getHeight());
        in.append("@" + densityDpi);
            
        return in.toString();
    }
    
    
    private int setGraphData(final String [] tokens)
    {
        int taskType = -1;

        if (tokens != null)
        {
            if (tokens.length == 10)
            {
                taskType = Integer.parseInt(tokens[0]);
 
                functionText1.setText(tokens[1]);
                functionText2.setText(tokens[2]);
                xMinText.setText(tokens[3]);
                xMaxText.setText(tokens[4]);
                yMinText.setText(tokens[5]);
                yMaxText.setText(tokens[6]);
            }
        }
        return taskType;
    }
    
    
    void setDefaultData(final int currentType)
    {
        switch (currentType)
        {
        case TaskType.DECART_2D:
            {
                functionText1.setText("sin(2 * pi() * x)");
            
                xMinText.setText("0");
                xMaxText.setText("2");
            }
            break;
            
        case TaskType.DECART_3D:
            {
                functionText1.setText("2 * cos(2 * pi() * x) * sin(2 * pi() * y)");
                
                xMinText.setText("-1");
                xMaxText.setText("1");
                yMinText.setText("-1");
                yMaxText.setText("1");
            }
            break;
            
        case TaskType.POLAR:
            {
                functionText1.setText("sin(2*f) * cos(3*f)");
            }
            break;
            
        case TaskType.PARAMETRIC:
            {
                functionText1.setText("sin(2 * t)");
                functionText2.setText("cos(5 * t)");
            
                xMinText.setText("0");
                xMaxText.setText("6.28");    
            }
            break;
            
        case TaskType.BOA_SCRIPT:
            break;
            
        default:
            break;
        }
    }
    
    
    private void setViewItems(final int currentType)
    {
        switch (currentType)
        {
        case TaskType.DECART_2D:
            {
                yTextView1.setText("y(x)=");
                yTextView2.setText("y(x)=");
                functionText2.setText("Not Available");
                functionText2.setEnabled(false);
                xMinText.setText("");
                xMinTextView.setText("xMin=");
                xMinText.setEnabled(true);
                xMaxText.setText("");
                xMaxTextView.setText("xMax=");
                xMaxText.setEnabled(true);
                yMinText.setText("Not available");
                yMinTextView.setText("yMin=");
                yMinText.setEnabled(false);
                yMaxText.setText("Not available");
                yMaxTextView.setText("yMax=");
                yMaxText.setEnabled(false);
            }
            break;
            
        case TaskType.DECART_3D:
            {
                yTextView1.setText("z(x,y)=");
                functionText1.setText("");
                yTextView2.setText("z(x,y)=");
                functionText2.setText("Not available");
                functionText2.setEnabled(false);
                xMinText.setText("");
                xMinTextView.setText("xMin=");
                xMinText.setEnabled(true);
                xMaxText.setText("");
                xMaxTextView.setText("xMax=");
                xMaxText.setEnabled(true);
                yMinText.setText("");
                yMinTextView.setText("yMin=");
                yMinText.setEnabled(true);
                yMaxText.setText("");
                yMaxTextView.setText("yMax=");
                yMaxText.setEnabled(true);
            }
            break;
            
        case TaskType.POLAR:
            {
                yTextView1.setText("r(f)=");
                yTextView2.setText("r(f)=");
                functionText2.setText("Not available");
                functionText2.setEnabled(false);
                xMinText.setText("0");
                xMinTextView.setText("fMin=");
                xMinText.setEnabled(false);
                xMaxText.setText("6.283185307179586");//476925286766559");
                xMaxTextView.setText("fMax=");
                xMaxText.setEnabled(false);
                yMinText.setText("Not available");
                yMinTextView.setText("fMin=");
                yMinText.setEnabled(false);
                yMaxText.setText("Not available");
                yMaxTextView.setText("fMax=");
                yMaxText.setEnabled(false);
            }
            break;
            
        case TaskType.PARAMETRIC:
            {
                yTextView1.setText("x(t)=");
                yTextView2.setText("y(t)=");
                functionText2.setText("");
                functionText2.setEnabled(true);
                xMinText.setText("");
                xMinTextView.setText("tMin=");
                xMinText.setEnabled(true);
                xMaxText.setText("");
                xMaxTextView.setText("tMax=");
                xMaxText.setEnabled(true);
                yMinText.setText("Not available");
                yMinTextView.setText("tMin=");
                yMinText.setEnabled(false);
                yMaxText.setText("Not available");
                yMaxTextView.setText("tMax=");
                yMaxText.setEnabled(false);
            }
            break;
            
        case TaskType.BOA_SCRIPT:
            break;
            
        default:
            break;
        }

    }
    
    
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        Log.i("m_TaskType = " + m_taskType);
    
        if (container == null) return null;
        
        View view = inflater.inflate(R.layout.fragment_graph, container, false);

        yTextView1    = (TextView)view.findViewById(R.id.yTextView1);
        functionText1 = (EditText)view.findViewById(R.id.functionText1);
        yTextView2    = (TextView)view.findViewById(R.id.yTextView2);
        functionText2 = (EditText)view.findViewById(R.id.functionText2);
        xMinText      = (EditText)view.findViewById(R.id.borderXMinText);
        xMinTextView  = (TextView)view.findViewById(R.id.borderXMinTextView);
        xMaxText      = (EditText)view.findViewById(R.id.borderXMaxText);
        xMaxTextView  = (TextView)view.findViewById(R.id.borderXMaxTextView);
        yMinText      = (EditText)view.findViewById(R.id.borderYMinText);
        yMinTextView  = (TextView)view.findViewById(R.id.borderYMinTextView);
        yMaxText      = (EditText)view.findViewById(R.id.borderYMaxText);
        yMaxTextView  = (TextView)view.findViewById(R.id.borderYMaxTextView);
        graphView     = (GraphView)view.findViewById(R.id.graphView);
        graphType     = (Spinner)view.findViewById(R.id.graphType);
        
        m_initView = true;
        
        graphType.setOnItemSelectedListener(new OnItemSelectedListener()
        {
            @Override
            public void onItemSelected(AdapterView<?> arg0, View arg1, int arg2, long arg3)
            {
                Log.i("m_TaskType = " + m_taskType);
                
                if (!m_initView)
                {
                    Storage.write(GRAPH_DATA_SAVE_NAME + m_taskType, getGraphData(m_taskType));
                }
                else
                {
                    m_initView = false;
                }
                
                m_taskType = arg2;
                
                setViewItems(m_taskType);
                
                String graphData = Storage.read(GRAPH_DATA_SAVE_NAME + m_taskType);
                
                if (graphData != null)
                {
                    String [] tokens = graphData.split("\\@");
                
                    if ((setGraphData(tokens) != m_taskType) || tokens[1].isEmpty())
                    {
                        Log.e("Wrong data: " + tokens.toString());
                    }
                }
                else
                {
                    m_taskType = graphType.getSelectedItemPosition();
                    setDefaultData(m_taskType);
                }
                        
                 fetchData(getGraphData(m_taskType));
            }

            @Override
            public void onNothingSelected(AdapterView<?> arg0)
            {
                Log.i("m_TaskType = " + m_taskType);
                
                //fetchData(getGraphData(m_taskType));
            }
        });
        
         Button runGraph = (Button)view.findViewById(R.id.runGraph);
         runGraph.setOnClickListener(new OnClickListener() {
             @SuppressLint("NewApi")
            public void onClick(View view)
             {
                 fetchData(getGraphData(m_taskType));
             }
         });

         Button functionOpenButton = (Button)view.findViewById(R.id.functionOpen);
         functionOpenButton.setOnClickListener(new OnClickListener() {
             public void onClick(View view)
             {
                 Intent intent = new Intent(getActivity(), FileManager.class);
                 intent.putExtra("requestCode", FileManager.FILE_OPEN);
                 startActivityForResult(intent, FileManager.FILE_OPEN);
             }
         });
         
         Button functionSaveButton = (Button)view.findViewById(R.id.functionSave);
         functionSaveButton.setOnClickListener(new OnClickListener() {
             public void onClick(View view)
             {
                 if (workFile != null)
                 {
                     FIleIO.write(workFile, getGraphData(m_taskType));
                 }
             }
         });
         
         Button functionSaveAsButton = (Button)view.findViewById(R.id.functionSaveAs);
         functionSaveAsButton.setOnClickListener(new OnClickListener() {
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

         return view;
    }

    
    @Override
    public void onViewStateRestored(Bundle savedInstanceState)
    {
        super.onViewStateRestored(savedInstanceState);
        
        Log.i("" + graphView.getWidth());
    }
    
    
    private void fetchData(final String in)
    {
        if ((graphView.getWidth() == 0) || (graphView.getHeight() == 0))
        {
            Log.w("Wrong graphView data");
            graphType.setSelection(m_taskType);
            return;
        }
        
        if (progressDialog != null)
        {
            Log.w("progressDialog != null");
            return;
        }
        
        progressDialog = ProgressDialog.show(GlobalData.context, "", "Drawing...");
        
        new Thread()
        {
            public void run()
            {
                String result = GlobalData.mainActivity.runBoaScript(in);
                
                Bundle data = new Bundle();
                data.putString("graph", result);
                Message msg = new Message();
                msg.setData(data);
                messageHandler.sendMessage(msg);
            }
        }.start();
    }
    
    
    private Handler messageHandler = new Handler()
    {
        public void handleMessage(Message msg)
        {
            super.handleMessage(msg);
            
            String graph = msg.getData().getString("graph");
            graphView.setData(graph);
            
            progressDialog.dismiss();
            progressDialog = null;
        }
    };
    
    
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
                            String graphData = FIleIO.read(file);
                            workFile = file;
                                                    
                            Log.i("graphData = " + graphData);
                            
                            String [] tokens = graphData.split("\\@");
                            m_taskType = setGraphData(tokens);
                            graphType.setSelection(m_taskType);
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
                            if (FIleIO.write(file, getGraphData(m_taskType)))
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
         
         Log.i("taskType = " + m_taskType);
         
         graphType.setSelection(m_taskType);
    }
    
    
    @Override
    public void onStart()
    {
        Log.i("onStart");
        
        super.onStart();
    }
    
    
    @Override
    public void onStop()
    {
        Log.i("onStop");
        
        Storage.write(GRAPH_DATA_SAVE_NAME + m_taskType, getGraphData(m_taskType));
        m_initView = true;
        
        graphType.setSelection(-1);
        
        super.onStop();
    }
 
    
    @Override
    public void onPause()
    {
        Log.i("onPause");
        
        Storage.write(GRAPH_DATA_SAVE_NAME + m_taskType, getGraphData(m_taskType));
        m_initView = true;
        
        graphType.setSelection(-1);
        
        super.onPause();
    }
    
} // class SourceFragment
