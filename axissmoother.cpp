#include "axissmoother.h"

AxisSmoother::AxisSmoother(float smoothing)
    : alpha(smoothing), prev(0.0f) {};

int AxisSmoother::update(float input) {

    // float normalized = (input + 10.0f) / 20.0f;         // [0.0; 1.0]
    // float scaled = normalized * 32768.0f;
    // return static_cast<int>(scaled);



    float target = (input / 9.8f) * 32768.0f;

    prev = alpha * target + (1.0f - alpha) * prev;
    return static_cast<int>(prev);
}

void AxisSmoother::setAlpha(float alpha) {
    this->alpha = alpha;
};
