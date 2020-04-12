#include "pch.h"
#include "CfgFileManager.h"

#include <fstream>
#include <vector>
#include <util/Utils.h>

using namespace std;


CfgFileManager::CfgFileManager() {
}

CfgFileManager::~CfgFileManager() {
}

bool CfgFileManager::init(const std::string& configFileName, int argc, char* argv[]) {
	char buff[4096];

	//
	// Register this instance as the singleton ...
	//
	s_singleton = this;
	
	//
	// Clear old configuration
	//
	m_params.clear();

	//
	// Read the new configuration
	//
	sprintf(buff, "Reading config file '%s'.", configFileName.c_str());

//	CBUTMSG(cbInfoGeneral, "cbcfg", "CbcfgFileManager", "init", buff);

	//
	// Open the config file ...
	//
	ifstream strm;

	strm.open(configFileName.c_str());

	if (strm.fail()) {
//		CBUTERR(cbErrorGeneral, "cbcfg", "CbcfgFileManager", "init",
//			"failed to open config file");
		return true;
	}

	//
	// Read the config parameters ...
	//
	int linenum = 0;

	std::vector<std::string> keys;

	while (!strm.eof() && strm.good()) {
		strm.getline(buff, 4096);

		std::string fileLine = Utils::trim(buff);
		linenum++;

		if (fileLine.size() > 0 && fileLine[0] != '#') {
			int pos = fileLine.find(":");

			if (pos <= 0) {
				sprintf(buff, "config file error - line %d", linenum);

//				CBUTERR(cbErrorGeneral, "cbcfg", "CbcfgFileManager", "init", buff);
			}
			else {
				std::string key =
					Utils::trim(fileLine.substr(0, pos));
				std::string val =
					Utils::trim(fileLine.substr(pos + 1, fileLine.size() - pos + 1));

				keys.push_back(key);
				m_params[key] = val;
			}
		}
	}


	//
	// Command line arguments override configuration file settings
	//
	int   ndx;

	ndx = 1;  // Skip first argument (i.e. the image name)

	while (ndx < argc) {
		if (argv[ndx][0] == '-') {
			std::string  key(&(argv[ndx][1]));
			std::string  val = "";

			if ((ndx < argc - 1) && (argv[ndx + 1][0] != '-')) {
				val = argv[ndx + 1];

				ndx++;
			}
			else {
				val = "true";
			}

			key = Utils::trim(key);
			val = Utils::trim(val);

			keys.push_back(key);
			m_params[key] = val;
		}

		ndx++;
	}
	   
	return true;
}

