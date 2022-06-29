+ import android.hardware.invcase.InvcaseManager;
public final class SystemServiceRegistry {
    static {
+         registerService(Context.INVCASE_SERVICE, InvcaseManager.class,
+             new CachedServiceFetcher<InvcaseManager>() {
+                 @Override
+                 public InvcaseManager createService(ContextImpl ctx)
+                     throws ServiceNotFoundException {
+                         Log.d("Invcase", "SystemServiceRegistry: registerService new InvcaseManager");
+                         return new InvcaseManager(ctx);
+                 }});
