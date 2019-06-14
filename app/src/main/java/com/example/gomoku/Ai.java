package com.example.gomoku;
import android.graphics.Point;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import java.util.ArrayList;
import java.util.List;

public class Ai {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    Ai(){
        System.out.println("");
        System.out.print("Hllo!!!!!");
    }


    public native static Point chess(ArrayList<Point> mBlackList, ArrayList<Point> mWhiteList, TFLite T);
    public native void test();
    public native static void tes();
    public native static int addd(TFLite T);
}
