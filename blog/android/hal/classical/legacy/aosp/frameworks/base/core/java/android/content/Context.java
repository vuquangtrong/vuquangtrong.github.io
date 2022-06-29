public abstract class Context {
    @StringDef(suffix = { "_SERVICE" }, value = {
+             INVCASE_SERVICE,
    })
+     /**
+      * Use with {@link #getSystemService(String)} to retrieve a
+      * {@link android.hardware.invcase.InvcaseManager}.
+      *
+      * @see #getSystemService(String)
+      * @hide
+      */
+     public static final String INVCASE_SERVICE = "invcase";