bool CfgFileManager::init(const std::string& configFileName, const std::string& localOverridesFileName) {
	char buff[4096];
	
	//
	// Register this instance as the singleton ...
	//
	s_singleton = this;
	
	//
	// Clear old configuration
	//
	m_params.clear();

	//
	// Read the new configuration
	//
	sprintf(buff, "Reading config file '%s'.", configFileName.c_str());

//	CBUTMSG(cbInfoGeneral, "cbcfg", "CbcfgFileManager", "init", buff);

	//
	// Open the config file ...
	//
	ifstream strm;

	strm.open(configFileName.c_str());

	if (strm.fail()) {
//		CBUTERR(cbErrorGeneral, "cbcfg", "CbcfgFileManager", "init",
//			"failed to open config file");
		return true;
	}

	//
	// Read the config parameters ...
	//
	int linenum = 0;

	std::vector<std::string> keys;

	while (!strm.eof() && strm.good()) {
		strm.getline(buff, 4096);

		std::string fileLine = Utils::trim(buff);
		linenum++;

		if (fileLine.size() > 0 && fileLine[0] != '#') {
			int pos = fileLine.find(":");

			if (pos <= 0) {
				sprintf(buff, "config file error - line %d", linenum);
//				CBUTERR(cbErrorGeneral, "cbcfg", "CbcfgFileManager", "init", buff);
			}
			else {
				std::string key = Utils::trim(fileLine.substr(0, pos));
				std::string val = Utils::trim(fileLine.substr(pos + 1, fileLine.size() - pos + 1));
				keys.push_back(key);
				m_params[key] = val;
			}
		}
	}

	if (!localOverridesFileName.empty()) {
		sprintf(buff, "Reading config file '%s'.", localOverridesFileName.c_str());

//		CBUTMSG(cbInfoGeneral, "cbcfg", "CbcfgFileManager", "init", buff);

		//
		// Open the config file ...
		//
		ifstream strm;

		strm.open(localOverridesFileName.c_str());

		if (strm.fail()) {
//			CBUTERR(cbErrorGeneral, "cbcfg", "CbcfgFileManager", "init",
//				"failed to open config file");
			return true;
		}

		//
		// Read the config parameters ...
		//
		int linenum = 0;

		std::vector<std::string> keys;

		while (!strm.eof() && strm.good()) {
			strm.getline(buff, 4096);

			std::string fileLine = Utils::trim(buff);
			linenum++;

			if (fileLine.size() > 0 && fileLine[0] != '#') {
				int pos = fileLine.find(":");

				if (pos <= 0) {
					sprintf(buff, "config file error - line %d", linenum);

//					CBUTERR(cbErrorGeneral, "cbcfg", "CbcfgFileManager", "init", buff);
				}
				else {
					std::string key = Utils::trim(fileLine.substr(0, pos));
					std::string val = Utils::trim(fileLine.substr(pos + 1, fileLine.size() - pos + 1));
					keys.push_back(key);
					m_params[key] = val;
				}
			}
		}
	}

	return true;
}

std::string CfgFileManager::getVal(const std::string& key) const {
	std::map<std::string, std::string>::const_iterator it;

	it = m_params.find(key);

	if (it == m_params.end()) {
		return "";
	}

	return (*it).second;
}

void CfgFileManager::setVal(const std::string& key, const std::string& val) {
	m_params[key] = val;
}

void CfgFileManager::getConfig(std::map<std::string, std::string>& config) const {
	config.clear();

	config = m_params;

	return;
}

bool CfgFileManager::refresh() {
//	CBUTERR(cbErrorGeneral, "cbcfg", "CbcfgFileManager", "refresh", "not implemented");
	return false;
}

void CfgFileManager::outputDebugInfo() const {
	std::string configDisplayStr = "\nConfiguration parameters:\n";

	std::map<std::string, std::string>::const_iterator it;

	for (it = m_params.begin(); it != m_params.end(); ++it) {
		const std::string& key = (*it).first;
		const std::string& val = (*it).second;

		configDisplayStr += "\t";
		configDisplayStr += key;
		configDisplayStr += ": ";
		configDisplayStr += val;
		configDisplayStr += "\n";
	}

//	CBUTALERT(cbAlertGeneral, "cbcfg", "CbcfgFileManager", "outputDebugInfo",
//		configDisplayStr.c_str());
}

bool CfgFileManager::registerAsSingleton(const std::string& configFileName, int argc, char* argv[]) {
	const char* const fn = "registerAsSingleton";

	//
	// Register this instance as the singleton ...
	//
	if (s_singleton == NULL) {
		CfgFileManager* me = new CfgFileManager();

		if (!me->init(configFileName, argc, argv))
		{
			//CBUTMSG(cbInfoGeneral, "cbcfg", "CbcfgFileManager",
			//	"registerAsSingleton", "Singleton registration failed!");
			return false;
		}

		s_singleton = me;
	}

	return true;
}

bool CfgFileManager::registerAsSingleton(const std::string& configFileName, const std::string& localOverridesFileName) {
	const char* const fn = "registerAsSingleton";

	//
	// Register this instance as the singleton ...
	//
	if (s_singleton == NULL)
	{
		CfgFileManager* me = new CfgFileManager();

		if (!me->init(configFileName, localOverridesFileName))
		{
			//CBUTMSG(cbInfoGeneral, "cbcfg", "CbcfgFileManager",
			//	"registerAsSingleton", "Singleton registration failed!");
			return false;
		}

		s_singleton = me;
	}

	return true;
}



