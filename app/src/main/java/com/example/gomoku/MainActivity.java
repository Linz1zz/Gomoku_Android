package com.example.gomoku;

import android.content.res.AssetFileDescriptor;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

// public class MainActivity extends AppCompatActivity {

//      // Used to load the 'native-lib' library on application startup.
//     static {
//         System.loadLibrary("native-lib");
//     }

//     @Override
//     protected void onCreate(Bundle savedInstanceState) {
//         super.onCreate(savedInstanceState);
//         setContentView(R.layout.activity_main);

//         // Example of a call to a native method
//         TextView tv = findViewById(R.id.sample_text);
//         tv.setText(stringFromJNI());
//     }

//     /**
//      * A native method that is implemented by the 'native-lib' native library,
//      * which is packaged with this application.
//      */
//     public native String stringFromJNI();
// }

public class MainActivity extends Activity implements View.OnClickListener {
    private GobangView gobangView;
    private Button restart;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        gobangView = (GobangView) findViewById(R.id.gobang);
        restart = (Button) findViewById(R.id.restart);

        // try {
        //     String filename[] = getAssets().list("");
        //     String filename_0 = filename[0];
        //     AssetFileDescriptor fileDescriptor = getAssets().openFd("gomoku.tflite");
        // }
        // catch (Exception e) {
        //     System.out.println("out load error!");
        // }
        restart.setOnClickListener(this);
        gobangView.setIChessResultListener(new GobangView.IChessResultListener() {
            @Override
            public void ResultListerer(int result) {
                String win = "";
                if (result == 0) {
                    win = "这局黑棋赢了！";
                } else {
                    win = "这局白棋赢了！";
                }
                new AlertDialog.Builder(MainActivity.this).setTitle(win+"是否再来一局？").setPositiveButton("确定", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        gobangView.reStart();
                    }
                }).setNegativeButton("取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        finish();
                    }
                }).create().show();
            }
        });
    }

    private void showMst(String msg) {
        Toast.makeText(this, msg, Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onClick(View v) {
        if (v.getId() == R.id.restart) {
            gobangView.reStart();
        }
    }

}