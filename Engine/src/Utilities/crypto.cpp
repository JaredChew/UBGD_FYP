#include "crypto.h"

template<typename dataType>
dataType Utilities::Cypto::encrypt(const std::string &key, const dataType &data, int &generatedKey) {

	Utilities::Random::seedRandom();

	generatedKey = Utilities::Random::randInt();

	std::string encryptedMessage, dataMessage = static_cast<std::string>(data);

	for (int i = 0; i < dataMessage.size(); ++i) {

		encryptedMessage += dataMessage[i] ^ (int(key.data()) + i) % generatedKey;

	}

	dataMessage.clear();

	return static_cast<dataType>(encryptedMessage);

}

template<typename dataType>
dataType Utilities::Cypto::decrypt(const std::string &key, const dataType &data, const int &generatedKey) {

	std::string decryptedMessage, dataMessage = static_cast<std::string>(data);

	for (int i = 0; i < dataMessage.size(); ++i) {

		decryptedMessage += dataMessage[i] ^ (int(key) + i) % generatedKey;

	}

	dataMessage.clear();

	return static_cast<dataType>(decryptedMessage);

}