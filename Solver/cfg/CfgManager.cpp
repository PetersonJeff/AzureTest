#include "pch.h"

#if defined (WIN32) || defined (WIN64)
#  pragma warning( disable : 4786 )
#  pragma warning( disable : 4503 )
#  pragma warning( disable : 4996 )
#endif

#if defined (WIN32) || defined (WIN64)
#  define strcasecmp stricmp
#else
#  define stricmp strcasecmp
#endif


#include "CfgManager.h"
#include <util/UtilMutex.h>
#include "util/Utils.h"

CfgManager* CfgManager::s_singleton = nullptr;

static UtilMutex config_mutex;

CfgManager::CfgManager() {
}

CfgManager::~CfgManager() {
}

int CfgManager::getIntValue(const std::string& key, int defaultVal) const {
	std::string  cfgStr = getVal(key);

	if (!cfgStr.empty()) {
		return ::atoi(cfgStr.c_str());
	}

	return defaultVal;
}

double CfgManager::getDoubleValue(const std::string& key, double defaultVal) const {
	std::string  cfgStr = getVal(key);

	if (!cfgStr.empty()) {
		return ::atof(cfgStr.c_str());
	}

	return defaultVal;
}

std::string CfgManager::getStringValue(const std::string& key, const std::string& defaultVal) const {
	std::string  cfgStr = getVal(key);

	if (!cfgStr.empty()) {
		return cfgStr;
	}

	return defaultVal;
}

bool CfgManager::getBoolValue(const std::string& key, bool defaultVal) const {
	std::string  cfgStr = getVal(key);

	if (!cfgStr.empty()) {
		if (strcasecmp(cfgStr.c_str(), "true") == 0) {
			return true;
		}

		return false;
	}

	return defaultVal;
}

void CfgManager::setValsForCurrentSession(const std::map<std::string, std::string>& vals) {
	UtilAutoLock lock(config_mutex);

	std::string sessionId = Utils::getCurrentThreadId();

	_sessionParams[sessionId] = vals;
}

void CfgManager::cleanValsForCurrentSession() {
	UtilAutoLock lock(config_mutex);

	std::string sessionId = Utils::getCurrentThreadId();

	std::map<std::string, std::map<std::string, std::string> >::iterator
		it = _sessionParams.find(sessionId);

	if (it != _sessionParams.end()) {
		_sessionParams.erase(it);
	}
}

void CfgManager::getConfigParameters(const std::string& expression,
	std::vector<std::pair<std::string, std::string>>& parameters) const {
	parameters.clear();

	std::map<std::string, std::string>::const_iterator iter;

	std::map<std::string, std::string> config;
	getConfig(config);

	for (iter = config.begin(); iter != config.end(); ++iter) {
		const std::string& key = (*iter).first;

		if (key.find(expression) != std::string::npos) {
			parameters.push_back((*iter));
		}
	}
}




