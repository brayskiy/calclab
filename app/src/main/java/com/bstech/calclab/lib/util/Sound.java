package com.bstech.calclab.lib.util;

import android.content.Context;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;

public class Sound
{
    private static MediaPlayer mp;

    public static void play(Context context, int id)
    {
        mp = MediaPlayer.create(context, id);
        mp.setOnCompletionListener(new OnCompletionListener() {
            public void onCompletion(MediaPlayer mpl)
            {
                mpl.release();
            }
        });
        mp.start();
    }
    
} // class Sound
