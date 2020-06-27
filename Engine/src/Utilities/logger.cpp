#include "logger.h"

Logger *Logger::instance;

void Logger::init(const std::string &title, const std::string &version, const bool &exportToFile, const std::string &directory) {

	if (ENABLE_LOG && !instance) { instance = new Logger(title, version, exportToFile, directory); }

}

Logger *Logger::getInstance() {

	return instance;

}

Logger::Logger(const std::string &title, const std::string &version, const bool &exportToFile, const std::string &directory) {

	this->title = title;
	this->version = version;

	previousError = Logger::LogType::NONE;

	this->exportToFile = exportToFile;

	if (exportToFile) {

		this->directory = directory;

		logFileRead = std::ifstream(directory.c_str());
		logFileWrite = std::ofstream(directory.c_str());

		initFile();

	}

	std::cout << "Logger ready" << std::endl;

}

Logger::~Logger() {

	std::cout << "\nLogger system shut down" << std::endl;

	if (exportToFile) {

		logFileWrite.open(directory.c_str(), std::ios::app);

		logFileWrite << "\nPlease make a copy of this file you wish to save this file";
		logFileWrite << "\nThe next runtime of the application will re-write the contents of this file." << std::endl;

		std::cout << "All logs dumpped at: " << directory.c_str() << std::endl;

		logFileWrite.close();

	}

}

void Logger::initFile() {

	//bool fileExist = logFileRead.is_open();

	std::remove(directory.c_str());

	logFileWrite.open(directory.c_str(), std::ios::app);

	logFileWrite << "\n" << std::endl;

	logFileWrite.close();

	logFileWrite.open(directory.c_str(), std::ios::app);

	logFileWrite << title << "   v" << version << std::endl;

	logFileWrite.close();

}

std::string Logger::getDateTime() {

   // https://stackoverflow.com/questions/17223096/outputting-date-and-time-in-c-using-stdchrono //

	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");

	return ss.str();

}

void Logger::writeToFile(const std::string &header, const std::string &msg, const bool &differentLog) {

	logFileWrite.open(directory.c_str(), std::ios::app);

	if (differentLog) { logFileWrite << "\n"; }

	logFileWrite << "[" << header << "] " << getDateTime() << ":	";

	logFileWrite << msg << std::endl;

	logFileWrite.close();

}

void Logger::writeLog(const std::string &logMsg) {

	if (!ENABLE_LOG || instance == nullptr) { return; }

	bool differentLog = previousError != Logger::LogType::LOG;

	previousError = Logger::LogType::LOG;

	if (exportToFile) { writeToFile("LOG", logMsg, differentLog); }

	if (differentLog) { std::cout << "\n"; }

	std::cout << "[LOG] " << logMsg << std::endl;

}

void Logger::infoLog(const std::string &infoMsg) {

	if (!ENABLE_LOG || instance == nullptr) { return; }

	bool differentLog = previousError != Logger::LogType::INFO;

	previousError = Logger::LogType::INFO;

	if (exportToFile) { writeToFile("INFO", infoMsg, differentLog); }

	if (differentLog) { std::cout << "\n"; }

	std::cout << "[INFO] " << infoMsg << std::endl;

}

void Logger::debugLog(const std::string &dbugMsg) {

	if (!ENABLE_LOG || instance == nullptr) { return; }

	bool differentLog = previousError != Logger::LogType::DEBUG;

	previousError = Logger::LogType::DEBUG;

	if (exportToFile) { writeToFile("DEBUG", dbugMsg, differentLog); }

	if (differentLog) { std::cout << "\n"; }

	std::cout << "[DEBUG] " << dbugMsg << std::endl;

}

void Logger::warningLog(const std::string &wrngMsg) {

	if (!ENABLE_LOG || instance == nullptr) { return; }

	bool differentLog = previousError != Logger::LogType::WARNING;

	previousError = Logger::LogType::WARNING;

	if (exportToFile) { writeToFile("WARNING", wrngMsg, differentLog); }

	if (differentLog) { std::cout << "\n"; }

	std::cerr << "[WARNING] " << wrngMsg << std::endl;

}

void Logger::errorLog(const std::string &errMsg) {

	if (!ENABLE_LOG || instance == nullptr) { return; }

	bool differentLog = previousError != Logger::LogType::ERROR;

	previousError = Logger::LogType::ERROR;

	if (exportToFile) { writeToFile("ERROR", errMsg, differentLog); }

	if (differentLog) { std::cout << "\n"; }

	std::cerr << "[ERROR] " << errMsg << std::endl;

}

void Logger::customLog(const std::string &header, const std::string &msg) {

	if (!ENABLE_LOG || instance == nullptr) { return; }

	bool differentLog = previousError != Logger::LogType::CUSTOM;

	previousError = Logger::LogType::CUSTOM;

	if (exportToFile) { writeToFile(header, msg, differentLog); }

	if (differentLog) { std::cout << "\n"; }

	std::cerr << "[" << header << "] " << msg << std::endl;

}
