namespace android {
+ int register_android_server_InvcaseService(JNIEnv *env);
};

extern "C" jint JNI_OnLoad(JavaVM* vm, void* /* reserved */)
{
+     register_android_server_InvcaseService(env);
}
