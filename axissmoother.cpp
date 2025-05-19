#include "axissmoother.h"
#include <cmath>

AxisSmoother::AxisSmoother(float smoothing)
    : smoothnessAlpha(smoothing), prev(0.0f) {};

int AxisSmoother::update(float input) {
    input = ((1-linearityAlpha) * (input/10) + linearityAlpha * std::pow(input/10, 3))*10;

    float target = (input / 9.8f) * 32768.0f;

    prev = smoothnessAlpha * target + (1.0f - smoothnessAlpha) * prev;
    return static_cast<int>(prev);
}

void AxisSmoother::setSmoothnessAlpha(float alpha) {
    this->smoothnessAlpha = alpha;
};

void AxisSmoother::setLinearityAlpha(float alpha) {
    this->linearityAlpha = alpha;
};
