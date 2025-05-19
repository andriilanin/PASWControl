#ifndef AXISSMOOTHER_H
#define AXISSMOOTHER_H

class AxisSmoother {
public:
    AxisSmoother(float smoothing = 0.1f);

    int update(float input);

    void setSmoothnessAlpha(float alpha);

private:
    float smoothnessAlpha;
    float prev;
};

#endif // AXISSMOOTHER_H
