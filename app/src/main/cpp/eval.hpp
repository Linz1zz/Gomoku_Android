#pragma once

#include <vector>
#include <jni.h>
// #include <numpy/arrayobject.h>
// #include <Python.h>
#include "gomoku.hpp"

using namespace gomoku;
namespace eval
{

typedef float Policy[BOARD_SIZE * BOARD_SIZE];

struct Evaluation {
    Policy policy;
    float value;
};

class PyEvaluator {
public:
    PyEvaluator(JNIEnv *env_in, jobject T_in);
    ~PyEvaluator();
    std::vector<Evaluation*> evaluate(std::vector<Game*> games, std::vector<Color> pov, JNIEnv *env, jobject T);
private:
    // JNIEnv* env;
    // jobject T;
    // jclass TFLite;
    // jmethodID PPP;
//     PyObject *py_network;
};

}
