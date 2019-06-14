#include "eval.hpp"
#include <jni.h>


using namespace std;


eval::PyEvaluator::PyEvaluator(JNIEnv *env_in, jobject T_in)
{
    // env = env_in;
    // T = T_in;
    // TFLite = env->FindClass("com/example/gomoku/TFLite");
    // PPP = env->GetMethodID(TFLite, "PPP","(Ljava/util/ArrayList;)V");

}

eval::PyEvaluator::~PyEvaluator()
{
    // Py_XDECREF(py_network);
}

std::vector<eval::Evaluation*> eval::PyEvaluator::evaluate(std::vector<Game*> games, std::vector<Color> povs, JNIEnv *env, jobject T){

// std::vector<eval::Evaluation*> eval::PyEvaluator::evaluate(JNIEnv *env, jobject T)
// std::vector<eval::Evaluation*> eval::PyEvaluator::evaluate(void)
    std::vector<Evaluation*> evals;
    if (games.size() == 0) {
        return evals;
    }
    evals.reserve(games.size());
    // auto obsvs = new Observation[games.size()];
    auto obsvs = new Observation[32];
    for (int ig = 0; ig < 32; ig++) {
        if (ig < games.size()) {
            games[ig]->get_observation(obsvs[ig], povs[ig]);
        }
        else {
            games[0]->get_observation(obsvs[ig], povs[0]);
        }
    }

    log("in eval");
    // float obsvs[32*450];
    // for (size_t i = 0; i < 32 * 450; i++) {
    //     obsvs[i] = 0;
    // }

    jfloatArray test_array = env->NewFloatArray(14400);
    env->SetFloatArrayRegion(test_array, 0, 14400, (float*)obsvs);

    jclass TFLite = env->FindClass("com/example/gomoku/TFLite");
    jmethodID add = env->GetMethodID(TFLite, "evaluate","([F)[F");
    log("callfloatmethod");
    jobject sum = env->CallObjectMethod(T, add, test_array);
    jfloatArray result = (jfloatArray)sum;

    jfloat* result_float = env->GetFloatArrayElements(result, 0);
    jsize size = env->GetArrayLength(result);
    log("finish callfloatmethod");

    // if (size != 32*450){
    //     log("length error!");
    // }
    // log("length pass!");
    // for (size_t i = 0; i < 32*450; i++) {
    //     if (result_float[i] != 0.67) {
    //         log("value error!");
    //     }
    // }
    // log("value pass!");

    for (int ig = 0; ig < games.size(); ig ++) {
        auto eval = new Evaluation;
        for (int i = 0; i < BOARD_SIZE * BOARD_SIZE + 1; i ++) {
            if ((i + 1) % 226 == 0) {
                eval->value = *result_float;
            }
            else {
                eval->policy[i] = *result_float;
            }
            result_float ++;
        }
        evals.emplace_back(eval);
    }

    delete[] obsvs;
    return evals;
}
