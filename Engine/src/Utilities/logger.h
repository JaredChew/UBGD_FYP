#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

#define ENABLE_LOG false

#ifdef _DEBUG

#undef  ENABLE_LOG
#define ENABLE_LOG true

#endif //_DEBUG

class Logger {

private:

	static Logger *instance;

	std::string title;
	std::string version;
	std::string directory;

	std::ifstream logFileRead;
	std::ofstream logFileWrite;

	bool exportToFile;

	enum class LogType { NONE, LOG, INFO, DEBUG, WARNING, ERROR, CUSTOM } previousError;

private:

	Logger(const std::string& title, const std::string& version, const bool &exportToFile, const std::string &directory);
	~Logger();

	void initFile();

	std::string getDateTime();

	void writeToFile(const std::string &header, const std::string &msg, const bool &differentLog);

public:

	static void init(const std::string &title, const std::string &version, const bool &exportToFile, const std::string &directory = "log_export.txt");
	static Logger *getInstance();

	void writeLog(const std::string &logMsg);
	void infoLog(const std::string &infoMsg);
	void debugLog(const std::string &dbugMsg);
	void warningLog(const std::string &wrngMsg);
	void errorLog(const std::string &errMsg);
	void customLog(const std::string &header, const std::string &msg);

};