#include "axissmoother.h"

AxisSmoother::AxisSmoother(float smoothing)
    : alpha(smoothing), prev(0.0f) {};

int AxisSmoother::update(float input) {
    float target = (input / 9.8f) * 32768.0f;

    prev = alpha * target + (1.0f - alpha) * prev;
    return static_cast<int>(prev);
}

void AxisSmoother::setAlpha(float alpha) {
    this->alpha = alpha;
};
