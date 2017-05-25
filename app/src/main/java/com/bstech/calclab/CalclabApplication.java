package com.bstech.calclab;

import android.app.Application;
import android.content.Context;

import com.bstech.calclab.lib.log.Log;
import com.bstech.calclab.lib.util.Storage;

/**
 * Created by brayskiy on 5/24/17.
 */

public class CalclabApplication extends Application {
    @Override
    public void onCreate() {
        super.onCreate();

        Log.init(BuildConfig.LOGGING_ENABLED);

        Storage.setContext(this);

        NdkBridge.init();
    }

    @Override
    protected void attachBaseContext(Context base) {
        super.attachBaseContext(base);

        //MultiDex.install(this);
    }
}
