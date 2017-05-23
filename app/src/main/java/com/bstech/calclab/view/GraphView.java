package com.bstech.calclab.view;


import java.util.Vector;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.bstech.calclab.GlobalData;
import com.bstech.calclab.lib.graphics.BColor;
import com.bstech.calclab.lib.log.Log;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.View;
import android.widget.Toast;


public class GraphView extends View 
{
    private Paint  paint  = new Paint();
    
    private Vector<Integer> x1   = new Vector<Integer>();
    private Vector<Integer> x2   = new Vector<Integer>();
    private Vector<Integer> y1   = new Vector<Integer>();
    private Vector<Integer> y2   = new Vector<Integer>();
    private Vector<Byte>    type = new Vector<Byte>();

    // MEMBERS
    
    public GraphView(Context context)
    {
        super(context);
    }
    
    
    public GraphView(Context context, AttributeSet attrs)
    {
        super(context, attrs);
    }

    
    @Override
    protected void onMeasure(int widthSpec, int heightSpec)
    {
        int measuredWidth  = MeasureSpec.getSize(widthSpec);
        int measuredHeight = MeasureSpec.getSize(heightSpec);

        setMeasuredDimension(measuredWidth, measuredHeight);

        // If you consider drawing circle as an example, you need to select the minimum
        // of height and width and set that value as your screen dimensions.

        int d = Math.min(measuredWidth, measuredHeight);
        setMeasuredDimension(d, d); 
    }
    
    
    public void setData(final String inData)
    {
        if (inData == null) return;
        
        x1.clear();
        x2.clear();
        y1.clear();
        y2.clear();
        type.clear();
        
        try
        {
            JSONArray json = new JSONObject(inData).getJSONArray("items");
        
            Log.d("json.length", "" + json.length());
            
            for (int i = 0; i < json.length(); ++i)
            {
                JSONObject item = json.getJSONObject(i);        
        
                String tag = item.getString("tag");
        
                if (tag.equals("line"))
                {
                    type.add((byte)'L');
                    x1.add(item.getInt("x1"));
                    y1.add(item.getInt("y1"));
                    x2.add(item.getInt("x2"));
                    y2.add(item.getInt("y2"));
                }
                else if (tag.equals("pen"))
                {
                    type.add((byte)'C');
                    x1.add(item.getInt("color"));
                    y1.add(0);
                    x2.add(0);
                    y2.add(0);
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
        
        invalidate();
    }
    
    @Override
    protected synchronized void onDraw(Canvas canvas)
    {
        super.onDraw(canvas);

        paint.setStrokeWidth(2);
        paint.setColor(BColor.get("White"));
        paint.setAntiAlias(true);
        //canvas.drawPaint(paint);
        //canvas.drawBitmap(BitmapCache.getBackground(), 0f, 0f, GlobalData.mainPaint);
         
        for (int i = 0; i < type.size(); ++i)
        {
            switch (type.get(i))
            {
            case 'L':
                canvas.drawLine(x1.get(i), y1.get(i), x2.get(i), y2.get(i), paint); break;
            case 'C':
                paint.setColor(x1.get(i));
            }
        }
     }            

} // class GraphView
