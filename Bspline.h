#pragma once
#include "C0Bezier.h"

class Bspline :
    public C0Bezier
{
    virtual float calculateY(Point p[], float t) const;
    void evaluateCurve(const std::vector<Point>& ptvCtrlPts, std::vector<Point>& ptvEvaluatedCurvePts, const float& fAniLength, const bool& bWrap) const;
};

