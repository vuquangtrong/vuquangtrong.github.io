package com.android.server.invcase;

import android.hardware.invcase.IInvcaseManager;
import android.content.Context;
import android.util.Log;
import com.android.server.SystemService;

public class InvcaseService extends SystemService {
    static final String TAG = "Invcase";
    static final boolean DEBUG = false;

    final IInvcaseManagerImpl mManagerService;

    private final class IInvcaseManagerImpl extends IInvcaseManager.Stub {
        @Override
        public String getData() {
            String str = invcase_native_read();
            Log.d(TAG, "InvcaseService: IInvcaseManager.getData= " + str);
            return str;
        }
        
        @Override
        public void putData(String data) {
            Log.d(TAG, "InvcaseService: IInvcaseManager.putData= " + data);
            invcase_native_write(data);
        }
    }

    public InvcaseService(Context context) {
        super(context);
        invcase_native_init();
        mManagerService = new IInvcaseManagerImpl();
        Log.d(TAG, "InvcaseService: mManagerService= " + mManagerService);
    }

    @Override
    public void onStart() {
        publishBinderService(Context.INVCASE_SERVICE, mManagerService);
        Log.d(TAG, "InvcaseService: onStart");
    }

    @Override
    protected void finalize() throws Throwable {
        invcase_native_deinit();
        super.finalize();
    }
    
    private static native void invcase_native_init();
    private static native void invcase_native_deinit();
    private static native String invcase_native_read();
    private static native void invcase_native_write(String string);
}
