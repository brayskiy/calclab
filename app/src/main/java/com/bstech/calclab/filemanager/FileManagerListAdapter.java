package com.bstech.calclab.filemanager;


import java.util.List;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
//import android.graphics.Matrix;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.bstech.calclab.R;
import com.bstech.calclab.GlobalData;


public class FileManagerListAdapter extends BaseAdapter
{
    private static LayoutInflater inflater = null;
    
    private List<String> textItems = null;
    private List<String> iconItems = null;
    
    //public ImageLoader imageLoader; 
    
    public FileManagerListAdapter(List<String> textItems, List<String> iconItems)
    {
        this.textItems = textItems;
        this.iconItems = iconItems;
        
        inflater = 
            (LayoutInflater) GlobalData.mainActivity.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    }

    
    public Object getItem(int position)
    {
        return position;
    }

    
    public long getItemId(int position)
    {
        return position;
    }
    
    
    public View getView(int position, View convertView, ViewGroup parent)
    {
        View vi = convertView;
        if (convertView == null)
        {
            vi = inflater.inflate(R.layout.file_manager_row, null);
        }
        TextView  text  = (TextView)vi.findViewById(R.id.tableText);;
        ImageView image = (ImageView)vi.findViewById(R.id.tableImage);
        
        text.setText(textItems.get(position));
        
        int id = GlobalData.res.getIdentifier(iconItems.get(position),
                                              "drawable",
                                              GlobalData.context.getPackageName());

        Bitmap src = BitmapFactory.decodeResource(GlobalData.res, id);

        //Matrix bitmapScale = new Matrix();
        //bitmapScale.postScale(
        //    (float)size.x / (float) src.getWidth(),
        //    (float)size.y / (float) src.getHeight());
        //Matrix mat = bitmapScale;

        Bitmap bitmap = Bitmap.createBitmap(src, 0, 0, src.getWidth(), src.getHeight(), null, true);
        
        image.setImageBitmap(bitmap);

        return vi;
    }


    public int getCount()
    {
        return textItems.size();
    }
    
} // TablesListAdapter
