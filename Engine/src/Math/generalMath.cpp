#include "generalMath.h"

float Math::interpolate(const float &startValue, const float &endValue, const float &stepNumber, const float &lastStepNumber) {
	return (endValue - startValue) * stepNumber / lastStepNumber + startValue;
}