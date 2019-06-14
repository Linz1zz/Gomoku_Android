package com.example.gomoku;
import android.app.Activity;
import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.util.Log;

import java.io.FileInputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.util.ArrayList;
import java.util.List;

import org.tensorflow.lite.Interpreter;
import org.tensorflow.lite.gpu.GpuDelegate;

import javax.xml.transform.Result;


public class TFLite {
    TFLite(Context context)
    {
        try {
            tfliteModel = loadModelFile(context);
        }
        catch (Exception e) {
            System.out.println("load error!");
        }
        System.out.println("load pass!");
        gpuDelegate = new GpuDelegate();
        if (gpuDelegate != null) {
            System.out.println("It's not NULL");
        }
        tfliteOptions = (new Interpreter.Options()).addDelegate(gpuDelegate);
        //tfliteOptions = (new Interpreter.Options());

        tflite = new Interpreter(tfliteModel, tfliteOptions);

        ObsvsData = ByteBuffer.allocateDirect( 32 * 450 * 4);

        ObsvsData.order(ByteOrder.nativeOrder());
        resultes = new float[7232];

        System.out.println("constractor_run");
    }

    /** Options for configuring the Interpreter. */
    private final Interpreter.Options tfliteOptions;

    public float data_from_c[] = new float[14400];


    public float[] evaluate(float in[])
    {
        // System.out.println(in[0] +"111111111111111");
        ObsvsData.rewind();
        for(int i = 0; i < 14400; i++)
            ObsvsData.putFloat(in[i]);

        // System.out.println(in[0] +"xxxxxxxxxxxxxxx");
        tflite.run(ObsvsData, resultes);
        return resultes;
    }


    /** Memory-map the model file in Assets. */
    private MappedByteBuffer loadModelFile(Context context) throws IOException {
        String filename[] = context.getAssets().list("");
        AssetFileDescriptor fileDescriptor = context.getAssets().openFd("gomoku.tflite");
        FileInputStream inputStream = new FileInputStream(fileDescriptor.getFileDescriptor());
        FileChannel fileChannel = inputStream.getChannel();
        long startOffset = fileDescriptor.getStartOffset();
        long declaredLength = fileDescriptor.getDeclaredLength();
        return fileChannel.map(FileChannel.MapMode.READ_ONLY, startOffset, declaredLength);
    }
    private GpuDelegate gpuDelegate;


    /** The loaded TensorFlow Lite model. */
    private MappedByteBuffer tfliteModel;

    /** An instance of the driver class to run model inference with Tensorflow Lite. */
    protected Interpreter tflite;

    /** Labels corresponding to the output of the vision model. */
    private List<String> labelList;
    private float[] resultes = null;

    /** A ByteBuffer to hold image data, to be feed into Tensorflow Lite as inputs. */
    protected ByteBuffer ObsvsData = null;

}
