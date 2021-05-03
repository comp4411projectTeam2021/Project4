#pragma once
#include "curveevaluator.h"
class C0Bezier :
    public CurveEvaluator
{
    void evaluateCurve(const std::vector<Point>& ptvCtrlPts, std::vector<Point>& ptvEvaluatedCurvePts, const float& fAniLength, const bool& bWrap) const;
};

