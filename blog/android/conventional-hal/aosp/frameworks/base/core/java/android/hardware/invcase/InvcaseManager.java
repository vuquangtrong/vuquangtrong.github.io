package android.hardware.invcase;

import android.annotation.NonNull;
import android.content.Context;
import android.util.Log;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.os.ServiceManager.ServiceNotFoundException;

public final class InvcaseManager {
    static final String TAG = "Invcase";
    private final Context mContext;
    private final IInvcaseManager mService;

    /**
     * Creates a InvcaseManager.
     *
     * @hide
     */
    public InvcaseManager(@NonNull Context context) throws ServiceNotFoundException {
        this(context, IInvcaseManager.Stub.asInterface(
            ServiceManager.getServiceOrThrow(Context.INVCASE_SERVICE)));
    }

    /**
     * Creates a InvcaseManager with a provided service implementation.
     *
     * @hide
     */
    public InvcaseManager(@NonNull Context context, @NonNull IInvcaseManager service) {
        mContext = context;
        mService = service;
        Log.d(TAG, "InvcaseManager: mContext= " + mContext + " mService= " + mService);
    }


    public @NonNull String getData() {
        try {
            String str = mService.getData();
            Log.d(TAG, "InvcaseManager: mService.getData= " + str);
            return str;
        } catch (RemoteException e) {
            e.printStackTrace();
        }
        return null;
    }

    public void putData(@NonNull String data) {
        try {
            Log.d(TAG, "InvcaseManager: mService.putData= " + data);
            mService.putData(data);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }
}
