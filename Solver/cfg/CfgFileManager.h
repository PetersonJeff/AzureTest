#pragma once
#include "CfgManager.h"
class CfgFileManager :
	public CfgManager
{

public:
	CfgFileManager();
	virtual ~CfgFileManager();

	//
	// Initialize the key-val pairs from the config file.
	// Command line arguments override config file values.
	//
	virtual bool init(const std::string& configFileName,
		int argc, char* argv[]);

	virtual bool init(const std::string& configFileName,
		const std::string& localOverridesFileName);


	//
	// Look up config value given a config key ...
	//
	virtual std::string getVal(const std::string& key) const;

	//
	// Set the value associated with the given key ...
	//
	virtual void setVal(const std::string& key,
		const std::string& val);

	//
	// Gets the configuration values as a map of key to value ...
	//
	virtual void getConfig(std::map< std::string, std::string >& config) const;

	//
	// Refresh the config data from sources ...
	//
	virtual bool refresh();

	//
	// Debug info ...
	//
	virtual void outputDebugInfo() const;

	//
	// Register this config manager as the singleton ...
	//
	static bool registerAsSingleton(const std::string& configFileName,
		int argc, char* argv[]);

	static bool registerAsSingleton(const std::string& configFileName,
		const std::string& localOverridesFileName);


protected:

private:
	std::map<std::string, std::string> m_params;

	// Disable copy constructor and assignment operator ...
	CfgFileManager(const CfgFileManager&);
	CfgFileManager& operator=(const CfgFileManager&);
};

