#pragma once

namespace Math {
	namespace StraightLineEquation {

		float gradiantFromTwoPoint(const float &x1, const float &y1, const float &x2, const float &y2);

		float gradiantFromIntersection(const float &y, const float &x, const float &intersection);

		float perpendicularGradiant(const float &gradiant);

		float intersectingPoint(const float &y, const float &x, const float &gradiant);

		float yPosAtXPos(const float &x, const float &gradiant, const float &intersection);

		float xPosAtYPos(const float &y, const float &gradiant, const float &intersection);

	}
}