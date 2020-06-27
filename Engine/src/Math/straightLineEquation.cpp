#include "straightLineEquation.h"

float Math::StraightLineEquation::gradiantFromTwoPoint(const float &x1, const float &y1, const float &x2, const float &y2) {

	return (y2 - y1) / (x2 - x1);

}

float Math::StraightLineEquation::gradiantFromIntersection(const float &y, const float &x, const float &intersection) {

	return (y - intersection) / x;

}

float Math::StraightLineEquation::perpendicularGradiant(const float &gradiant) {

	return -1 / gradiant;

}

float Math::StraightLineEquation::intersectingPoint(const float &y, const float &x, const float &gradiant) {

	return y - (gradiant * x);

}

float Math::StraightLineEquation::yPosAtXPos(const float &x, const float &gradiant, const float &intersection) {

	return (gradiant * x) + intersection;

}

float Math::StraightLineEquation::xPosAtYPos(const float &y, const float &gradiant, const float &intersection) {

	return (y - intersection) / gradiant;

}