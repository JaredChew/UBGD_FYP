#pragma once

#include <string>

#include "random.h"

namespace Utilities {
	namespace Cypto {

		template<typename dataType>
		dataType encrypt(const std::string &key, const dataType &data, int &generatedKey);

		template<typename dataType>
		dataType decrypt(const std::string &key, const dataType &data, const int &generatedKey);

	}
}