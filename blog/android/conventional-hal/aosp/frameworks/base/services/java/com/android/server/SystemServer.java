import com.android.server.invcase.InvcaseService;
import android.util.Log;
public final class SystemServer implements Dumpable {
    private void startBootstrapServices(@NonNull TimingsTraceAndSlog t) {
+         // Manages Invcase device.
+         t.traceBegin("StartInvcaseService");
+         Log.d("Invcase", "SystemServer: start InvcaseService");
+         mSystemServiceManager.startService(InvcaseService.class);
+         t.traceEnd();
