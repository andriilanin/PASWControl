#include "axissmoother.h"

AxisSmoother::AxisSmoother(float smoothing)
    : smoothnessAlpha(smoothing), prev(0.0f) {};

int AxisSmoother::update(float input) {
    float target = (input / 9.8f) * 32768.0f;

    prev = smoothnessAlpha * target + (1.0f - smoothnessAlpha) * prev;
    return static_cast<int>(prev);
}

void AxisSmoother::setSmoothnessAlpha(float alpha) {
    this->alpha = smoothnessAlpha;
};
