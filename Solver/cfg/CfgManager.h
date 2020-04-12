#pragma once

#include <string>
#include <map>
#include <vector>

#define CfgIntValue(key, defValue) \
	CfgManager::singleton()->getIntValue(key, defValue)

#define CfgDoubleValue(key, defValue) \
	CfgManager::singleton()->getDoubleValue(key, defValue)

#define CfgStringValue(key, defValue) \
	CfgManager::singleton()->getStringValue(key, defValue)

#define CfgBoolValue(key, defValue) \
	CfgManager::singleton()->getBoolValue(key, defValue)


class CfgManager
{
public:
	virtual ~CfgManager();


	static CfgManager* singleton() { return s_singleton; }

	//
// Get the value associated with the given key ...
// This will try to get value for current session if available,
// otherwise, get from global value
//
	virtual std::string getVal(const std::string& key) const = 0;
	//
	// Get configuration values
	//

	// Int values
	virtual int         getIntValue(const std::string& key,
		int                defaultVal = 0) const;

	// Double values
	virtual double      getDoubleValue(const std::string& key,
		double             defaultVal = 0.0) const;

	// String values
	virtual std::string getStringValue(const std::string& key,
		const std::string& defaultVal = "") const;

	// Bool values
	virtual bool		getBoolValue(const std::string& key,
		bool               defaultVal = true) const;

	//
	// Set the value associated with the given key ...
	//
	virtual void setVal(const std::string& key,
		const std::string& val) = 0;

	//
	// Set the value associated with the given key and  ...
	//
	virtual void setValsForCurrentSession(const std::map<std::string, std::string>& vals);

	//
	// Clean local configuraton values for current session
	//
	virtual void cleanValsForCurrentSession();

	//
	// Gets the configuration values as a map of key to value ...
	//
	virtual void getConfig(std::map< std::string, std::string >& config) const = 0;

	void getConfigParameters(const std::string& expression,
		std::vector<std::pair<std::string, std::string> >& parameters) const;

	//
	// Refresh the config data from sources ...
	//
	virtual bool refresh() = 0;

	//
	// Debug info ...
	//
	virtual void outputDebugInfo() const = 0;

	
protected:
	static CfgManager* s_singleton;

	CfgManager();

	//Thread Id -> Config Key -> Config Value
	std::map<std::string, std::map<std::string, std::string> > _sessionParams;

	
private:
	CfgManager(const CfgManager&);
	CfgManager& operator=(const CfgManager&);
	
};

