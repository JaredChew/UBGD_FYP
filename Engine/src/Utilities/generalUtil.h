#pragma once

namespace Utilities {

	template<typename custom> bool compareGreather(custom comparingWith, custom toBeComparedWith);
	template<typename custom> bool compareLesser(custom comparingWith, custom toBeComparedWith);

	double removeHeadingZeros(double value);

}