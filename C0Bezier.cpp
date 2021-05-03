#include "C0Bezier.h"
#include "vec.h"

void C0Bezier::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap) const 
{
	ptvEvaluatedCurvePts.clear();
	int iCtrlPtCount = ptvCtrlPts.size();
	for (int subBegin = 0; subBegin < iCtrlPtCount; subBegin += 4) {
		if (subBegin + 4 > iCtrlPtCount + 1)
			break;
		//float x0 = ptvCtrlPts[subBegin].x;
		//Point p[4];
		//if(subBegin + 4 >= iCtrlPtCount)
			//Point p[] = { ptvCtrlPts[subBegin % iCtrlPtCount] ,ptvCtrlPts[(subBegin + 1) % iCtrlPtCount] ,ptvCtrlPts[(subBegin + 2) % iCtrlPtCount] ,ptvCtrlPts[(subBegin + 3)% iCtrlPtCount] };
		//else
			Point p[] = { ptvCtrlPts[subBegin] ,ptvCtrlPts[subBegin+1] ,ptvCtrlPts[subBegin+2] ,ptvCtrlPts[subBegin+3] };
		float sample = 1 / (p[3].x > p[0].x ? (p[3].x - p[0].x)*10: (fAniLength + p[3].x - p[0].x)*10);
		for (float t = 0; t <= 1; t += sample) {
			float t2 = pow(t, 2);
			float t3 = pow(t, 3);
			float y = (p[0] * (-3 * t + 3 * t2 - t3 + 1) + p[1] * (3 * t - 6 * t2 + 3 * t3) + p[2] * (3 * t2 - 3 * t3) + p[3] * t3).y;
			if(p[3].x > p[0].x)
				ptvEvaluatedCurvePts.push_back(Point((p[3].x-p[0].x)*t + p[0].x,y));
			else {
				Point temp((fAniLength + p[3].x - p[0].x) * t + p[0].x, y);
				if (temp.x > fAniLength) {
					temp.x -= fAniLength;
					if (temp.x > min(p[1].x,min(p[2].x, p[3].x))) {
						return;
					}
				}
				ptvEvaluatedCurvePts.push_back(temp);

			}

		}
	}

	// connect end to begin
	if (iCtrlPtCount % 4 == 0) {
		float dx = fAniLength + ptvCtrlPts[0].x - ptvCtrlPts[iCtrlPtCount - 1].x;
		float dy = (ptvCtrlPts[0].y - ptvCtrlPts[iCtrlPtCount - 1].y);
		float sample = 1 / (dx * 10);
		for (float t = 0; t <= 1; t += sample) {

				Point temp(dx * t + ptvCtrlPts[iCtrlPtCount - 1].x, ptvCtrlPts[iCtrlPtCount - 1].y+dy*t);
				if (temp.x > fAniLength) {
					temp.x -= fAniLength;
				}
				ptvEvaluatedCurvePts.push_back(temp);

		}
	}


	



}