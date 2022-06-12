package com.invcase;

import android.hardware.invcase.InvcaseManager;
import android.content.Context;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.util.Log;

public class Invcase extends Activity {
    private static final String TAG = "Invcase";

    private InvcaseManager mManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mManager = (InvcaseManager)getSystemService(Context.INVCASE_SERVICE);
        Log.d(TAG, "App: mManager= " + mManager);

        Button btn = (Button)findViewById(R.id.button);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                EditText editText = (EditText)findViewById(R.id.editText);
                String txt = editText.getText().toString();
                Log.d(TAG, "App: request= " + txt);
                
                mManager.putData(txt);
                
                String ret = mManager.getData();
                Log.d(TAG, "App: received= " + ret);

                TextView tv = (TextView)findViewById(R.id.textView);
                tv.setText(ret);
            }
        });
    }
}
