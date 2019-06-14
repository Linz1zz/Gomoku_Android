#include <jni.h>
#include <string>
#include "mcts.hpp"
#include <android/log.h>

#define LOG_TAG "netfairy-log"
#define log(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

using namespace std;
int test_add(JNIEnv *env, jclass type, jobject test);

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_gomoku_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_gomoku_Ai_chess(JNIEnv *env, jobject instance, jobject mBlackList,
                                jobject mWhiteList, jobject T) {

    // jclass cls_ArrayList = env->FindClass("java/util/ArrayList");
    // jmethodID construct = env->GetMethodID(cls_ArrayList,"<init>","()V");

    // get class
    log("HELLO!!");
    jclass black = env->GetObjectClass(mBlackList);
    jclass white = env->GetObjectClass(mWhiteList);
    jclass arrayClass = env->FindClass("java/util/ArrayList");
    jclass pointClass = env->FindClass("android/graphics/Point");
    // jclass ToPointClass = env->FindClass("com.example.gomoku.ToPoint");

    // get x, y ,<init>in Point
    jfieldID getX_ID = env->GetFieldID(pointClass, "x", "I");
    jfieldID getY_ID = env->GetFieldID(pointClass, "y", "I");
    jmethodID setXY = env->GetMethodID(pointClass, "set","(II)V");
    jmethodID construct = env->GetMethodID(pointClass, "<init>","()V");

    // next code is for test
    // static int j = 0;
    jobject toP = env->NewObject(pointClass, construct);
    // env->CallVoidMethod(toP, setXY, j, 0);
    // j++;

    // get size of black and white
    jvalue arg1, arg2;
    jmethodID sizeMid = env->GetMethodID(arrayClass, "size", "()I");
    jint black_size = env->CallIntMethodA(mBlackList, sizeMid, &arg1);
    jint white_size = env->CallIntMethodA(mWhiteList, sizeMid, &arg2);
    // return size;


    // get content of black and white
    jmethodID black_get = env->GetMethodID(black, "get", "(I)Ljava/lang/Object;");
    jmethodID white_get = env->GetMethodID(white, "get", "(I)Ljava/lang/Object;");

    // get the coordinate of black
    jobject point;
    int x, y;

    static mcts::MCTS* mcts_ptr = nullptr;
    static bool first_time = true;
    // static auto eval = PyEvaluator("../weights/519.pkl");
    if (black_size == 0 || white_size == 0)
    {
        static auto eval = PyEvaluator(env, T);
        mcts_ptr = new mcts::MCTS(new ChessState(nullptr, Game(), COLOR_BLACK), &eval, false);

    }
    point = env->CallObjectMethod(mBlackList,black_get, black_size - 1);
    x = env->GetIntField(point, getX_ID );
    y = env->GetIntField(point, getY_ID );
    Position pos = Position{y, x};
    mcts_ptr->do_set(pos);
    mcts_ptr->search(8000, env, T);
    pos = mcts_ptr->get_simulation_result(0.0);
    mcts_ptr->do_set(pos);
    env->CallVoidMethod(toP, setXY, pos.col, pos.row);

    return toP;

}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_gomoku_Ai_test(JNIEnv *env, jobject instance) {

    std::string hello = "Hello from C++";

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_gomoku_Ai_tes(JNIEnv *env, jclass type) {

    std::string hello = "Hello from C++";
    printf("ok");

}


// next code is just for test
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_gomoku_Ai_addd(JNIEnv *env, jclass type, jobject test) {
    log("Commmmmmmmmm");
    // jobject *pp = &test;
    // if (test ==0)
    //     log("NULLLLLLLLPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP");
    int sum = test_add(env, type, test);
    return sum;

}

int test_add(JNIEnv *env, jclass type, jobject test)
{

    if (test ==0)
        log("NULLLLLLLLLLLLLLLLLLLLLLLLLLL");
    jclass TFLite = env->FindClass("com/example/gomoku/TFLite");
    if (TFLite == 0)
        log("Error!!!!!!!!!!");
    // jclass TFLite = env->GetObjectClass("TFLite");
    jmethodID add = env->GetMethodID(TFLite, "add","(II)I");
    if (add == 0)
        log("DDDDDDDDDDDDDDDDD!");

    int sum = env->CallIntMethod(test, add, 1, 2);
    // log(sum);
    log("CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
    return sum;

}