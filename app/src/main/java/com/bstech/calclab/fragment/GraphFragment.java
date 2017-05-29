package com.bstech.calclab.fragment;

import java.io.File;

import android.annotation.SuppressLint;
import android.app.Fragment;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
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
import android.widget.LinearLayout;

import android.widget.Spinner;

import android.widget.TextView;
import android.widget.Toast;

import com.bstech.calclab.NdkBridge;
import com.bstech.calclab.R;
import com.bstech.calclab.TaskType;
import com.bstech.calclab.filemanager.FileManager;
import com.bstech.calclab.GlobalData;
import com.bstech.calclab.lib.io.FIleIO;
import com.bstech.calclab.lib.log.Log;
//import com.bstech.calclab.lib.util.Storage;
import com.bstech.calclab.models.GraphData;
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

    private LinearLayout mYBorders   = null;

    private EditText  yMinText      = null;
    private TextView  yMinTextView  = null;
    private EditText  yMaxText      = null;
    private TextView  yMaxTextView  = null;

    private GraphView graphView     = null;
    private Spinner   graphType     = null;

    private int       m_taskType    = -1;

    // METHODS
    
    public GraphFragment()
    {
        super();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        View view = inflater.inflate(R.layout.fragment_graph, container, false);

        yTextView1    = (TextView)view.findViewById(R.id.yTextView1);
        functionText1 = (EditText)view.findViewById(R.id.functionText1);
        yTextView2    = (TextView)view.findViewById(R.id.yTextView2);
        functionText2 = (EditText)view.findViewById(R.id.functionText2);

        xMinText      = (EditText)view.findViewById(R.id.borderXMinText);
        xMinTextView  = (TextView)view.findViewById(R.id.borderXMinTextView);
        xMaxText      = (EditText)view.findViewById(R.id.borderXMaxText);
        xMaxTextView  = (TextView)view.findViewById(R.id.borderXMaxTextView);

        mYBorders      = (LinearLayout)view.findViewById(R.id.yBorders);

        yMinText      = (EditText)view.findViewById(R.id.borderYMinText);
        yMinTextView  = (TextView)view.findViewById(R.id.borderYMinTextView);
        yMaxText      = (EditText)view.findViewById(R.id.borderYMaxText);
        yMaxTextView  = (TextView)view.findViewById(R.id.borderYMaxTextView);

        graphView     = (GraphView)view.findViewById(R.id.graphView);
        graphType     = (Spinner)view.findViewById(R.id.graphType);

        graphType.setOnItemSelectedListener(new OnItemSelectedListener()
        {
            @Override
            public void onItemSelected(AdapterView<?> arg0, View arg1, int arg2, long arg3)
            {
                if (m_taskType != -1) {
                    GraphData.writeData(m_taskType, getGraphData(m_taskType).toJson());
                }

                m_taskType = arg2;
                Log.i("m_TaskType = " + m_taskType);

                String graphData = GraphData.readData(m_taskType);
                setGraphData(m_taskType, graphData);
                fetchData(getGraphData(m_taskType).toJson());
            }

            @Override
            public void onNothingSelected(AdapterView<?> arg0) {}
        });

        Button runGraph = (Button)view.findViewById(R.id.runGraph);
        runGraph.setOnClickListener(new OnClickListener() {
            @SuppressLint("NewApi")
            public void onClick(View view)
            {
                fetchData(getGraphData(m_taskType).toJson());
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
                    FIleIO.write(workFile, getGraphData(m_taskType).toJson());
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
    public void onResume()
    {
        super.onResume();
        int taskType = GraphData.readType();
        if (taskType == -1) taskType = 0;
        graphType.setSelection(taskType);
    }

    @Override
    public void onPause()
    {
        GraphData.writeType(m_taskType);
        GraphData.writeData(m_taskType, getGraphData(m_taskType).toJson());
        super.onPause();
    }

    @Override
    public void onViewStateRestored(Bundle savedInstanceState)
    {
        super.onViewStateRestored(savedInstanceState);

        Log.i("" + graphView.getWidth());
    }

    private GraphData getGraphData(int currentTask)
    {
        GraphData data = new GraphData();

        DisplayMetrics metrics = new DisplayMetrics();
        GlobalData.mainActivity.getWindowManager().getDefaultDisplay().getMetrics(metrics);
        data.densityDpi = metrics.densityDpi;
        data.task = currentTask;
        data.discrete = (currentTask == TaskType.DECART_3D) ? 50 : 500;

        try {
            data.function1 = functionText1.getText().toString();
        } catch (Exception e) {}

        try {
            data.function2 = functionText2.getText().toString();
        } catch (Exception e) {}

        try {
            data.xMin = Double.parseDouble(xMinText.getText().toString());
        } catch (Exception e) {}

        try {
            data.xMax = Double.parseDouble(xMaxText.getText().toString());
        } catch (Exception e) {}

        try {
            data.yMin = Double.parseDouble(yMinText.getText().toString());
        } catch (Exception e) {}

        try {
            data.yMax = Double.parseDouble(yMaxText.getText().toString());
        } catch (Exception e) {}

        data.viewWidth = graphView.getWidth();
        data.viewHeight = graphView.getHeight();

        return data;
    }

    private void setGraphData(int currentType, String graphData)
    {
        GraphData data = null;
        if (graphData != null) data = GraphData.fromJson(graphData);

        switch (currentType) {
            case TaskType.DECART_2D: {
                yTextView1.setText("y(x)=");
                functionText1.setText((data != null) ? data.function1 : "sin(2 * pi() * x)");

                yTextView2.setVisibility(View.GONE);
                functionText2.setVisibility(View.GONE);

                xMinTextView.setText("xMin=");
                xMinText.setText((data != null) ? ("" + data.xMin) : "0");

                xMaxTextView.setText("xMax=");
                xMaxText.setText((data != null) ? ("" + data.xMax) : "2");

                mYBorders.setVisibility(View.GONE);
            }
            break;
            
            case TaskType.DECART_3D: {
                yTextView1.setText("z(x,y)=");
                functionText1.setText((data != null) ? data.function1 :
                        "2 * cos(2 * pi() * x) * sin(2 * pi() * y)");

                yTextView2.setVisibility(View.GONE);
                functionText2.setVisibility(View.GONE);

                xMinTextView.setText("xMin=");
                xMinText.setText((data != null) ? ("" + data.xMin) : "-1");
                xMaxTextView.setText("xMax=");
                xMaxText.setText((data != null) ? ("" + data.xMax) : "1");

                mYBorders.setVisibility(View.VISIBLE);

                yMinTextView.setText("yMin=");
                yMinText.setText((data != null) ? ("" + data.yMin) : "-1");
                yMaxTextView.setText("yMax=");
                yMaxText.setText((data != null) ? ("" + data.yMax) : "1");
            }
            break;
            
            case TaskType.POLAR: {
                yTextView1.setText("r(f)=");
                functionText1.setText((data != null) ? data.function1 : "sin(2*f) * cos(3*f)");

                yTextView2.setVisibility(View.GONE);
                functionText2.setVisibility(View.GONE);

                xMinText.setText("0");
                xMinTextView.setText("fMin=");
                xMaxText.setText("6.283");
                xMaxTextView.setText("fMax=");

                mYBorders.setVisibility(View.GONE);
            }
            break;
            
            case TaskType.PARAMETRIC: {
                yTextView1.setText("x(t)=");
                functionText1.setVisibility(View.VISIBLE);
                functionText1.setText((data != null) ? data.function1 : "sin(2 * t)");

                yTextView2.setVisibility(View.VISIBLE);
                yTextView2.setText("y(t)=");
                functionText2.setVisibility(View.VISIBLE);
                functionText2.setText((data != null) ? data.function2 : "cos(5 * t)");

                xMinTextView.setText("tMin=");
                xMinText.setText((data != null) ? ("" + data.xMin) : "0");
                xMaxTextView.setText("tMax=");
                xMaxText.setText((data != null) ? ("" + data.xMax) : "6.283");

                mYBorders.setVisibility(View.GONE);
            }
            break;

            default: {
                // TODO ?
            }
            break;
        }
    }
    
    private void fetchData(final String graphData)
    {
        final ProgressDialog progressDialog = ProgressDialog.show(GlobalData.context, "", "Drawing...");
        
        new Thread()
        {
            public void run()
            {
                final String result = NdkBridge.runBoaScript(graphData);

                new Handler(Looper.getMainLooper(), new Handler.Callback() {
                    @Override
                    public boolean handleMessage(Message msg) {

                        String graph = result;
                        graphView.setData(graph);

                        progressDialog.dismiss();

                        return false;
                    }
                }).sendEmptyMessage(0);
            }
        }.start();
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
                            String graphData = FIleIO.read(file);
                            workFile = file;
                                                    
                            Log.i("graphData = " + graphData);

                            setGraphData(m_taskType, graphData);
                            graphType.setSelection(m_taskType);
                        }
                    }
                    break;
                    
                case FileManager.RESULT_FAIL:
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
                            String fileName = data.getExtras().getString("filePath");
                            if (fileName != null) {
                                File file = new File(fileName);
                                if (FIleIO.write(file, getGraphData(m_taskType).toJson())) {
                                    workFile = file;
                                }
                                else
                                {
                                    Toast.makeText(getActivity(), "Can't write file", Toast.LENGTH_SHORT)
                                            .show();
                                }
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
} // class GraphFragment
