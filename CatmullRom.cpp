#include "CatmullRom.h"
Point CatmullRom::calculateY(Point p[], float t) const
{
	float t2 = pow(t, 2);
	float t3 = pow(t, 3);
	Point Qt = ((p[2] - p[0]) * t + p[0] * (2 * t2 - t3) - p[1] * (5 * t2 - 3 * t3 - 2) + p[2] * (4 * t2 - 3 * t3) - p[3] * (t2 - t3))/2.0;
	return Qt;
}

void CatmullRom::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap) const {
	int iCtrlPtCount = ptvCtrlPts.size();
	ptvEvaluatedCurvePts.clear();
		Point temp;
	if (iCtrlPtCount >= 3) {			
		std::vector<Point> newCtrlPts;
		newCtrlPts.reserve(iCtrlPtCount + 4);

		if (bWrap) {

			temp = Point(ptvCtrlPts[iCtrlPtCount - 2]);
			temp.x -= fAniLength;
			newCtrlPts.push_back(temp);

			temp = Point(ptvCtrlPts[iCtrlPtCount - 1]);
			temp.x -= fAniLength;
			newCtrlPts.push_back(temp);

			newCtrlPts.insert(newCtrlPts.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());


			temp = Point(ptvCtrlPts[0]);
			temp.x += fAniLength;
			newCtrlPts.push_back(temp);

			temp = Point(ptvCtrlPts[1]);
			temp.x += fAniLength;
			newCtrlPts.push_back(temp);



		}
		else
		{
			
			temp = Point(ptvCtrlPts[0]);
			temp.x = 0;
			newCtrlPts.push_back(temp);
			ptvEvaluatedCurvePts.push_back(temp);


			newCtrlPts.insert(newCtrlPts.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());


			temp = Point(ptvCtrlPts[iCtrlPtCount - 1]);
			temp.x = fAniLength;

			newCtrlPts.push_back(temp);

			ptvEvaluatedCurvePts.push_back(temp);

		}

		int iCtrlPtCount = newCtrlPts.size();
		for (int subBegin = 0; subBegin < iCtrlPtCount - 3; subBegin += 1) {

			Point p[] = { newCtrlPts[subBegin] ,newCtrlPts[subBegin + 1] ,newCtrlPts[subBegin + 2] ,newCtrlPts[subBegin + 3] };
			float sample = 1.0 / (p[3].x > p[0].x ? (p[3].x - p[0].x) * 10 : (fAniLength + p[3].x - p[0].x) * 10);
			for (float t = 0; t <= 1; t += sample) {

				Point Qt = calculateY(p, t);
				ptvEvaluatedCurvePts.push_back(Qt);


			}
		}

	}
	else
	{
		Bspline::evaluateCurve(ptvCtrlPts, ptvEvaluatedCurvePts, fAniLength, bWrap);

	}
}